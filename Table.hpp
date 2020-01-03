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
#include <iostream>
#include <sstream>

using namespace std;
using namespace cppu;

typedef std::shared_ptr<Multimedia> MultimediaPtr;
typedef std::shared_ptr<Picture> PicturePtr;
typedef std::shared_ptr<Video> VideoPtr;
typedef std::shared_ptr<Film> FilmPtr;
typedef std::shared_ptr<Group> GroupPtr;

class Table{
	
private:
	std::map<std::string, MultimediaPtr> multimediaMap;
	std::map<std::string, GroupPtr> groupMap;
	
public:
	Table(){};
	~Table(){
		std::cout << "Table  deleted" << std::endl;
	};
	
	PicturePtr createPicture(string name, string pathname, float latitude, float longitude){
		PicturePtr p = (PicturePtr) new Picture(name, pathname, latitude, longitude);
		multimediaMap[name] = p;
		return p;
	};
	
	VideoPtr createVideo(string name, string pathname,int length){
		VideoPtr v = (VideoPtr) new Video(name, pathname, length);
		multimediaMap[name] = v;
		return v;
	};
	
	FilmPtr createFilm(string name, string pathname,int length, int numberOfChapters, int * chapterLengths){
		FilmPtr f = (FilmPtr) new Film(name, pathname, length, numberOfChapters, chapterLengths);
		multimediaMap[name] = f;
		return f;
	};
	
	GroupPtr createGroupe(std::string groupName){
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
};
#endif /* Table_hpp */
