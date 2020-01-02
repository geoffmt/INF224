//
//  Video.hpp
//  Projet - INF224
//
//  Created by Geoff on 26/11/2019.
//  Copyright © 2019 Geoff. All rights reserved.
//

#ifndef Video_hpp
#define Video_hpp

#include <iostream>
#include <stdio.h>
#include "Multimedia.hpp"

using namespace std;

class Video : public Multimedia {
	
private:
	int length; //durée de la vidéo
	
public:
	Video();
	Video(string name, string pathname,int length):Multimedia( name,  pathname){
		this->length = length;
	}
	
	
	int getLength() const {return length;};
	
	void setLength(int newLength){this->length = newLength;};

	void playMedia() const override {
		string cmd = "mpv " + this->getPathname() + this->getName() + "&";
		system(cmd.c_str());
	};
	
};

#endif /* Video_hpp */
