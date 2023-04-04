#ifndef FMI_OOP_STUDENT_RECORD_HPP
#define FMI_OOP_STUDENT_RECORD_HPP


struct StudentRecord {
	char studentId[10];
	char courseId[6];
	int grade;

	bool isStudent(const char* studentId) const {
		return strncmp(studentId, this->studentId, 10) == 0;
	}

	bool isCourse(const char* courseId) const {
		return strncmp(courseId, this->courseId, 6) == 0;
	}
};

#endif /* FMI_OOP_STUDENT_RECORD_HPP */
