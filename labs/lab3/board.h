#pragma once
#include "stack.h"
#include "canvas.h"
#include <cstddef>

class Board {
private:
    struct moveStruct{
        int from;
        int to;
        // moveStruct(int f,int t):from(f),to(t){};
    };
    Stack<int> stacks[3]; // list of pointers to stacks
    Stack<moveStruct>moves;  // list of moves already taken by user (need for reverting moves back to start autoplay)
    int num_disk;
    int num_move;
    Canvas canvas;
    void hanoi(int n, int to, int from, int aux);

public:
    Board(int num_disk);

    ~Board();
    void draw();
    void move(int from, int to, bool log = true);
    bool win();
    void autoplay();
};
