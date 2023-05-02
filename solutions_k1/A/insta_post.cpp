#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>

#include "insta_post.hpp"


void InstaPost::printPhoto(std::ostream& out) const {
	std::ifstream fin(photoPath);
	if (!fin) {
		throw std::invalid_argument("Could not open file for reading!");
	}

	for(char c; fin.get(c);) {
		out << c;
	}

	// Close the file explicitely to make the professor happy
	fin.close();
}

InstaPost::InstaPost(const char* description, const char* photoPath): likes{0} {
	if (strlen(description) > sizeof(this->description) - 1) {
		throw std::invalid_argument("description too long!");
	}
	if (strlen(photoPath) > sizeof(this->photoPath) - 1) {
		throw std::invalid_argument("photoPath too long!");
	}

	strcpy(this->description, description);
	strcpy(this->photoPath, photoPath);
}

std::ostream& operator <<(std::ostream& out, const InstaPost& post) {
	post.printPhoto(out);
	out << "Likes: " << post.likes << std::endl;
	out << "Desc.: " << post.description << std::endl;

	return out;
}
