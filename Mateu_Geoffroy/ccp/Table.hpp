//
//  Table.hpp
//  Projet - INF224
//
//  Created by Geoff on 03/01/2020.
//  Copyright © 2020 Geoff. All rights reserved.
//

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
	Table(){};
	~Table(){
		std::cout << "Table  deleted" << std::endl;
	};
	

	
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
	};
	
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
	};
	
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
	};
	
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
	
	bool processRequest(TCPConnection& cnx, const string& request, string& response);
	

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
	};
	
	void saveSerialtoFile(){
		std::ofstream file("/Users/geoffhome/Documents/TPT/2A/inf224/ProjetINF224/ProjetINF224/mySerialFile.json");
		file << j;
		file.close();
	};
	
	void readSerialFile(){
		std::ifstream loadedSerial("/Users/geoffhome/Documents/TPT/2A/inf224/ProjetINF224/ProjetINF224/mySerialFile.json",std::ifstream::in);
		cout << loadedSerial.rdbuf();
		
	};
	
};


#endif /* Table_hpp */
