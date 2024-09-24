/*
    Generic menu system for console applications in C++.

    This generic menu allows you handle a basic template and pass the options as
   functions to being called, allowing a dynamic programming of the behaviour of
   the menu. Also, includes a generic exit option.

    Example of usage:
        #include "generic-menu.cpp"

        void function1() {
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

#include <cstdlib>    // For system calls (consider portability alternatives)
#include <functional> // For function pointers in menu_options
#include <iostream>
#include <limits>
#include <map> // For menu_options (replace with unordered_map if performance is critical)
#include <string>

using namespace std;

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause_screen() {
#ifdef _WIN32
    system("pause");
#else
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
#endif
}

// Checks if the input is a valid integer and returns true if it is, otherwise
// clears the input stream and returns false.
bool is_valid_int_input(int &input_int) {
    if (cin >> input_int) {
        return true;
    } else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
}

bool is_valid_string_input(string &input_string) {
    if (cin >> input_string) {
        return true;
    } else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
}

// Function type alias for menu options
using MenuFunction = function<void()>;

// Menu option structure
struct MenuOption {
    string option_text;
    MenuFunction function;
};

// Create a menu with header, options, and prompt messages
void display_menu(const string &menu_header_msg,
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
        clear_screen();
        cout << menu_header_msg << endl;

        for (const auto &[option_number, menu_option] : menu_options) {
            cout << menu_option.option_text << endl;
        }
        cout << "0. Salir" << endl;

        cout << (last_input_was_invalid ? invalid_input_msg : ask_option_msg);

        int selected_option;
        bool valid_input = is_valid_int_input(selected_option);
        bool valid_option =
            (selected_option == 0 || menu_options.count(selected_option));

        if (!valid_input || !valid_option) {
            last_input_was_invalid = true;
            continue;
        }
        last_input_was_invalid = false;

        clear_screen();

        if (selected_option == 0) {
            is_running = false;
        } else {
            menu_options.at(selected_option).function();
        }
    }
}
