"""
Dada la siguiente definición de la estructura arreglo
Typedef cola = array [n] of interger;
Integer fin,inicio;

Escriba un algoritmo en C, que simule la atención de una cola en una taquilla bancaria, cuya capacidad máxima es de 8 personas. Resuelva las colisiones (cuando no haya espacio) y controle cuando la cola está llena o vacía
"""

import array
import time
from mymodule import *

if __name__ == "__main__":
    cola = array.array("i", [0] * 8)
    fin = -1
    entered_people = 0
    leaved_pepole = 0
    null_actions = 0

    clear_screen()

    initial_msg = """Simulación del flujo de cola de un cajero automático.
El cajero tiene una capacidad máxima de 8 personas
y entrarán y se irán personas continuamente.

    """

    print_colored(initial_msg, "magenta")

    while not kbhit():
        people_enter = probability_check(45)
        people_leave = probability_check(85)
        status_msg = ""
        print_color = ""

        if people_enter and fin < 7:
            fin += 1
            cola[fin] = fin + 1

            status_msg = "    Entró(+) la persona número " + str(fin + 1)
            print_color = "green"
            entered_people += 1
        elif people_leave and fin > -1:
            cola[fin] = 0
            status_msg = "    Salió(-) la persona número " + str(fin + 1)
            print_color = "red"

            fin -= 1

            leaved_pepole += 1
        else:
            status_msg = "    No entró ni salió ninguna persona."
            print_color = "white"
            null_actions += 1

        print_colored(status_msg, print_color)

        time.sleep(1)

    cola_representation = " ".join([str(x) for x in cola])

    final_msg = """

Resultado de la simulación:
  - Personas que entraron: {}
  - Personas que salieron: {}
  - Acciones nulas: {}
  - Estado de la cola: {}
    """.format(
        entered_people, leaved_pepole, null_actions, cola_representation
    )

    print_colored(final_msg, "magenta")

    stop()
    clear_screen()
