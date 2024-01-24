#include <climits>
#include <iostream>
#include <string>

#include "board.h"

using namespace std;

int main() {
    while (true) {
        cout << "How many disks do you want? (1 ~ 5)" << endl;
        string input;
        int from, to, inp_num;
        getline(cin, input);
        if (input == "Q")
            break;
        try {
            inp_num = stoi(input);
        } catch (const invalid_argument& e) {
            continue;
        }
        if (inp_num < 1 || inp_num > 5)
            continue;
        Board b = Board(inp_num);
        b.draw();

        while (!b.win()) {
            cout << "Move a disk. Format: x y " << endl;
            getline(cin, input);

            int space_pos = input.find(' ');
            if (space_pos == string::npos)
                continue;
            try {
                from = stoi(input.substr(0, space_pos));
                to = stoi(input.substr(space_pos + 1));
            } catch (const invalid_argument& e) {
                continue;
            }

            if (from == 0 && to == 0)
                b.autoplay();
            else
                b.move(from - 1, to - 1, false);
        }
        cout << "Congratulations! You win!" << endl;
    }
    return 0;
}
