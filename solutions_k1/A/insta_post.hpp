#ifndef INSTA_POST_HPP
#define INSTA_POST_HPP

#include <iostream>


class InstaPost {
private:
	char description[1025];	// 1024 + '\0'
	unsigned likes;
	char photoPath[65];		// 64 + '\0'

	void printPhoto(std::ostream& out) const;

	friend std::ostream& operator <<(std::ostream& out, const InstaPost& post);

public:
	// Not necessary, added for ease of testing.
	InstaPost() = default;
	InstaPost(const char* description, const char* photoPath);

	void printPhoto() const {
		printPhoto(std::cout);
	}

	void like() {
		likes++;
	}
};

std::ostream& operator <<(std::ostream& out, const InstaPost& post);

#endif /* INSTA_POST_HPP */
