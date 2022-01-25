#include "CMD_ANIME_API.h"

#include <assert.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
using namespace std;

void CMD_ANIME_API::framecpy(int **&from, int **to, int r, int c) {
    for (int i = 0; i < row; i++) {
        memset(to[i], 0, col * sizeof(int));
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            to[i][j] = from[i][j];
        }
    }
    return;
}
bool CMD_ANIME_API::isSame(int idx) {
    for (int i = 0; i < col; i++) {
        if (cur_screen[idx][i] != next_screen[idx][i]) return false;
    }
    return true;
}
void CMD_ANIME_API::replace(int idx) {
    string index = to_string(idx + 1);
    string cursorpos = "\e[" + index + ";1H";  // escape code
    string clrline = "\e[2K";
    cout << cursorpos << clrline << flush;

    for (int i = 0; i < row; i++) {
        cout << TransferTable[next_screen[idx][i]];
    }
    cout << flush;
    return;
}

void CMD_ANIME_API::showcur() {
    string clearscreen = "\e[2J";  // escape code
    string cursorpos = "\e[1;1H";  // escape code
    cout << clearscreen << cursorpos << flush;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << TransferTable[cur_screen[i][j]];
        }
        cout << endl;
    }
    return;
}

CMD_ANIME_API::CMD_ANIME_API(int col, int row) : col(col), row(row) {
    // init the screen size, columns and rows.
    int *tmp = new int[row * col];
    int *tmp2 = new int[row * col];
    memset(tmp, 0, row * col * sizeof(int));
    memset(tmp2, 0, row * col * sizeof(int));

    cur_screen = new int *[row];
    next_screen = new int *[row];
    for (int i = 0; i < row; i++) {
        cur_screen[i] = &(tmp[i * col]);
        next_screen[i] = &(tmp2[i * col]);
    }
}

void CMD_ANIME_API::TransferNumberToString(unordered_map<int, string> CustomizeTable) {
    // user specify the transfer table, which is used for fransfer screen data to customize siginature.
    // For Example: 0 represent as "X", 1 represent "O".
    TransferTable.insert(CustomizeTable.begin(), CustomizeTable.end());
    showcur();
}
void CMD_ANIME_API::show(int **&frame, int r, int c) {
    // show out the screen.
    assert(r <= row && c <= col);
    framecpy(frame, next_screen, r, c);

    for (int i = 0; i < row; i++) {
        if (!isSame(i)) {
            replace(i);
        }
    }

    framecpy(next_screen, cur_screen, r, c);

    usleep(500 * 1000);
}
void CMD_ANIME_API::print() {
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            cout << cur_screen[i][j];
        }
        cout << endl;
    }
    return;
}

CMD_ANIME_API::~CMD_ANIME_API() {
}

int main(void) {
    // log.open("log.txt", ostream::out);

    CMD_ANIME_API API(20, 20);
    unordered_map<int, string> map;
    map[0] = "XX";
    map[1] = " o";
    map[2] = " .";
    API.TransferNumberToString(map);

    int **maze = new int *[20];
    for (int i = 0; i < 20; i++) {
        maze[i] = new int[20];
    }

    for (int i = 0; i < 100; i++) {
        int r = rand() % 20;
        int c = rand() % 20;
        maze[r][c] = rand() % 2 + 1;
        API.show(maze, 20, 20);
    }
}