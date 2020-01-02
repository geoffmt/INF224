//
// main.cpp
// Created on 21/10/2018
//


#include <iostream>
using namespace std;

#include "Multimedia.hpp"
#include "Video.hpp"
#include "Picture.hpp"


int main(int argc, const char* argv[])
{
	/** Test du displayMultimedia
	 Multimedia * multimedia = new Multimedia("welcome","tetech");
	 multimedia->displayMultimedia(cout);
	 */
	
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
	
	
	
}
