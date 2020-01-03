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
	
	virtual ~Multimedia(){
		std::cout << "Media " << getName() << " deleted\n\n";
	} //destructeur
	
	string getName() const;
	string getPathname() const;
	virtual string getClassName() const {
		return "Multimedia";
	};
	
	void setType(string newName);
	void setPathname(string newPathname);
	
	/*
	 Affiche les attributs du média
	 */
	virtual void displayMedia (std::ostream&) const;
	
	/*
	 Joue le média
	 */
	virtual void playMedia() const {}
	
};
#endif /* Multimedia_hpp */
