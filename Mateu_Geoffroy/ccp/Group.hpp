//
//  Group.hpp
//  ProjetINF224
//
//  Created by Geoff on 02/01/2020.
//  Copyright © 2020 Geoff. All rights reserved.
//

#ifndef Group_h
#define Group_h

#include <iostream>
#include <stdio.h>

#include <list>


class Group : public std::list<std::shared_ptr<Multimedia>> {
	
private:
	std::string groupName;
	
public:
	Group();
	Group(std::string groupName){
		this->groupName = groupName;
	};
	
	std::string getGroupName() const {return groupName;};
	
	~Group(){
		std::cout << "Group " << getGroupName() << " deleted\n\n";
	};
	
	void displayMedia(std::ostream& f) const{
		f << "Group name : " << groupName << std::endl;
		for (std::shared_ptr<Multimedia> media : *this)
		{
			media->displayMedia(f);
		}
	};
};

#endif /* Group_h */
