#pragma once

#include <cstdlib>
#include <iostream>
#include <limits>

using namespace std;

inline void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

inline void pauseScreen() {
#ifdef _WIN32
    system("pause");
#else
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
#endif
}

inline bool getAndValidateIntegerInput(int &input_int) {
    if (cin >> input_int) {
        return true;
    } else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
}

inline bool getAndvalidateStringInput(string &input_string) {
    if (cin >> input_string) {
        return true;
    } else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
}

inline bool isValidInput() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    } else {
        return true;
    }
}

inline void printColorString(string text, int color) {
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
