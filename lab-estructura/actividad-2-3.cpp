#include "generic-menu.h"
#include "kbhit.h"
#include "my-basic-utils.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

void startProgram() {
    stack<int> stacks_of_plates;

    map<int, string> plates_colors = {
        {1, "Azul"},
        {2, "Blanco"},
        {3, "Rojo"},
    };

    int plates_total = 0;
    int blue_plates_count = 0;
    int white_plates_count = 0;
    int red_plates_count = 0;

    cout << "La cocina se ha abierto. " << endl;
    cout << "Se empezaran a lavar y entregar platos." << endl << endl;

    while (!_kbhit()) {
        bool plates_clearing = fiftyProb();
        int affected_type_plate;
        string states_msg = "";
        string term_color;

        if (plates_clearing) {
            affected_type_plate = getRandomInt(1, 3);
            plates_total += 1;
            stacks_of_plates.push(affected_type_plate);
            states_msg = "Entra(+) plato lavado de color " +
                         plates_colors[affected_type_plate];

            if (affected_type_plate == 1) {
                blue_plates_count += 1;
            } else if (affected_type_plate == 2) {
                white_plates_count += 1;
            } else if (affected_type_plate == 3) {
                red_plates_count += 1;
            }

        } else if (!stacks_of_plates.empty()) {
            affected_type_plate = stacks_of_plates.top();
            plates_total -= 1;
            stacks_of_plates.pop();
            states_msg = "Sale(-) plato lavado de color " +
                         plates_colors[affected_type_plate];

            if (affected_type_plate == 1) {
                blue_plates_count -= 1;
            } else if (affected_type_plate == 2) {
                white_plates_count -= 1;
            } else if (affected_type_plate == 3) {
                red_plates_count -= 1;
            }
        } else {
            states_msg = "No sucede nada.";
        }

        if (affected_type_plate == 1) {
        } else if (affected_type_plate == 2) {
        } else {
        }

        cout << states_msg << endl;

        sleep(1);
    }

    cout << endl << endl;
    cout << "Reporte Actual De Platos" << endl;
    cout << "Hay " << blue_plates_count << " platos azules." << endl;
    cout << "Hay " << white_plates_count << " platos blancos." << endl;
    cout << "Hay " << red_plates_count << " platos rojos." << endl;
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
