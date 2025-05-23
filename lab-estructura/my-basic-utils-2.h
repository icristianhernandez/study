#pragma once

#include <cstdlib>    // For system calls (consider portability alternatives)
#include <functional> // For function pointers in menu_options
#include <iostream>
#include <limits>
#include <map> // For menu_options (replace with unordered_map if performance is critical)
#include <random>
#include <string>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::function;
using std::map;
using std::mt19937;
using std::numeric_limits;
using std::pair;
using std::rand;
using std::random_device;
using std::streamsize;
using std::string;
using std::to_string;
using std::uniform_int_distribution;

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

/*inline pair<int, bool> getAndValidateIntegerInput() {*/
/*    int input_int;*/
/*    if (cin >> input_int) {*/
/*        return {input_int, true};*/
/*    } else {*/
/*        cin.clear();*/
/*        cin.ignore(numeric_limits<streamsize>::max(), '\n');*/
/*        return {0, false};*/
/*    }*/
/*}*/
// example of usage:
// auto [input_int, valid_input] = getAndValidateIntegerInput();

// without using auto:
// int input_int;
// bool valid_input;
// tie(input_int, valid_input) = getAndValidateIntegerInput();

template <typename T> inline pair<T, bool> getAndValidateInput() {
    T input;
    if (cin >> input) {
        return {input, true};
    } else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return {T(), false};
    }
}
// example of usage:
// auto [input_int, valid_input] = getAndValidateInput<int>();

inline bool getAndValidateStringInput(string &input_string) {
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

template <typename T>
inline pair<T, bool> askValidInput(const function<bool(const T &)> &check =
                                       [](const T &) { return true; }) {
    T input;
    if (cin >> input && check(input)) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return {input, true};
    } else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return {T(), false};
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
inline void printColoredString(const string &str, const int &color_code) {
    if (color_code < 0 || color_code > 7) {
        cerr << "Invalid color code. Valid range is 0-7." << endl;
        return;
    }

    string color_escape = "\033[3";
    color_escape += to_string(color_code);
    color_escape += 'm';

    cout << color_escape << str << "\033[0m"; // Reset to default color
}

inline int getRandomInt(int min, int max) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

inline bool fiftyProb() { return getRandomInt(1, 2) == 1; }

//////////////////////////////////////////////////
/// GENERIC MENU SYSTEM FOR CONSOLE APPLICATIONS /
/////////////////////////////////////////////////

/*
This generic menu allows you handle a basic template and
    pass the options as functions to being called,
    allowing a dynamic programming of the behaviour of the menu.Also,
    includes a generic exit option.

    Example of usage :
#include "generic-menu.cpp"

    void
    function1() {
    cout << "Function 1" << endl;
    pause_screen();
}

void function2() {
    cout << "Function 2" << endl;
    pause_screen();
}

int main() {
    map<int, MenuOption> menu_options = {
        {1, {"1. Primera Opción", function1}},
        {2, {"2. Segunda Opción", function2}},
    };

            display_menu("Menú de Pruebas", menu_options, "\nSeleccione una
    opción: ");
}
*/

// TODO: Add defalt values for arguments in display_menu function
// TODO: Add a way to pass a custom exit message
// TODO: Pass the utility functions to a separate headers
// TODO: Add utility to print in a color
// TODO: Define if I going to programming in windows or linux, and of what way

// Function type alias for menu options
// MenuFunction represents a function that takes no arguments and returns void.
using MenuFunction = function<void()>;

// Menu option structure
// Represents an option in the menu with its display text and associated
// function.
struct MenuOption {
    string option_text;
    MenuFunction function;
};

inline void display_menu_header(const string &menu_header_msg,
                                const map<int, MenuOption> &menu_options) {
    clearScreen();
    cout << menu_header_msg << endl;

    for (const auto &[option_number, menu_option] : menu_options) {
        cout << menu_option.option_text << endl;
    }
    cout << "0. Salir" << endl;
}

inline void display_menu(const string &menu_header_msg,
                         const map<int, MenuOption> &menu_options,
                         const string &ask_option_msg) {
    if (menu_options.empty()) {
        cout << "No hay opciones disponibles." << endl;
        return;
    }

    bool is_running = true;
    bool last_input_was_invalid = false;
    string invalid_input_msg = "\nOpción inválida. Introduzca nuevamente: ";

    while (is_running) {
        display_menu_header(menu_header_msg, menu_options);
        cout << (last_input_was_invalid ? invalid_input_msg : ask_option_msg);

        int selected_option;
        bool valid_input = getAndValidateIntegerInput(selected_option);
        bool valid_option =
            (selected_option == 0 || menu_options.count(selected_option));

        if (!valid_input || !valid_option) {
            last_input_was_invalid = true;
            continue;
        }
        last_input_was_invalid = false;

        clearScreen();

        if (selected_option == 0) {
            is_running = false;
        } else {
            menu_options.at(selected_option).function();
        }
    }
}

//////////////////////////////////////////////////
/// GENERIC KBHIT IMPLEMENTATION /
/////////////////////////////////////////////////

#ifndef KBHIT_H
#define KBHIT_H

#ifdef _WIN32
#include <conio.h>
#else // Linux
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#endif

#ifdef _WIN32
inline int _kbhit() { return kbhit(); }
#else
inline int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (!initialized) {
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN, &readfds);

    timeval tv = {0, 0};

    int flags = fcntl(STDIN, F_GETFL, 0);
    fcntl(STDIN, F_SETFL, flags | O_NONBLOCK);

    int ret = select(STDIN + 1, &readfds, NULL, NULL, &tv);

    fcntl(STDIN, F_SETFL, flags); // Restore original flags

    return ret > 0 && FD_ISSET(STDIN, &readfds);
}
#endif // _WIN32

#endif // KBHIT_H
