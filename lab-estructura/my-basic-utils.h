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

/*
Foreground colors:
Black: \033[0;30m
Red: \033[0;31m
Green: \033[0;32m
Yellow: \033[0;33m
Blue: \033[0;34m
Magenta: \033[0;35m
Cyan: \033[0;36m
White: \033[0;37m  

Background colors:
Black: \033[0;40m
Red: \033[0;41m
Green: \033[0;42m
Yellow: \033[0;43m
Blue: \033[0;44m
Magenta: \033[0;45m
Cyan: \033[0;46m
White: \033[0;47m  

Effects:
Bold: \033[1m
Italic: \033[3m
Underline: \033[4m
Reset: \033[0m
*/

/*
 * Prints a colored string to the console.
 *
 * @param str The string to print.
 * @param color_code The color code to use. Valid color codes are:
 *   - 0: Black
 *   - 1: Red
 *   - 2: Green
 *   - 3: Yellow
 *   - 4: Blue
 *   - 5: Magenta
 *   - 6: Cyan
 *   - 7: White
 */
inline void printColoredString(const std::string &str, int color_code) {
    std::string color_escape = "\033[3";
    color_escape += std::to_string(color_code);
    color_escape += 'm';

    std::cout << color_escape << str << "\033[0m"; // Reset to default color
}

inline int getRandomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

inline bool fiftyProb() { return getRandomInt(1, 2) == 1; }
