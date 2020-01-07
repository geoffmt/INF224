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

/* Cette méthode est appelée chaque fois qu'il y a une requête à traiter.
 * Ca doit etre une methode de la classe qui gere les données, afin qu'elle
 * puisse y accéder.
 *
 * Arguments:
 * - 'request' contient la requête
 * - 'response' sert à indiquer la réponse qui sera renvoyée au client
 * - si la fonction renvoie false la connexion est close.
 *
 * Cette fonction peut etre appelée en parallele par plusieurs threads (il y a
 * un thread par client).
 *
 * Pour eviter les problemes de concurrence on peut créer un verrou en creant
 * une variable Lock **dans la pile** qui doit etre en mode WRITE (2e argument = true)
 * si la fonction modifie les donnees.*/
bool Table::processRequest(TCPConnection &cnx, const string &request, string &response){
	
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

