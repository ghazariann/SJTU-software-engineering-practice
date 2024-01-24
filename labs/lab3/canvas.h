#pragma once

#include <iostream>
#include "stack.h"
#include <cstddef>

using namespace std;

class Canvas {
public:
    static const int HEIGHT = 11, WIDTH = 41;
    char buffer[HEIGHT][WIDTH];
    
    void draw() const {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++)
                cout << buffer[i][j];
            cout << endl;
        }
    }
    void drawDisks(int num_disk, const Stack<int>* stacks) {
        int colCenter = 0;
        int numOfPlates = 0;
        int numOfasterisk = 0;
        for (int i = 0; i < 3; i++) {
            colCenter = 5 + 15 * i;
            numOfPlates = stacks[i].size();

            for (int j = 0; j < numOfPlates; j++) {
                numOfasterisk = stacks[i].get(numOfPlates - j - 1);
                for (int k = 0; k < numOfasterisk; k++) {
                    buffer[HEIGHT - 2 - 2*j][colCenter - numOfasterisk / 2 + k] = '*';
                }
            }
        }
    }

    void reset() {
        // for (int i = 0; i < HEIGHT; i++)
        //     for (int j = 0; j < WIDTH; j++)
        //         buffer[i][j] = ' ';
    for (int i = 0; i < HEIGHT-1; i++) {
            for (int j = 0; j < WIDTH; j++)
                if (j == 5 || j==20 || j==35)
                    buffer[i][j] = '|';
                else
                    buffer[i][j] = ' ';
        }
    for (int j = 0; j < WIDTH; j++){
        if (j == 5 || j==20 || j==35)
            buffer[HEIGHT-1][j] = '|';
        else
            buffer[HEIGHT-1][j] = '-';
        }
    }
};