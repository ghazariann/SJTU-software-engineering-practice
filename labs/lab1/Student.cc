#include "Student.h"

#include <iostream>
#include <sstream>
#include <string>

#include "Class.h"
using namespace std;

string Student::toString() const {
    ostringstream oss;
    oss << "Student Information:"
        << "\n\tid: " << id
        << "\n\tname: " << name
        << "\n\tenrollment year: " << year
        << "\n\tdegree: " << (degree == graduate ? "graduate" : "undergraduate")
        << endl;
    return oss.str();
}

void Student::addClass(Class *c) {
    classes.push_back(c);
};

double Undergraduate::getGrade() const {
    double gpa = 0;
    double allPoints = 0;
    for (const auto &c : classes) {
        gpa += c->getStudentWrapper(this->id).getScore() * (c->point) / 20;
        allPoints += c->point;
    }
    return gpa / allPoints;
};

double Graduate::getGrade() const {
    double gpa = 0;
    double allPoints = 0;
    double score;
    for (const auto &c : classes) {
        double point = c->point;
        score = c->getStudentWrapper(this->id).getScore();
        allPoints += point;
        if (score >= 90) {
            gpa += 4.0 * point;
        } else if (score >= 80 && score < 90) {
            gpa += 3.5 * point;
        } else if (score >= 70 && score < 80) {
            gpa += 3.0 * point;
        } else if (score >= 60 && score < 70) {
            gpa += 2.5 * point;
        } else {
            gpa += 2.0 * point;
        }
    }
    return gpa / allPoints;
};
