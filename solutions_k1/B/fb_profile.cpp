#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>

#include "fb_profile.hpp"


// Private helper functions (copy, move, and cleanup)
void FacebookProfile::copy(const FacebookProfile& other) {
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	numPosts = other.numPosts;
	posts = new FacebookPost*[numPosts];
	for (size_t i = 0; i < numPosts; i ++) {
		posts[i] = other.isEmpty(i) ?
			nullptr :
			new FacebookPost{*other.posts[i]};
	}
}

void FacebookProfile::move(FacebookProfile&& other) {
	name = other.name;
	numPosts = other.numPosts;
	posts = other.posts;

	other.name = nullptr;
	other.numPosts = 0;
	other.posts = nullptr;
}

void FacebookProfile::cleanup() {
	delete[] name;
	for (size_t i = 0; i < numPosts; i ++) {
		delete posts[i];
	}
	delete[] posts;
}


// Canonical representation + move semantics
FacebookProfile::FacebookProfile(const char* name, const size_t numPosts):
	numPosts{numPosts} {

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);

	// Use `()` to set all elements to `nullptr`
	posts = new FacebookPost*[numPosts]();
}

FacebookProfile::FacebookProfile(const FacebookProfile& other) {
	copy(other);
}

FacebookProfile& FacebookProfile::operator =(const FacebookProfile& other) {
	if (this != &other) {
		cleanup();
		copy(other);
	}
	return *this;
}

FacebookProfile::FacebookProfile(FacebookProfile&& other) {
	move(std::move(other));
}

FacebookProfile& FacebookProfile::operator =(FacebookProfile&& other) {
	if (this != &other) {
		cleanup();
		move(std::move(other));
	}
	return *this;
}

FacebookProfile::~FacebookProfile() {
	cleanup();
}


// Constructor from binary file.
FacebookProfile::FacebookProfile(const char* name, const char *file, const size_t numPosts):
	numPosts(numPosts) {
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);

	posts = new FacebookPost*[numPosts];

	// Read posts from binary file
	std::ifstream fin(file, std::ios::binary | std::ios::in);
	if (!fin) {
		throw std::invalid_argument("Could not open file for reading!");
	}

	FacebookPost post;
	size_t index = 0;
	while (fin.read((char*)&post, sizeof(post))) {
		if (index == numPosts) {
			std::cerr << "Not enough space for all posts!" << std::endl;
			break;
		}
		posts[index] = new FacebookPost{post};
		index++;
	}

	// Close the file explicitely to make the professor happy
	fin.close();

	// If we have additional places, mark them as empty
	for (; index < numPosts; index++) {
		posts[index] = nullptr;
	}
}


// Other methods
void FacebookProfile::addPostAtIndex(const FacebookPost& post, const size_t index) {
	// No need for explicit range check since done by `isEmpty`
	if (isEmpty(index)) {
		posts[index] = new FacebookPost{post};
	} else {
		*posts[index] = post;
	}
}

unsigned FacebookProfile::operator [](const size_t index) const {
	// No need for explicit range check since done by `isEmpty`
	if (isEmpty(index)) {
		throw std::runtime_error("Empty position!");
	}

	return posts[index]->sumReactions();
}

bool FacebookProfile::isEmpty(const size_t index) const {
	if (index >= numPosts) {
		throw std::out_of_range("Position out of range!");
	}

	return posts[index] == nullptr;
}
