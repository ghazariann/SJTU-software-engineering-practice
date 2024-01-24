#include "board.h"
#include "canvas.h"

Board::Board(int num_disk) {
    this->num_disk = num_disk;
    this->num_move = 0;
    for (int i = 0; i < 3; i++) {
        stacks[i] = Stack<int>();
    }
    for (int i = num_disk; i > 0; i--) {
        stacks[0].push(2 * i + 1);
    }
}

Board::~Board() {
    for (int i = 0; i < 3; i++) {
        stacks[i].~Stack();
    }
}

void Board::draw() {
    Canvas canvas;
    canvas.reset();
    canvas.drawDisks(num_disk, stacks);
    canvas.draw();
}

void Board::move(int from, int to, bool log) {
    if (from < 0 || from > 2 || to < 0 || to > 2) {
        draw();
        return;
    }
    if (log)
        cout << "Auto moving:" << from + 1 << "->" << to + 1 << endl;

    if (!stacks[from].empty() && ((stacks[to].empty()) || (stacks[from].top() < stacks[to].top()))) {
        stacks[to].push(stacks[from].pop());
        if (!log) {
            moveStruct m;
            m.from = from;
            m.to = to;
            moves.push(m);
        }

        draw();
    } else {  // invalid move
        draw();
        return;
    }
}

bool Board::win() {
    return stacks[1].size() == num_disk || stacks[2].size() == num_disk;
}

void Board::hanoi(int n, int to, int from, int aux) {  // move n disks from rod A to rod B, use rod C as
    if (n == 0)
        return;
    hanoi(n - 1, to, aux, from);
    move(to, from, true);  // move the nth disk from rod A to rod B
    hanoi(n - 1, aux, from, to);
}
void Board::autoplay() {
    while (!moves.empty()) {
        moveStruct prevMov = moves.pop();
        move(prevMov.to, prevMov.from);
    }

    hanoi(num_disk, 0, 1, 2);
}
