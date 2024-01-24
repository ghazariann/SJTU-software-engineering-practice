#pragma once
#include <string>
using std::string;

class Buffer {
private:
    int currentLineNum;
    struct line {
        string text;
        line *next;
        line(const string &x, line *n = NULL, line *p = NULL) {
            text = x, next = n;
        }
        line() : next(NULL) {}
        ~line() {}
    };
    line *head;
    
    void clear();
    line *move(int i) const; 

public:
    Buffer();
    ~Buffer();
    int currentLength;
    void writeToFile(const string &filename) const;

    const string &moveToLine(int idx);// const;

    void showLines(int from, int to);
    void traverse();
    void deleteLines(int from, int to);
    void insertLine(const string &text);
    void appendLine(const string &text);
};
