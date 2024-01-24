#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include "Class.h"
#include "Student.h"

using namespace std;

class AppX {
   private:
    vector<Student *> studentVec;
    vector<Class *> classVec;

    void loadFiles();
    void inputScore();
    void printAvgScore();
    void printGpa();

   public:
    AppX();
    ~AppX();
    int run();
};

AppX::~AppX() {
    // You can use the traditional loop, which is more clear.
    for (vector<Class *>::iterator it = classVec.begin();
         it != classVec.end();
         ++it) {
        if (*it) delete (*it);
    }
    // You can use modern and simpler loops only if you know what it is doing.
    for (const auto &s : studentVec) {
        if (s) delete (s);
    }
}

AppX::AppX() {
    loadFiles();
}

void AppX::loadFiles() {
    string line;
    size_t pos1, pos2;
    vector<string> bufv;
    Student *st = nullptr;
    string clsname;
    int point;
    Class *cl = nullptr;

    // Open a file as a input stream.
    ifstream stfile("./Students.txt");
    while (getline(stfile, line)) {
        if (line.empty())  // It's an empty line.
            continue;
        if (line[0] == '#')  // It's a comment line.
            continue;

        // The bufv vector stores each columnes in the line.
        bufv.clear();
        // Split the line into columes.
        //   pos1: begining the the column.
        //   pos2: end of the column.
        pos1 = 0;
        while (true) {
            pos2 = line.find(';', pos1 + 1);
            if (pos2 == string::npos) {  // No more columns.
                // Save the last column (pos1 ~ eol).
                bufv.push_back(line.substr(pos1, string::npos));
                break;
            } else {
                // Save the column (pos1 ~ pos2).
                bufv.push_back(line.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + 1;
        }

        if (bufv[3] == "U")
            st = new Undergraduate(bufv[0], bufv[1], bufv[2]);
        else
            st = new Graduate(bufv[0], bufv[1], bufv[2]);

        studentVec.push_back(st);
    }
    stfile.close();

    ifstream clfile("./Classes.txt");
    clsname = "";
    point = 0;
    while (getline(clfile, line)) {
        if (line[0] == '#')  // It's a comment line.
            continue;
        bufv.clear();

        if (line.find("Class:") != string::npos)
            clsname = line.substr(line.find(":") + 1, string::npos);
        else if (line.find("Points:") != string::npos)
            point = stoi(line.substr(line.find(":") + 1, string::npos));

        if (clsname != "" && point != 0) {
            cl = new Class(clsname, point);
            while (getline(clfile, line)) {
                if (line.empty()) {
                    clsname = "";
                    point = 0;
                    break;
                }
                for (const auto &s : studentVec) {
                    if (s->id == line) {
                        s->addClass(cl);
                        cl->addStudent(*s);
                        break;
                    }
                }
            }
            classVec.push_back(cl);
        }
    }
    clfile.close();
}

void AppX::inputScore() {
    string className;
    string studentId;
    Class *cl = nullptr;
    string scoreStr;
    double score;
    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> className;
        if (className == "q")
            break;
        for (const auto &c : classVec) {
            if (className == c->name) {
                cl = c;
                break;
            }
        }
        if (cl == nullptr) {
            cout << "No match class!" << endl;
            continue;
        }

        while (true) {
            cout << "Please input the student id (or input q to quit): ";
            cin >> studentId;
            if (studentId == "q")
                break;
            cout << "please input the score: ";
            cin >> scoreStr;
            try {
                if (scoreStr[0] < '0' || scoreStr[0] > '9')
                    throw "Invalid Score!";
                else
                    score = stod(scoreStr);
                cl->getStudentWrapper(studentId).setScore(score);
            }
            catch (const char *c) {
                if (c[0] == 'N') cout << "No match student!\n";
                if (c[0] == 'I') cout << "Wrong score!\n";
            }
        }
    }
};

void AppX::printAvgScore() {
    string sbuf;
    Class *cl;
    double avg;

    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;

        cl = nullptr;
        for (vector<Class *>::iterator it = classVec.begin();
             it != classVec.end();
             ++it) {
            if ((*it)->name == sbuf) {
                cl = *it;
                break;
            }
        }
        if (cl == nullptr) {
            cout << "No match class!" << endl;
            continue;
        }
        avg = cl->getAvgScore();
        cout << "The average score is: " << fixed << setprecision(2) << avg << endl;
    }
}

void AppX::printGpa() {
    string studentId;
    double gpa;
    while (true) {
        cout << "Please input the student id (or input q to quit): ";
        cin >> studentId;
        if (studentId == "q")
            break;
        gpa = -1;
        for (const auto &s : studentVec) {
            if (s->id == studentId) {
                gpa = s->getGrade();
                break;
            }
        }
        if (gpa != -1)
            cout << "GPA = " << fixed << setprecision(2) << gpa << endl;
        else
            cout << "No match student!" << endl;
        gpa = 0;
    }
}
int AppX::run() {
    char cmd;
    while (true) {
        cout << "Command menu:\n"
             << "\ti: Input score\n"
             << "\ta: Compute average score of a class\n"
             << "\tg: Compute grade of a student\n"
             << "\tq: Quit\n"
             << "Please input the command: ";
        cin >> cmd;
        if (cmd == 'i') {
            inputScore();
        } else if (cmd == 'a') {
            printAvgScore();
        } else if (cmd == 'g') {
            printGpa();
        } else if (cmd == 'q') {
            break;
        } else {
            cout << "Invalid command!\n"
                 << endl;
        }
    }
    return 0;
}

int main() {
    AppX app;
    return app.run();
}
