/**
 * \file Video.hpp
 * \brief Objet qui contient une vidéo
 *
 */

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
	
	
    int getLength() const {return length;}
	virtual string getClassName() const override{
		return "Video";
    }
	
    void setLength(int newLength){this->length = newLength;}
	
    /**
     * @brief Affiche les attributs d'une vidéo : son nom, path, durée
     * @param f : le buffer vers lequel on envoie les données
     */
	virtual void displayMedia(std::ostream& f) const override {
		f << "Name : " << getName() << ", "
		<< "Path : " << getPathname() << ", "
		<< "Length : " << getLength() << ", ";
    }

    /**
     * @brief Joue la vidéo avec mpv
     */
	virtual void playMedia() const override {
		string cmd = "mpv " + this->getPathname()  + "&";
		system(cmd.c_str());
    }

};

#endif /* Video_hpp */
