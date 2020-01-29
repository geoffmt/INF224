/**
 * \file Picture.hpp
 * \brief Objet qui contient une image
 *
 */

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
	

	
    float getLatitude() const {return latitude;}
    float getLongitude() const {return longitude;}
	string getClassName() const override {
		return "Picture";
    }
	
    void setLatitude(int newLatitude){this->latitude = newLatitude;}
    void setLongitude(int newLongitude){this->longitude = newLongitude;}
	
    /**
     * @brief Affiche les attributs d'une image : son nom, path, largeur, longueur
     * @param f : le buffer vers lequel on envoie les données
     */
	void displayMedia(std::ostream& f) const override {
			f << "Name : " << getName() << ", "
			<< "Path : " << getPathname() << ", "
			<< "Latitude : " << getLatitude() << ", "
			<< "Longitude : " << getLongitude();
        }
		
    /**
     * @brief Affiche l'image avec imagej
     */
	void playMedia() const override {
		string cmd = "imagej " + this->getPathname() + "&";
		system(cmd.c_str());
    }
	
	
};

#endif /* Picture_hpp */
