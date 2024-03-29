#include "Class.h"

#include <string>

#include "Student.h"

void Class::addStudent(const Student &st) {
    StudentWrapper sw(st.id, st);
    students.push_back(sw);
}

StudentWrapper &Class::getStudentWrapper(const std::string &studentId) {
    for (std::vector<StudentWrapper>::iterator it = students.begin(); it != students.end(); ++it) {
        if (it->id == studentId)
            return *it;
    }
    throw "No matching student!";
}

double Class::getAvgScore() {
    double avg_score = 0;
    for (std::vector<StudentWrapper>::iterator it = students.begin(); it != students.end(); ++it) {
        avg_score += it->getScore();
    }
    return avg_score / students.size();
}
