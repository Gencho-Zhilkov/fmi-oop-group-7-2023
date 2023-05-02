#include <iostream>

#include "insta_post.hpp"
#include "insta_profile.hpp"


int main() {
	InstaProfile profile("Ivan Ivanov", 3);
	profile += InstaPost("Post 1", "../photo_1.txt");
	profile += InstaPost("Post 2", "../photo_2.txt");
	profile += InstaPost("Post 3", "../photo_3.txt");
	profile += InstaPost("Post 4", "../photo_2.txt");

	for (size_t i = 0; i < 3; i++) {
		InstaPost p = profile[i];
		for(size_t j = 0; j < i; j++) {
			p.like();
		}
		std::cout << p << std::endl;
	}

	return 0;
}
