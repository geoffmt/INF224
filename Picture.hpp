//
//  Picture.hpp
//  Projet - INF224
//
//  Created by Geoff on 26/11/2019.
//  Copyright © 2019 Geoff. All rights reserved.
//

#ifndef Picture_hpp
#define Picture_hpp

#include <iostream>
#include <stdio.h>
#include "Multimedia.hpp"

using namespace std;

class Picture : public Multimedia {
	
private:
	float latitude;
	float longitude;
	
public:
	Picture();
	Picture(string name, string pathname, float latitude, float longitude):Multimedia(name,  pathname){
		this->latitude = latitude;
		this->longitude = longitude;
	}
	

	
	float getLatitude() const {return latitude;};
	float getLongitude() const {return longitude;};
	
	void setLatitude(int newLatitude){this->latitude = newLatitude;};
	void setLongitude(int newLongitude){this->longitude = newLongitude;};
	
	void displayMedia(std::ostream& f) const override {
			f << "Name : " << getName() << ", "
			<< "Path : " << getPathname() << ", "
			<< "Latitude : " << getLatitude() << ", "
			<< "Longitude : " << getLongitude() << std::endl;
		};
		
	void playMedia() const override {
		string cmd = "imagej " + this->getPathname() + "&";
		system(cmd.c_str());
	};
	
	
};

#endif /* Picture_hpp */
