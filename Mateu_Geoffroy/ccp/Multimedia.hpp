/**
 * \file Multimedia.hpp
 * \brief Objet qui contient un média
 *
 */

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
	
    /**
     * @brief Affiche les attributs d'un média
     * @param f : le buffer vers lequel on envoie les données
     */
	virtual void displayMedia (std::ostream&) const;
	
    /**
     * @brief Joue le média

     */
	virtual void playMedia() const = 0;
	
};
#endif /* Multimedia_hpp */
