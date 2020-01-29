/**
 * \file Group.hpp
 * \brief Objet qui contient un groupe de médias
 *
 */

#ifndef Group_h
#define Group_h

#include <iostream>
#include <stdio.h>
#include <memory>

#include <list>

#include "Multimedia.hpp"


class Group : public std::list<std::shared_ptr<Multimedia>> {
	
private:
	std::string groupName;
	
public:
	Group();
	Group(std::string groupName){
		this->groupName = groupName;
    }
	
    std::string getGroupName() const {return groupName;}
	
	~Group(){
		std::cout << "Group " << getGroupName() << " deleted\n\n";
    }
	
    /**
     * @brief Affiche les attributs d'un groupe, c'est-à-dire son nom ainsi que les attributs de ses éléments
     * @param f : le buffer vers lequel on envoie les données
     */
	void displayMedia(std::ostream& f) const{
		f << "Group name : " << groupName << std::endl;
		for (std::shared_ptr<Multimedia> media : *this)
		{
			media->displayMedia(f);
		}
    }
};

#endif /* Group_h */
