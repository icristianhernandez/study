/*
    Basic program for play around the use of stacks.

    The program creates a stack with a random amount of numbers in a range
    defined by the user and after show the resulting stack, asks the user which
    number they want to know how many times it appears

    The numbers are added to the stack each second and the user stops pressing a
    key.

    Date: 23/09/2024
    Subject: Labotarorio de Estructura de Datos
 */

#include "generic-menu.cpp"
/*#include <conio.h>*/
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>
#include <unistd.h>

using namespace std;

struct StackBounds {
    int min;
    int max;
};

StackBounds stack_bounds = {1, 100};

int getRandomInt(int min, int max) { return rand() % (max - min + 1) + min; }

void printStack(stack<int> stack_of_numbers) {
    while (!stack_of_numbers.empty()) {
        cout << stack_of_numbers.top() << " ";
        stack_of_numbers.pop();
    }
    cout << endl;
}

int searchIntOcurrencesStack(stack<int> stack_of_numbers,
                             int number_to_search) {
    int times_found = 0;

    while (!stack_of_numbers.empty()) {
        if (stack_of_numbers.top() == number_to_search) {
            times_found++;
        }
        stack_of_numbers.pop();
    }

    return times_found;
}

void startProgram() {
    stack<int> stack_of_numbers;
    int number_to_add;
    int number_to_search;
    int times_found = 0;
    string repeat_answer;

    // clear
    clear_screen();

    cout << "Se comenzara a anadir numeros a la pila cada segundo" << endl
         << "Presione cualquier tecla para detener" << endl
         << endl;

    while (true) {
        number_to_add = getRandomInt(stack_bounds.min, stack_bounds.max);
        stack_of_numbers.push(number_to_add);
        cout << "Se anade a la pila el numero: " << number_to_add << endl;

        sleep(1);

        if (kbhit()) {
            break;
        }
    }

    cout << endl;

    cout << "La pila resultante es: " << endl;
    printStack(stack_of_numbers);
    cout << endl << endl;

    cout << "Ingrese el numero que desea saber cuantas veces aparece: ";
    while (!is_valid_int_input(number_to_search)) {
        cout << "Ingrese un numero valido: ";
    }

    times_found = searchIntOcurrencesStack(stack_of_numbers, number_to_search);

    cout << "El numero " << number_to_search << " aparece " << times_found
         << " veces en la pila" << endl;

    cout << endl;
    cout << "Desea repetir el proceso? (y/n): ";
    while (!is_valid_string_input(repeat_answer) ||
           (repeat_answer != "y" && repeat_answer != "n")) {
        cout << "Ingrese una respuesta valida: ";
    }

    if (repeat_answer == "y") {
        startProgram();
    }
}

void changeBounds() {
    int new_min;
    int new_max;

    cout << "Ingrese el nuevo limite inferior: ";
    while (!is_valid_int_input(new_min)) {
        cout << "Ingrese un numero valido: ";
    }

    cout << "Ingrese el nuevo limite superior: ";
    while (!is_valid_int_input(new_max) || new_max <= new_min) {
        cout << "Ingrese un numero valido: ";
    }

    stack_bounds.min = new_min;
    stack_bounds.max = new_max;

    cout << "Los limites han sido cambiados a: [" << stack_bounds.min << ", "
         << stack_bounds.max << "]" << endl;

    pause_screen();
}

int main() {
    srand(time(0));

    string menu_header = "Menu de prueba\n";
    string menu_input_request = "\nSeleccione una opcion: ";

    map<int, MenuOption> menu_options = {
        {1, {"1. Iniciar el Programa", startProgram}},
        {2, {"2. Configurar los Limites", changeBounds}},
    };

    display_menu(menu_header, menu_options, menu_input_request);

    return 0;
}
