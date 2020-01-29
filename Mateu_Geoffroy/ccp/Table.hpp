/**
 * \file Table.hpp
 * \brief Objet qui contient une map
 *
 */

#ifndef Table_hpp
#define Table_hpp

#include "Multimedia.hpp"
#include "Video.hpp"
#include "Picture.hpp"
#include "Film.hpp"
#include "Group.hpp"
#include "tcpserver.h"
#include "cppsocket.h"

#include <map>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>


using namespace std;
using namespace cppu;

typedef std::shared_ptr<Multimedia> MultimediaPtr;
typedef std::shared_ptr<Picture> PicturePtr;
typedef std::shared_ptr<Video> VideoPtr;
typedef std::shared_ptr<Film> FilmPtr;
typedef std::shared_ptr<Group> GroupPtr;

#include "json.hpp"

using json = nlohmann::json;

class Table {

private:
	std::map<std::string, MultimediaPtr> multimediaMap;
	std::map<std::string, GroupPtr> groupMap;
	json j;

public:
    Table(){}
		~Table(){
		std::cout << "Table  deleted" << std::endl;
    }


    /**
     * @brief Crée un objet image avec ses attributs
     * @param name
     * @param pathname
     * @param latitude
     * @param longitude
     * @return Renvoie un pointeur d'image vers ce nouvel objet
     */
	PicturePtr createPicture(string name, string pathname, float latitude, float longitude){
		try{
			if (multimediaMap.count(name)>0){
				throw "Picture with the same name already created!";
			}
			if (name.find("\n") != string::npos || name.find("\r") != string::npos){
				throw "Name containing invalid caracters";
			}
		} catch (const char* e) {
			cerr << e << endl;
			return nullptr;
		}
		PicturePtr p = (PicturePtr) new Picture(name, pathname, latitude, longitude);
		multimediaMap[name] = p;
		return p;
    }

    /**
     * @brief Crée un objet vidéo avec ses attributs
     * @param name
     * @param pathname
     * @param length
     * @return Renvoie un pointeur de vidéo vers ce nouvel objet
     */
	VideoPtr createVideo(string name, string pathname,int length){
		try{
			if (multimediaMap.count(name)>0){
				throw "Video with the same name already created!";
			}
			if (name.find("\n") != string::npos || name.find("\r") != string::npos){
				throw "Name containing invalid caracters";
			}
		} catch (const char* e) {
			cerr << e << endl;
			return nullptr;
		}
		VideoPtr v = (VideoPtr) new Video(name, pathname, length);
		multimediaMap[name] = v;
		return v;
    }

    /**
     * @brief Crée un objet film avec ses attributs
     * @param name
     * @param pathname
     * @param length
     * @param numberOfChapters
     * @param chapterLengths
     * @return Renvoie un pointeur de film vers ce nouvel objet
     */
	FilmPtr createFilm(string name, string pathname,int length, int numberOfChapters, int * chapterLengths){
		try{
			if (multimediaMap.count(name)>0){
				throw "Film with the same name already created!";
			}
			if (name.find("\n") != string::npos || name.find("\r") != string::npos){
				throw "Name containing invalid caracters";
			}
			if (length <= 0){
				throw "Film's length is invalid";
			}
		} catch (const char* e) {
			cerr << e << endl;
			return nullptr;
		}
		FilmPtr f = (FilmPtr) new Film(name, pathname, length, numberOfChapters, chapterLengths);
		multimediaMap[name] = f;
		return f;
    }

    /**
     * @brief Crée un objet groupe
     * @param groupName
     * @return Renvoie un pointeur de groupe vers ce nouvel objet
     */
	GroupPtr createGroupe(std::string groupName){
		try{
			if (multimediaMap.count(groupName)>0){
				throw "Group with the same name already created!";
			}
			if (groupName.find("\n") != string::npos || groupName.find("\r") != string::npos){
				throw "Name containing invalid caracters";
			}
		} catch (const char* e) {
			cerr << e << endl;
			return nullptr;
		}
		GroupPtr g = (GroupPtr) new Group(groupName);
		groupMap[groupName] = g;
		return g;
	}

	MultimediaPtr findMultimedia(std::string name){
		return multimediaMap.at(name);
	}

	GroupPtr findGroup(std::string groupName){
		return groupMap.at(groupName);
	}

	void displayMultimedia(std::string name, std::ostream& f) const {

		multimediaMap.find(name)->second->displayMedia(f);
	}

	void displayGroup(std::string name, std::ostream& f) const {
		groupMap.find(name)->second->displayMedia(f);
	}

	void play(std::string name) const {
		multimediaMap.find(name)->second->playMedia();
	}

	void remove(std::string name);

    /**
     * @brief Cette méthode est appelée chaque fois qu'il y a une requête à traiter.
     * @param cnx : connexion tcp
     * @param request contient la requête
     * @param response sert à indiquer la réponse qui sera renvoyée au client
     * @return false : connexion close
     */
	bool processRequest(TCPConnection& cnx, const string& request, string& response);

    /**
     * @brief Permet la sérialisation des données dans un fichier de type json
     */
	void serialize(){
		for (auto& i : multimediaMap){
			MultimediaPtr media = i.second;
			if(media->getClassName() == "Picture"){
				PicturePtr myPic = dynamic_pointer_cast<Picture>(media);
				j[myPic->getClassName()][myPic->getName()] = {myPic->getPathname(), myPic->getLatitude(),myPic->getLongitude()};
			}
			if(media->getClassName() == "Video"){
				VideoPtr myVid = dynamic_pointer_cast<Video>(media);
				j[myVid->getClassName()][myVid->getName()] = {myVid->getPathname(), myVid->getLength()};
			}
			if(media->getClassName() == "Film"){
				FilmPtr myFilm = dynamic_pointer_cast<Film>(media);
				j["Video"][myFilm->getClassName()][myFilm->getName()] = {myFilm->getPathname(),myFilm->getNumberOfChapters(), *myFilm->getChapterLengths()};
			}
		}
    }

    /**
     * @brief Permet de sauver le fichier sérialisé dans un fichier .json
     */
	void saveSerialtoFile(){
		std::ofstream file("/cal/homes/gmateu/inf224/Mateu_Geoffroy/ccp/mySerialFile.json");
		file << j;
		file.close();
    }

    /**
     * @brief Permet de lire le fichier sérialisé dans un fichier .json
     */
	void readSerialFile(){
		std::ifstream loadedSerial("/cal/homes/gmateu/inf224/Mateu_Geoffroy/ccp/mySerialFile.json",std::ifstream::in);
		cout << loadedSerial.rdbuf();

    }

};


#endif /* Table_hpp */
