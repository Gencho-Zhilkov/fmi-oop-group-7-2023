#include <iostream>

#include "fb_post.hpp"
#include "fb_profile.hpp"


int main() {
	FacebookProfile profile("Ivan Ivanov", 3);

	FacebookPost p1{"Post 1", "../photo_1.txt"};
	p1.addReaction(0);
	p1.printPost();
	profile.addPostAtIndex(p1, 0);

	FacebookPost p2{"Post 2", "../photo_2.txt"};
	p2.addReaction(0);
	p2.addReaction(1);
	p2.printPost();
	profile.addPostAtIndex(p2, 1);

	FacebookPost p3{"Post 3", "../photo_3.txt"};
	p3.addReaction(0);
	p3.addReaction(1);
	p3.addReaction(2);
	p3.printPost();
	profile.addPostAtIndex(p3, 2);

	for (size_t i = 0; i < 3; i++) {
		std::cout << profile[i] << std::endl;
	}
	return 0;
}
