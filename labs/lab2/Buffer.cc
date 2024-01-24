#include "Buffer.h"

#include <fstream>
#include <iostream>
using namespace std;

Buffer::Buffer() {
    head = new line;
    currentLength = 0;
    currentLineNum = 0;
}

Buffer::~Buffer() {
    clear();
    delete head;
}
void Buffer::clear() {
    line *p = head->next, *q;
    head->next = NULL;
    while (p != nullptr) {
        q = p->next;
        delete p;
        p = q;
    }
    currentLength = 0;
}

Buffer::line *Buffer::move(int idx) const {
    line *p = head;
    while (idx-- > 0 && p)
        p = p->next;
    return p;
}
void Buffer::writeToFile(const string &filename) const {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Failed to open file\n";
    }
    line *p = head;
    while (p->next != nullptr) {  // 删除链表中的所有结点
        p = p->next;
        file << p->text << '\n';
    }
    cout << file.tellp() << " byte(s) written" << endl;
    file.close();
}

void Buffer::showLines(int from, int to) {
    if (from > to) {
        throw "Number range error";
    }
    if ((from <= 0 || from > currentLength) || (to <= 0 || to > currentLength))
        throw "Line number out of range";
    line *p = move(from);
    while (from <= to) {
        cout << from << '\t' << p->text << endl;
        p = p->next;
        from++;
    }
    currentLineNum = to;
}

void Buffer::deleteLines(int from, int to) {
    if (from > to)
        throw "Delete range error";
    if ((from <= 0 || from > currentLength) || (to <= 0 || to > currentLength))
        throw "Line number out of range";
    line *pos, *delp;
    pos = move(from - 1);
    while (from <= to) {
        delp = pos->next;
        pos->next = delp->next;
        delete delp;
        --currentLength;
        --currentLineNum;
        from++;
        if (currentLineNum <= 0) currentLineNum = 0;  // ?
    }
}

void Buffer::insertLine(const string &text) {
    if (currentLineNum == 0) currentLineNum++;
    line *currP = move(currentLineNum - 1);
    currP->next = new line(text, currP->next);
    ++currentLength;
}

void Buffer::appendLine(const string &text) {
    line *currP = move(currentLineNum);
    currP->next = new line(text, currP->next);
    ++currentLength;
    ++currentLineNum;
}

const string &Buffer::moveToLine(int idx) {
    if (idx <= 0 || idx > currentLength) {
        throw "Line number out of range";
    }
    line *p = move(idx);
    currentLineNum = idx;
    return p->text;
}
