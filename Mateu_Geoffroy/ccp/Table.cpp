//
//  Table.cpp
//  Projet - INF224
//
//  Created by Geoff on 03/01/2020.
//  Copyright © 2020 Geoff. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <exception>
#include "Table.hpp"
using namespace cppu;
using namespace std;


/*
 Si j'enleve un groupe : OK
 Si j'enleve un media, je dois aussi l'enlever du (ou des) groupe qui le contient
 et lorsqu'on supprime un objet multimédia il faut d'abord l'enlever de tous les groupes dans lesquels il figure.
 */
void Table::remove(std::string name){
	
	try{
		if (multimediaMap.count(name)>0){
			throw "This unexisting group cannot be erased!";
		}
	} catch (const char* e) {
		cerr << e << endl;
	}
	auto it_g = groupMap.find(name);
	if (it_g != groupMap.end()) {
		groupMap.erase(it_g);
		return;
	}
	
	try{
		if (!multimediaMap.count(name)){
			throw "This unexisting media cannot be erased!";
		}
	} catch (const char* e) {
		cerr << e << endl;
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


bool Table::processRequest(TCPConnection &cnx, const string &request, 
string &response){
	
	cerr << "\nRequest: '" << request << "'" << endl;
	
	/*
	 Parsing the request
	 */
	
	std::string action, name;
	std::stringstream str = std::stringstream(request);
	 //insertion de la requête
	str >> action; //on extrait jusqu'au premier espace l'action
	str >> name;
	
	
	
	/*
	 Traitement
	 */
	
	
	stringbuf buffer = stringbuf();
	ostream os(&buffer);

	GroupPtr group;
	
	if (action == "search")
	{
		TCPLock lock(cnx);
		
		try {
			group = findGroup(name);
		} catch (out_of_range const& e){

		}
        if (!group.get())
		{
			try{
				MultimediaPtr media = findMultimedia(name);
			} catch(out_of_range const& e){
                response = "L'élément que vous cherchez n'est pas dans la base de donnée";
				return true;
			}
			displayMultimedia(name, os);
			
		}
		else {displayGroup(name, os);}
		
		response = buffer.str();
		return true;
	}
	if (action == "play")
	{
		TCPLock lock(cnx);
		
		MultimediaPtr media;
		media = findMultimedia(name);
		media->playMedia();
		
		response = "Playing " + name + " on server";
		return true;
	}
	
	
	response = "OK: " + request;
	cerr << "response: " << response << endl;
	
	// renvoyer false si on veut clore la connexion avec le client
	return true;
}

