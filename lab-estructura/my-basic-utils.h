#pragma once
#include <cstdlib>
#include <iostream>
#include <limits>

using namespace std;

inline void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

inline void pause_screen() {
#ifdef _WIN32
    system("pause");
#else
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
#endif
}

inline bool is_valid_int_input(int &input_int) {
    if (cin >> input_int) {
        return true;
    } else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
}

inline bool is_valid_string_input(string &input_string) {
    if (cin >> input_string) {
        return true;
    } else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
}

inline void print_color_string(string text, int color) {
    /*
        Color codes:
        0 = Black
        1 = Blue
        2 = Green
        3 = Cyan
        4 = Red
        5 = Magenta
        6 = Brown
        7 = Light Gray
        8 = Dark Gray
        9 = Light Blue
        10 = Light Green
        11 = Light Cyan
        12 = Light Red
        13 = Light Magenta
        14 = Yellow
        15 = White
    */

    cout << "\033[1;" << color << "m" << text << "\033[0m";
}

inline int getRandomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

inline bool fiftyProb() { return getRandomInt(1, 2) == 1; }

inline bool _kbhit() {
    // Generic implementation of kbhit for Windows and Linux
#ifdef _WIN32
    return _kbhit();
#else
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(0, &fds); // STDIN_FILENO is 0
    select(1, &fds, NULL, NULL, &tv);
    return FD_ISSET(0, &fds);

#endif
}
