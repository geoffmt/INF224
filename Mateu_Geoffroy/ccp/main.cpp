//
// main.cpp
// Created on 21/10/2018
//


#include <memory>
#include <string>
#include <iostream>
#include <sstream>



#include "Table.hpp"

const int PORT = 3333;


int main(int argc, const char* argv[])
{
	
	
	/** Test du displayMultimedia
	 Multimedia * multimedia = new Multimedia("welcome","tetech");
	 multimedia->displayMultimedia(cout);
	 */
	
	/**
	 Picture * picture = new Picture("test_photo.jpg","/Users/geoffhome/Documents/TPT/2A/inf224/ProjetINF224/ProjetINF224/test_photo.jpg",640,545);
		 
	 Video * video = new Video("movie","/Users/geoffhome/Documents/TPT/2A/inf224/ProjetINF224/ProjetINF224/test_video.m4v",100);
	 

	 Video * video2 = new Video("movie2","/Users/geoffhome/Documents/TPT/2A/inf224/ProjetINF224/ProjetINF224/test_video2.m4v",10);
		 
	  
	 
	 Multimedia ** multimedias = new Multimedia * [3];
	 multimedias[0] = video;
	 multimedias[1] = picture;
	 multimedias[2] = video2;
	 
	 for (int i=0;i<3;i++){
		 multimedias[i]->playMedia(); //polymorhpisme (a vérifier)
	 }
	 
	 */
	// cree le TCPServer
	shared_ptr<TCPServer> server(new TCPServer());
	
	// cree l'objet qui gère les données
	shared_ptr<Table> table(new Table());
	table->createPicture("dog", "/cal/homes/gmateu/inf224/Mateu_Geoffroy/ccp/test_photo.jpg", 640,545);
	table->createVideo("sample_video", "/cal/homes/gmateu/inf224/Mateu_Geoffroy/ccp/test_video.m4v", 100);
	table->serialize();
	table->saveSerialtoFile();
	//table->readSerialFile();

    // le serveur appelera cette méthode chaque fois qu'il y a une requête
	server->setCallback(*table, &Table::processRequest);
	
	// lance la boucle infinie du serveur
	cout << "Starting Server on port " << PORT << endl;
	int status = server->run(PORT);
	
    // en cas d'erreur
	if (status < 0) {
		cerr << "Could not start Server on port " << PORT << endl;
		return 1;
	}
	
	return 0;




	
	
}
