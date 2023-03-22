#include <iostream>
#include <stdexcept>
#include <cassert>
#include <string>


bool checkBrackets(const std::string& str) {
	std::string brackets;
	for (const char c: str) {
		switch(c) {
		case '(':
			brackets.push_back(')');
			break;
		case '[':
			brackets.push_back(']');
			break;
		case '{':
			brackets.push_back('}');
			break;
		case ')':
		case ']':
		case '}':
			if (brackets.empty() || brackets.back() != c) {
				return false;
			}
			brackets.pop_back();
			break;
		}
	}
	return brackets.empty();
}


int main() {
	std::cout << std::boolalpha;
	for (const char* s: {
		"", "(", "[", "{", ")", "]", "}",
		"()", "[]", "{}",
		"{()}", "{(})",
		"[[[]](){}{{{()}}[]}]",
	}) {
		std::cout << '"' << s << "\" -> " << checkBrackets(s) << std::endl;
	}

	return 0;
}
