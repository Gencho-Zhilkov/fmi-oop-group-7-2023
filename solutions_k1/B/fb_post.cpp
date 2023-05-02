#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>

#include "fb_post.hpp"


FacebookPost::FacebookPost(const char* description, const char* photoPath): reactions{} {
    if (strlen(description) > sizeof(this->description) - 1) {
        throw std::invalid_argument("description too long!");
    }
    if (strlen(photoPath) > sizeof(this->photoPath) - 1) {
        throw std::invalid_argument("photoPath too long!");
    }

    strcpy(this->description, description);
    strcpy(this->photoPath, photoPath);
}

void FacebookPost::addReaction(const size_t index) {
    if (index >= 7) {
        throw std::out_of_range("Reaction out of range!");
    }

    reactions[index]++;
}

unsigned FacebookPost::sumReactions() const {
    unsigned sum = 0;
    for (size_t i = 0; i < 7; i ++) {
        sum += reactions[i];
    }
    return sum;
}

void FacebookPost::printPost() const {
    std::cout << description << std::endl;
    std::cout << *this;

    std::cout << "Reactions: ";
    for (size_t i = 0; i < 7; i++) {
        std::cout << reactions[i] << ' ';
    }
    std::cout << std::endl;
}

std::ostream& operator <<(std::ostream& out, const FacebookPost& post) {
    std::ifstream fin(post.photoPath);
    if (!fin) {
        throw std::invalid_argument("Could not open file for reading!");
    }

    for(char c; fin.get(c);) {
        out << c;
    }

    // Close the file explicitely to make the professor happy
    fin.close();

    return out;
}
