#ifndef FB_POST_HPP
#define FB_POST_HPP

#include <iostream>

class FacebookPost {
private:
    unsigned reactions[7];
    char description[1025];	// 1024 + '\0'
    char photoPath[33];		// 32 + '\0'

    friend std::ostream& operator <<(std::ostream& out, const FacebookPost& post);

public:
    // Not necessary, added for ease of testing.
    FacebookPost() = default;
    FacebookPost(const char* description, const char* photoPath);

    void addReaction(const size_t index);
    unsigned sumReactions() const;
    void printPost() const;
};

#endif /* FB_POST_HPP */
