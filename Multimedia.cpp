//
//  Multimedia.cpp
//  Projet - INF224
//
//  Created by Geoff on 26/11/2019.
//  Copyright © 2019 Geoff. All rights reserved.
//


#include "Multimedia.hpp"


Multimedia::Multimedia(string _name, string _pathname){
	name = _name;
	pathname = _pathname;
}

string Multimedia::getName() const {return name;};
string Multimedia::getPathname() const {return pathname;};

void Multimedia::setType(string newName){name = newName;};
void Multimedia::setPathname(string newPathname){pathname = newPathname;};

void Multimedia::displayMedia (std::ostream & f) const {
	f << "Name : " << getName() << ", "
	<< "Path : " << getPathname() << std::endl;
};
