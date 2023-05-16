#include <iostream>
#include <stdexcept>
#include <cassert>
#include <cstring>
#include <string>


class Cypher {
protected:
	static size_t indexOf(const char c) {
		assert('A' <= c && c <= 'Z');
		return c - 'A';
	}

public:
	static const size_t AlphabetSize = 'Z' - 'A' + 1;

	virtual char encrypt(const char c) = 0;
	virtual ~Cypher() {}
};


class CeaserCypher: public Cypher {
private:
	size_t offset;

	static char enc(const char c, const size_t offset) {
		return 'A' + (indexOf(c) + offset) % AlphabetSize;
	}

public:
	CeaserCypher(const size_t offset) {
		setOffset(offset);
	}

	size_t getOffset() const {
		return offset;
	}

	void setOffset(const size_t offset) {
		this->offset = offset % AlphabetSize;
	}

	char encrypt(const char c) override {
		return enc(c, offset);
	}

	char decrypt(const char c) {
		return enc(c, AlphabetSize - offset);
	}
};


class PermutationCypher: public Cypher {
protected:
	char letters[AlphabetSize];

public:
	PermutationCypher(const char* letters) {
		if (strlen(letters) != AlphabetSize) {
			throw std::invalid_argument("letters must be 26 characters!");
		}

		for (size_t i = 0; i < AlphabetSize; i++) {
			this->letters[i] = letters[i];
		}
	}

	char encrypt(const char c) override {
		return letters[indexOf(c)];
	}
};

class Reflector: public PermutationCypher {
private:
	static const char* getPerm(const std::string& config) {
		if (config == "UKW-A") {
			return "EJMZALYXVBWFCRQUONTSPIKHGD";
		} else if (config == "UKW-B") {
			return "YRUHQSLDPXNGOKMIEBFZCWVJAT";
		} else if (config == "UKW-C") {
			return "FVPJIAOYEDRZXWGCTKUQSBNMHL";
		} else {
			throw std::invalid_argument("Invalid Reflector config!");
		}
	}

public:
	Reflector(const std::string& config):
		PermutationCypher(getPerm(config)) {}
};

class Plugboard: public PermutationCypher {
public:
	Plugboard():
		PermutationCypher("ABCDEFGHIJKLMNOPQRSTUVWXYZ") {}

	void connect(const char a, const char b) {
		if (letters[indexOf(a)] != a) {
			throw std::invalid_argument("a already plugged");
		}
		if (letters[indexOf(b)] != b) {
			throw std::invalid_argument("b already plugged");
		}

		letters[indexOf(a)] = b;
		letters[indexOf(b)] = a;
	}
};


class Rotator: public Cypher {
private:
	CeaserCypher caesar;
	PermutationCypher perm;

	static const char* getPerm(const std::string& type) {
		if(type == "I") {
			return "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
		} else if(type == "II") {
			return "AJDKSIRUXBLHWTMCQGZNPYFVOE";
		} else if(type == "III") {
			return "BDFHJLCPRTXVZNYEIWGAKMUSQO";
		} else if(type == "IV") {
			return "ESOVPZJAYQUIRHXLNFTGKDCMWB";
		} else if(type == "V") {
			return "VZBRGITYUPSDNHLXAWMJQOFECK";
		} else {
			throw std::invalid_argument("Invalid Rotator type!");
		}
	}

public:
	Rotator(const std::string& type, const size_t offset):
		caesar(offset), perm(getPerm(type)) {}
	char encrypt(const char c) override {
		char res = caesar.encrypt(c);
		res = perm.encrypt(res);
		res = caesar.decrypt(res);
		step();
		return res;
	}

	void step() {
		const size_t offset = caesar.getOffset();
		caesar.setOffset(offset + 1);
	}
};


int main() {
	CeaserCypher s(3);
	for (char c: std::string("ABCDXYZ")) {
		std::cout << c << " -> " << s.encrypt(c) << std::endl;
	}
	return 0;
}
