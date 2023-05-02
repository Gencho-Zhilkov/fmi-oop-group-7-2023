#ifndef FB_PROFILE_HPP
#define FB_PROFILE_HPP

#include "fb_post.hpp"


class FacebookProfile {
private:
    char *name;
    FacebookPost **posts;
    size_t numPosts;

    void copy(const FacebookProfile& that);
    void move(FacebookProfile&& that);
    void cleanup();

public:
    FacebookProfile(const char* name="", const size_t numPosts=1);
    FacebookProfile(const char* name, const char *file, const size_t numPosts);

    FacebookProfile(const FacebookProfile& other);
    FacebookProfile& operator=(const FacebookProfile& other);

    FacebookProfile(FacebookProfile&& other);
    FacebookProfile& operator=(FacebookProfile&& other);

    ~FacebookProfile();

    void addPostAtIndex(const FacebookPost& post, const size_t index);
    unsigned operator[](const size_t index) const;
    bool isEmpty(const size_t index) const;
};

#endif /* FB_PROFILE_HPP */
