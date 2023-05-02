#ifndef INSTA_PROFILE_HPP
#define INSTA_PROFILE_HPP

#include "insta_post.hpp"


class InstaProfile {
private:
	char *username;
	InstaPost **posts;
	size_t numPosts;

	void copy(const InstaProfile& that);
	void move(InstaProfile&& that);
	void cleanup();

public:
	// For easy testing
	InstaProfile(const char* username="", const size_t numPosts=1);
	InstaProfile(const char* username, const char *file, const size_t numPosts);

	InstaProfile(const InstaProfile& that);
	InstaProfile& operator =(const InstaProfile& that);

	InstaProfile(InstaProfile&& that);
	InstaProfile& operator =(InstaProfile&& that);

	~InstaProfile();

	InstaProfile& operator +=(const InstaPost& post);
	InstaPost operator [](const size_t pos) const;

	bool isEmpty(const size_t pos) const;
};

#endif /* INSTA_PROFILE_HPP */
