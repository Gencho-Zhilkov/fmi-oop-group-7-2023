#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <cstring>

#include "student_record.hpp"


const char *DATA_FILE = "student_records.data";


std::vector<int> getStudentNotes(const char* studentId) {
	std::ifstream fin(DATA_FILE, std::ios::in | std::ios::binary);
	if (!fin) {
		throw std::invalid_argument("Could not open file for reading!");
	}

	std::vector<int> grades;
	StudentRecord r;
	while (fin.read((char *)&r, sizeof(r))) {
		if (r.isStudent(studentId)) {
			grades.push_back(r.grade);
		}
	}

	return grades;
}

std::vector<int> getCourseNotes(const char* courseId) {
	std::ifstream fin(DATA_FILE, std::ios::in | std::ios::binary);
	if (!fin) {
		throw std::invalid_argument("Could not open file for reading!");
	}

	std::vector<int> grades;
	StudentRecord r;
	while (fin.read((char *)&r, sizeof(r))) {
		if (r.isCourse(courseId)) {
			grades.push_back(r.grade);
		}
	}

	return grades;
}

double average(const std::vector<int>& grades) {
	int sum = 0;
	for(size_t i = 0; i < grades.size(); i++) {
		sum += grades[i];
	}
	return ((double)sum) / grades.size();
}

double getStudentAverage(const char* studentId) {
	return average(getStudentNotes(studentId));
}

double getCourseAverage(const char* courseId) {
	return average(getCourseNotes(courseId));
}

void printNotes(const std::vector<int> notes) {
	for (const int note: notes) {
		std::cout << note << " ";
	}
	std::cout << std::endl;
}

int main() {
	const char *studentId = "5MI0213977";
	const char *courseId = "CS321";

	try {
		std::cout << "Notes for student " << studentId << ": ";
		printNotes(getStudentNotes(studentId));
		std::cout << "Avg. note for student " << studentId << ": "
				  << getStudentAverage(studentId) << std::endl;

		std::cout << "Notes for course " << courseId << ": ";
		printNotes(getCourseNotes(courseId));
		std::cout << "Avg. note for course " << courseId << ": "
				  << getCourseAverage(courseId) << std::endl;
	} catch(std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
