#include <iostream>
#include <vector>
#include <string>
#include <cctype>


// Помощни функции
template <typename T>
std::ostream& operator <<(std::ostream& out, const std::vector<T>& vec) {
    out << "{ ";
    for (const T& elem : vec) {
        out << elem << ", ";
    }
    out << '}';
    return out;
}

template <typename T>
bool find(const std::vector<T>& vec, const T& val) {
    for (const T& elem : vec) {
        if (elem == val) {
            return true;
        }
    }

    return false;
}

template <typename T>
std::vector<T> unique(const std::vector<T> vec) {
    std::vector<T> res;

    for (const T& elem : vec) {
        if (!find(res, elem)) {
            res.push_back(elem);
        }
    }

    return res;
}


// Задача 1. Обединение на два вектора
template <typename T>
std::vector<T> vectUnion(const std::vector<T>& v1, const std::vector<T>& v2) {
    // Инициализираме резултата като копие на v1
    std::vector<T> res{v1};

    // Добавяме елементите от втория вектор, ако не са вече добавени
    for (const T& elem : v2) {
        if (!find(v1, elem)) {
            res.push_back(elem);
        }
    }

    return res;
}


// Задача 2. Сечение на два вектора
template <typename T>
std::vector<T> vectIntersect(const std::vector<T>& v1, const std::vector<T>& v2) {
    // Инициализираме резултата като копие на v1
    std::vector<T> res;

    // Добавяме елементите от първия вектор, които са и във втория
    for (const T& elem : v1) {
        if (find(v2, elem)) {
            res.push_back(elem);
        }
    }

    return res;
}


// Задача 3.
std::string longestCommonPrefix(const std::string& str1, const std::string& str2) {
    std::string res = "";
    const size_t minLength = std::min(str1.size(), str2.size());

    for (size_t i = 0; i < minLength; i++) {
        if (str1[i] == str2[i]) {
            res += str1[i];
        } else {
            break;
        }
    }

    return res;
}


// Задача 4.
std::string replaceChar(std::string str, char oldChar, char newChar) {
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == oldChar) {
            str[i] = newChar;
        }
    }
    return str;
}


// Задача 5.
std::vector<std::string> splitWords(const std::string& text) {
    std::vector<std::string> words;
    std::string word;

    for (const char c : text) {
        if (isalpha(c)) {
            word += c;
        } else if (!word.empty()) {
            words.push_back(word);
            word.clear();
        }
    }

    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}

// Бонус: неповтарящи се думи
std::vector<std::string> uniqueWords(const std::string& text) {
    return unique(splitWords(text));
}


// main функция с примерни извиквания
int main() {
    // Зад 1 и 2.
    const std::vector<int> v1{1, 2, 3, 4, 5};
    const std::vector<int> v2{4, 5, 6, 7, 8};
    const std::vector<int> u = vectUnion(v1, v2);
    const std::vector<int> i = vectIntersect(v1, v2);
    std::cout << v1 << " \\/ " << v2 << " = " << u << std::endl;
    std::cout << v1 << " /\\ " << v2 << " = " << i << std::endl;

    // Зад 3.
    const std::string str1 = "hello";
    const std::string str2 = "heaven";
    const std::string lcp = longestCommonPrefix(str1, str2);
    std::cout << "The longest common prefix of \"" << str1 << "\" and \""
              << str2 << "\" is \"" << lcp << '"' << std::endl;

    // Зад 4.
    const std::string s1 = "Hello world";
    std::cout << s1 << " => " << replaceChar(s1, 'o', 'a') << std::endl;

    // Зад 5.
    const std::string text = "Hello, world!\nThis is a\ttest. Goodbye, world.";
    std::cout << text << " => " << splitWords(text) << std::endl;
    // Бонус.
    std::cout << text << " => " << uniqueWords(text) << std::endl;

    return 0;
}


