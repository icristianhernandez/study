/**
 * @file ConsoleUtils.h
 * @brief Comprehensive utility library for console operations and menu
 * management.
 *
 * This library offers a robust set of functions to facilitate console I/O,
 * interactive menu display, random number generation, and cross-platform
 * keyboard input detection. Key functionalities include:
 *
 * - **Screen Management**
 *   - `clearConsole() -> void`: Clears the console screen.
 *   - `pauseConsole() -> void`: Pauses the console until user input.
 *
 * - **Input Handling**
 *   - `readSafeInput<T>() -> std::pair<T, bool>`: Safely reads input of type T.
 *   - `promptValidInput<T>() -> T`: Prompts the user for valid input with
 * optional validation.
 *
 * - **Colored Output**
 *   - `displayColoredText(const std::string &str, int color_code) -> void`:
 * Displays text in the specified color.
 *
 * - **Random Number Generation**
 *   - `generateRandomNumber(int min, int max) -> int`: Generates a random
 * integer within a range.
 *   - `isFiftyPercentProbable() -> bool`: Returns a boolean with a 50%
 * probability.
 *
 * - **Menu Display and Interaction**
 *   - `displayUserMenu() -> void`: Displays an interactive user menu and
 * handles input.
 *
 * - **Keyboard Input Detection**
 *   - `checkKeyPress() -> int`: Checks if a keyboard key has been pressed.
 */

#pragma once

#include <cstdio>     // For system calls (consider portability alternatives)
#include <functional> // For function pointers in menu_options
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map> // For menu_options (better performance than map)
#include <vector> // For menu_options (changed from unordered_map to vector)

using std::bernoulli_distribution;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::function;
using std::istringstream;
using std::make_pair;
using std::mt19937;
using std::numeric_limits;
using std::pair;
using std::random_device;
using std::streamsize;
using std::string;
using std::to_string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::vector;
using std::ws;

/**
 * @brief Clears the console screen.
 * @details This function clears the console screen by calling the appropriate
 * system command based on the operating system.
 * @example
 * \code
 * clearConsole();
 * \endcode
 */
inline void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * @brief Pauses the console screen until the user presses Enter.
 * @details This function waits for the user to press Enter. On Windows, it uses
 * the "pause" system command. On other systems, it prompts the user and waits
 * for input.
 * @example
 * \code
 * pauseConsole();
 * \endcode
 */
inline void pauseConsole() {
#ifdef _WIN32
    cout << endl;
    system("pause");
#else
    cout << endl;
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
#endif
}

/**
 * @brief Safely reads input of type T from the console.
 *
 * @tparam T The type of input to read.
 * @return A pair containing the input value and a boolean indicating if the
 * input was valid.
 * @example
 * \code
 * auto [value, isValid] = readSafeInput<int>();
 * if (isValid) {
 *     // Use value
 * }
 * \endcode
 */
template <typename T> inline pair<T, bool> readSafeInput() {
    T input;
    string line;

    if (getline(cin, line)) {
        istringstream iss(line);
        if (iss >> input && iss.eof()) {
            return pair<T, bool>(input, true);
        }
    }
    return pair<T, bool>(T(), false);
}

/**
 * @brief Asks the user for valid input of type T, with an optional validation
 * function.
 *
 * @tparam T The type of input to read.
 * @param reask_msg The message to display if the input is invalid.
 * @param check A function to validate the input.
 * @return The valid input value.
 * @example
 * \code
 * int age = promptValidInput<int>("Please enter a valid age: ", [](const int
 * &a) { return a > 0; });
 * \endcode
 */
template <typename T>
T promptValidInput(
    const string &reask_msg = "Invalid input, try again: ",
    const function<bool(const T &)> &check = [](const T &) { return true; }) {

    while (true) {
        auto [input, valid_input] = readSafeInput<T>();

        if (valid_input && (!check || check(input))) {
            return input;
        }

        cout << reask_msg;
    }
}

/**
 * @brief Prints a colored string to the console.
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
 * @example
 * \code
 * displayColoredText("Hello, World!", 2); // Displays green text
 * \endcode
 */
inline void displayColoredText(const string &str, int color_code) {
    if (color_code < 0 || color_code > 7) {
        cerr << "Invalid color code. Valid range is 0-7." << endl;
        return;
    }

    string color_escape = "\033[3" + to_string(color_code) + 'm';
    cout << color_escape << str << "\033[0m"; // Reset to default color
}

/**
 * @brief Generates a random integer between min and max (inclusive).
 *
 * @param min The minimum value.
 * @param max The maximum value.
 * @return A random integer between min and max.
 * @example
 * \code
 * int randomNum = generateRandomNumber(1, 100);
 * \endcode
 */
inline int generateRandomNumber(int min, int max) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

/**
 * @brief Returns true with a probability of 50%.
 *
 * @return True with a probability of 50%, otherwise false.
 * @example
 * \code
 * if (isFiftyPercentProbable()) {
 *     // Do something
 * }
 * \endcode
 */
inline bool isFiftyPercentProbable() {
    static random_device rd;
    static mt19937 gen(rd());
    static bernoulli_distribution d(0.5);
    return d(gen);
}

// Menu option structure
struct MenuOption {
    string trigger_substring;
    string option_text;
    function<void()> callback;
};

/**
 * @brief Displays a user menu and handles user input to trigger corresponding
 * functions.
 *
 * This function displays a menu with options provided in the `menu_options`
 * vector. It continuously prompts the user to select an option until the user
 * chooses to exit. Each menu option is associated with a function that gets
 * called when the option is selected.
 *
 * @param menu_options A vector of MenuOption objects, each containing a trigger
 * substring and a function to execute.
 * @param menu_header_msg A string message to display as the menu header.
 * Default is "Menu\n".
 * @param ask_option_msg A string message to prompt the user to select an
 * option. Default is "\nPlease select an option: ".
 * @param invalid_input_msg A string message to display when the user input is
 * invalid. Default is "\nInvalid option. Please try again: ".
 *
 * @note If the `menu_options` vector is empty, the function will print "No
 * options available." and return immediately.
 * @example
 * \code
 * std::vector<MenuOption> options = {
 *     {"1", "Say Hello", []() { std::cout << "Hello, World!" << std::endl; }},
 *     {"2", "Say Goodbye", []() { std::cout << "Goodbye!" << std::endl; }}
 * };
 * displayUserMenu(options);
 * \endcode
 */
inline void displayUserMenu(
    const vector<MenuOption> &menu_options,
    const string &menu_header_msg = "Menu\n",
    const string &ask_option_msg = "\nPlease select an option: ",
    const string &invalid_input_msg = "\nInvalid option. Please try again: ") {

    clearConsole();

    if (menu_options.empty()) {
        cout << "No options available." << endl;
        return;
    }

    unordered_map<string, const function<void()>> menu_option_map;
    for (const auto &option : menu_options) {
        menu_option_map.emplace(option.trigger_substring, option.callback);
    }

    bool is_running = true;

    while (is_running) {
        clearConsole();

        cout << menu_header_msg << endl;
        for (size_t i = 0; i < menu_options.size(); ++i) {
            cout << i + 1 << ". " << menu_options[i].option_text << endl;
        }
        cout << "0. Exit" << endl;

        cout << ask_option_msg;
        auto [selected_option, valid_input] = readSafeInput<string>();

        if (!valid_input) {
            cout << invalid_input_msg;
            continue;
        }

        if (selected_option == "0") {
            is_running = false;
        } else if (menu_option_map.find(selected_option) !=
                   menu_option_map.end()) {
            menu_option_map[selected_option]();
        } else {
            cout << invalid_input_msg;
        }
    }
}

//////////////////////////////////////////////////
/// GENERIC KBHIT IMPLEMENTATION ///
//////////////////////////////////////////////////

#ifndef KBHIT_H
#define KBHIT_H

#ifdef _WIN32
#include <conio.h>
#else // Linux
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#endif

/**
 * @brief Checks if a keyboard key has been pressed (cross-platform).
 *
 * @return Non-zero if a key has been pressed, otherwise zero.
 * @example
 * \code
 * if (checkKeyPress()) {
 *     // Handle key press
 * }
 * \endcode
 */
inline int checkKeyPress() {
#ifdef _WIN32
    return kbhit();
#else
    static const int STDIN = 0;
    static bool initialized = false;
    static termios old_term, new_term;

    if (!initialized) {
        tcgetattr(STDIN, &old_term);
        new_term = old_term;
        new_term.c_lflag &= ~ICANON;
        new_term.c_lflag &= ~ECHO;
        tcsetattr(STDIN, TCSANOW, &new_term);
        setbuf(stdin, NULL);
        atexit([] { tcsetattr(STDIN, TCSANOW, &old_term); });
        initialized = true;
    }

    pollfd fds[1];
    fds[0].fd = STDIN;
    fds[0].events = POLLIN;

    int ret = poll(fds, 1, 0);

    if (ret > 0 && (fds[0].revents & POLLIN)) {
        return 1;
    }

    return 0;
#endif // _WIN32
}

#endif // KBHIT_H
