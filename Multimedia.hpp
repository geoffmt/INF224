//
//  Multimedia.hpp
//  Projet - INF224
//
//  Created by Geoff on 26/11/2019.
//  Copyright © 2019 Geoff. All rights reserved.
//


#ifndef Multimedia_hpp
#define Multimedia_hpp

#include <iostream>
#include <stdio.h>
using namespace std;

class Multimedia {

private:
	string name; //nom de l'objet multimédia
	string pathname; //chemin complet
	
public:
	Multimedia();
	Multimedia(string name, string pathname);
	
	virtual ~Multimedia(){} //destructeur
	
	string getName() const;
	string getPathname() const;
	
	void setType(string newName);
	void setPathname(string newPathname);
	
	void displayMultimedia (std::ostream & f);
	
	virtual void playMedia() const {}
	
};
#endif /* Multimedia_hpp */