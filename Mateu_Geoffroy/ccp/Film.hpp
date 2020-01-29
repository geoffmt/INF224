/**
 * \file Film.hpp
 * \brief Objet qui contient un film
 *
 */

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
	
	~Film() {
		delete [] chapterLengths;
		std::cout << "Film " << getName() << " deleted\n\n";
	}
	
	string getClassName() const override{
		return "Film";
    }
	
	const int * getChapterLengths() const {
		return chapterLengths;
	}
	
	int getNumberOfChapters() const {
		return numberOfChapters;
	}
	
	void setLengths(int numberOfChapters, int * lengths) {
		copyLengths(lengths, numberOfChapters);
	}
	
    /**
     * @brief Affiche les attributs d'un film avec son nom, path, taille, nombre de chapitres ainsi que leurs noms
     * @param f : le buffer vers lequel on envoie les données
     */
	void displayMedia(std::ostream& f) const override {
		f << "Name : " << getName() << ", "
		<< "Path : " << getPathname() << ", "
		<< "Length : " << getLength() << ", "
		<< "Number of chapters : " << getNumberOfChapters();
		f << "Chapters" << std::endl;
		for (int i=0; i<numberOfChapters; i++) {
			f << "Chapter " << i << " : " << chapterLengths[i];
			
		}
	}
	
};



#endif /* Film_hpp */
