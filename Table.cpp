//
//  Table.cpp
//  Projet - INF224
//
//  Created by Geoff on 03/01/2020.
//  Copyright © 2020 Geoff. All rights reserved.
//

#include "Table.hpp"


/*
 Si j'enleve un groupe : OK
 Si j'enleve un media, je dois aussi l'enlever du (ou des) groupe qui le contient
 et lorsqu'on supprime un objet multimédia il faut d'abord l'enlever de tous les groupes dans lesquels il figure.
 */
void Table::remove(std::string name){
	
	auto it_g = groupMap.find(name);
	if (it_g != groupMap.end()) {
		groupMap.erase(it_g);
		return;
	}
	
	auto it_m = multimediaMap.find(name);
	if (it_m != multimediaMap.end()) {
		for (auto& i : groupMap) {
			GroupPtr group = i.second;
			for (std::shared_ptr<Multimedia> media : *group){
				if(media->getName() == name){
					group->remove(media);
				}
			}
		}
		multimediaMap.erase(it_m);
		return;
	}
	
}
