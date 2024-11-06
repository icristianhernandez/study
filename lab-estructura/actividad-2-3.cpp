// This program simulates the flow of washed and delivered plates in a kitchen.
// Plates are randomly added or removed from a stack, and each plate has a
// color. The simulation runs until the user presses a key, at which point it
// displays the total number of plates and their distribution by color.

/*#include "generic-menu.h"*/
/*#include "kbhit.h"*/
/*#include "my-basic-utils.h"*/

#include "my-basic-utils-2.h"

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>
#include <thread>

using namespace std;

// color struct
struct Color {
    string name;
    int ansiCode;
    int count;
};

void startProgram() {
    stack<int> stacks_of_plates;
    int plates_total = 0;

    Color colors[3] = {{"Azul", 4, 0}, {"Verde", 2, 0}, {"Rojo", 1, 0}};

    cout << "Se abrira la cocina." << endl;
    cout << "Se simulara el flujo de platos lavados y entregados." << endl;
    cout << "  (Presione cualquier tecla para detener la simulacion.)" << endl;
    cout << endl;

    // simulation loop
    while (!_kbhit()) {
        bool plates_clearing = fiftyProb();
        int affected_plate_index;
        string states_msg = "";

        if (plates_clearing) {
            affected_plate_index = getRandomInt(0, 2);
            stacks_of_plates.push(affected_plate_index);

            states_msg = "Se ha agregado(+) un plato de color " +
                         colors[affected_plate_index].name + ".";

            plates_total += 1;
            colors[affected_plate_index].count += 1;

        } else if (!stacks_of_plates.empty()) {
            affected_plate_index = stacks_of_plates.top();
            stacks_of_plates.pop();

            states_msg = "Se retira(-) un plato de color " +
                         colors[affected_plate_index].name + ".";

            plates_total -= 1;
            colors[affected_plate_index].count -= 1;

        } else {
            states_msg = "No sucede nada.";
        }

        if (states_msg == "No sucede nada.") {
            states_msg = "    " + states_msg + "\n";
            cout << states_msg;

        } else {
            states_msg = "    " + states_msg + "\n";
            printColoredString(states_msg,
                               colors[affected_plate_index].ansiCode);
        }

        this_thread::sleep_for(chrono::seconds(1));
    }

    // report final state
    cout << endl << endl;
    cout << "Distribucion de platos por color (" << plates_total
         << " platos ):" << endl;
    for (const Color &color : colors) {
        string report_msg =
            "  Color " + color.name + ": " + to_string(color.count) + "\n";
        printColoredString(report_msg, color.ansiCode);
    }

    cout << endl;
    pauseScreen();
}

int main() {
    srand(time(0));

    string menu_header =
        "Programa que simula el flujo de platos lavados y entregados en una "
        "cocina. Cuando el usuario desee, se detiene la simulacion y muestra "
        "la cantidad disponible de platos lavados y la distribucion por tipos "
        "de platos. \n";
    string menu_input_request = "\nSeleccione una opcion: ";

    map<int, MenuOption> menu_options = {
        {1, {"1. Iniciar el Programa", startProgram}},
    };

    display_menu(menu_header, menu_options, menu_input_request);

    return 0;
}
