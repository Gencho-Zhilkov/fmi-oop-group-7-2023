#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>

#include "insta_profile.hpp"


// Private helper functions (copy, move, and cleanup)
void InstaProfile::copy(const InstaProfile& that) {
	username = new char[strlen(that.username) + 1];
	strcpy(username, that.username);

	numPosts = that.numPosts;
	posts = new InstaPost*[numPosts];
	for (size_t i = 0; i < numPosts; i ++) {
		posts[i] = that.isEmpty(i) ?
			nullptr :
			new InstaPost{*that.posts[i]};
	}
}

void InstaProfile::move(InstaProfile&& that) {
	username = that.username;
	numPosts = that.numPosts;
	posts = that.posts;

	that.username = nullptr;
	that.numPosts = 0;
	that.posts = nullptr;
}

void InstaProfile::cleanup() {
	delete[] username;
	for (size_t i = 0; i < numPosts; i ++) {
		delete posts[i];
	}
	delete[] posts;
}


// Canonical representation and move semantics
InstaProfile::InstaProfile(const char* username, const size_t numPosts):
	numPosts{numPosts} {
	this->username = new char[strlen(username) + 1];
	strcpy(this->username, username);

	// Use `()` to set all elements to `nullptr`
	posts = new InstaPost*[numPosts]();
}

InstaProfile::InstaProfile(const InstaProfile& that) {
	copy(that);
}

InstaProfile& InstaProfile::operator =(const InstaProfile& that) {
	if (this != &that) {
		cleanup();
		copy(that);
	}
	return *this;
}

InstaProfile::InstaProfile(InstaProfile&& that) {
	move(std::move(that));
}

InstaProfile& InstaProfile::operator =(InstaProfile&& that) {
	if (this != &that) {
		cleanup();
		move(std::move(that));
	}
	return *this;
}

InstaProfile::~InstaProfile() {
	cleanup();
}


// Constructor from binary file
InstaProfile::InstaProfile(const char* username, const char *file, const size_t numPosts):
	numPosts(numPosts) {
	this->username = new char[strlen(username) + 1];
	strcpy(this->username, username);

	posts = new InstaPost*[numPosts];

	// Read posts from binary file
	std::ifstream fin(file, std::ios::binary | std::ios::in);
	if (!fin) {
		throw std::invalid_argument("Could not open file for reading!");
	}

	InstaPost post;
	size_t index = 0;
	while (fin.read((char*)&post, sizeof(post))) {
		if (index == numPosts) {
			std::cerr << "Not enough space for all posts!" << std::endl;
			break;
		}
		posts[index] = new InstaPost{post};
		index++;
	}

	// Close the file explicitely to make the professor happy
	fin.close();

	// If we have additional slots, mark them as empty
	for (; index < numPosts; index++) {
		posts[index] = nullptr;
	}
}


// Other methods
InstaProfile& InstaProfile::operator +=(const InstaPost& post) {
	for (size_t i = 0; i < numPosts; i ++) {
		if (isEmpty(i)) {
			posts[i] = new InstaPost{post};
			return *this;
		}
	}

	// If we're here it means there are no free slots => Override last one.
	*posts[numPosts - 1] = post;
	return *this;
}

InstaPost InstaProfile::operator [](const size_t pos) const {
	// No need for explicit range check since done by `isEmpty`
	if (isEmpty(pos)) {
		throw std::runtime_error("Empty position!");
	}

	return *posts[pos];
}

bool InstaProfile::isEmpty(const size_t pos) const {
	if (pos >= numPosts) {
		throw std::out_of_range("Position out of range!");
	}

	return posts[pos] == nullptr;
}
