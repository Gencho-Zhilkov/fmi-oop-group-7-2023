#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>

#include "student_record.hpp"
#include "int_vector.hpp"


const char *DATA_FILE = "student_records.data";


IntVector getStudentNotes(const char* studentId) {
	std::ifstream fin(DATA_FILE, std::ios::in | std::ios::binary);
	if (!fin) {
		throw std::invalid_argument("Could not open file for reading!");
	}

	IntVector grades;
	StudentRecord r;
	while (fin.read((char *)&r, sizeof(r))) {
		if (r.isStudent(studentId)) {
			grades.append(r.grade);
		}
	}

	return grades;
}

IntVector getCourseNotes(const char* courseId) {
	std::ifstream fin(DATA_FILE, std::ios::in | std::ios::binary);
	if (!fin) {
		throw std::invalid_argument("Could not open file for reading!");
	}

	IntVector grades;
	StudentRecord r;
	while (fin.read((char *)&r, sizeof(r))) {
		if (r.isCourse(courseId)) {
			grades.append(r.grade);
		}
	}

	return grades;
}

double average(const IntVector& grades) {
	int sum = 0;
	for(size_t i = 0; i < grades.size(); i++) {
		sum += grades.get(i);
	}
	return ((double)sum) / grades.size();
}

double getStudentAverage(const char* studentId) {
	return average(getStudentNotes(studentId));
}

double getCourseAverage(const char* courseId) {
	return average(getCourseNotes(courseId));
}


int main() {
	const char *studentId = "5MI0213977";
	const char *courseId = "CS321";

	try {
		std::cout << "Notes for student " << studentId << ": ";
		print(getStudentNotes(studentId));
		std::cout << "Avg. note for student " << studentId << ": "
				  << getStudentAverage(studentId) << std::endl;

		std::cout << "Notes for course " << courseId << ": ";
		print(getCourseNotes(courseId));
		std::cout << "Avg. note for course " << courseId << ": "
				  << getCourseAverage(courseId) << std::endl;
	} catch(std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
