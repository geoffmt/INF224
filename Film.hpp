//
//  Film.hpp
//  Projet - INF224
//
//  Created by Geoff on 03/12/2019.
//  Copyright © 2019 Geoff. All rights reserved.
//

#ifndef Film_hpp
#define Film_hpp

#include <iostream>
#include <stdio.h>
#include "Video.hpp"

using namespace std;

class Film:public Video{
	
private:
	int numberOfChapters = 0;
	int * chapterLengths = nullptr;
	
	void setLength(float length) {
	  Video::setLength(length);
	}

	void copyLengths(const int * chapterLengths, int numberOfChapters) {
	  if (!chapterLengths) {
		this->chapterLengths = nullptr;
		setLength(0);
		return;
	  }

	  int length = 0;
	  this->chapterLengths = new int [numberOfChapters];
	  for (int i = 0; i<numberOfChapters; i++) {
		length += chapterLengths[i];
		(this->chapterLengths)[i] = chapterLengths[i];
	  }
	  setLength(length);
	}
	
public:
	Film();
	Film(string name, string pathname,int length, int numberOfChapters, int * chapterLengths):Video(name, pathname, 0){
		this->chapterLengths = chapterLengths;
		this->numberOfChapters = numberOfChapters;
		copyLengths(chapterLengths, numberOfChapters);
	}
	
	~Film() {	}
	
	const int * getChapterLengths() const {
		return chapterLengths;
	}
	
	int getNumberOfChapters() const {
		return numberOfChapters;
	}
	
	//Setters
	void setLengths(int numberOfChapters, int * lengths) {
		copyLengths(lengths, numberOfChapters);
	}
	
	void displayMedia(std::ostream& f) const override {
		f << "Name : " << getName() << ", "
		<< "Path : " << getPathname() << ", "
		<< "Length : " << getLength() << ", "
		<< "Number of chapters : " << getNumberOfChapters() << std::endl;
		f << "Chapters" << std::endl;
		for (int i=0; i<numberOfChapters; i++) {
			f << "Chapter " << i << " : " << chapterLengths[i] << std::endl;
			
		}
	}
	
};



#endif /* Film_hpp */
