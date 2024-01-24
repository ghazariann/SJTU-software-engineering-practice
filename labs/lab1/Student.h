#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Class;

enum Degree {
    undergraduate,
    graduate
};

class Student {
private:
    const string year;
    const string name;
    const enum Degree degree;

protected:
    vector<Class *> classes;
public:
    const string id;
    Student(const string &id, const string &name, const string &year, const Degree degree): 
    id(id), name(name), year(year), degree(degree){

    };
    // Student(Student &other) {
    // this->year = other.year;
    // this->name = other.name;
    // this->degree = other.degree;

    // };
    string toString() const;
    virtual double getGrade() const = 0;
    void addClass(Class* c);
};

class Undergraduate: public Student{
    public:
        Undergraduate(const string &id, const string &name, const string &year): 
        Student(id, name, year, graduate){};

        double getGrade() const;
};
class Graduate: public Student{
    public:
     Graduate(const string &id, const string &name, const string &year): 
        Student(id, name, year, graduate){};
        double getGrade() const;
};

class StudentWrapper{
private:
    const Student &student;
    double score = 0.0;
public:
    const std::string id;
    StudentWrapper(const string &id,  const Student &student): id(id), student(student) {
        // this->id = id;
        // this->student = student;
    }

    void setScore(double score)
    {
        if (score < 0 || score > 100)
            throw "Invalid Score!";
        this->score = score;
    }

    double getScore() const
    {
        return this->score;
    }

    std::string toString() const
    {
        return student.toString();
    }
};

#endif // STUDENT_H_
