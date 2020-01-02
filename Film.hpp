//
//  Film.hpp
//  Projet - INF224
//
//  Created by Geoff on 03/12/2019.
//  Copyright © 2019 Geoff. All rights reserved.
//

#ifndef Film_hpp
#define Film_hpp

#include <iostream>
#include <stdio.h>
#include "Video.hpp"

using namespace std;

class Film:public Video{
	
private:
	float latitude;
	float longitude;
	
public:
	Film();
	Film(string name, string pathname, float latitude, float longitude):Multimedia(name, pathname){
		this->latitude = latitude;
		this->longitude = longitude;
	}
};

#endif /* Film_hpp */
