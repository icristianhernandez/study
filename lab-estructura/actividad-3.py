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
    repeat_simulation = True
    while repeat_simulation:
        cola_size = 8
        cola = array.array("i", [0] * cola_size)
        fin = 1
        inicio = 1
        ocuped_places = 0
        entered_people = 0
        leaved_people = 0
        null_actions = 0

        clear_console_screen()

        initial_msg = """Simulación del flujo de cola de un cajero automático.
El cajero tiene una capacidad máxima de 8 personas
y entrarán y se irán personas continuamente.

        """

        print_with_color(initial_msg, "magenta")

        while not is_key_pressed():
            people_enter = flip_coin()
            status_msg = ""
            print_color = ""

            if people_enter and ocuped_places < cola_size:
                entered_people += 1
                cola[fin - 1] = entered_people

                status_msg = "    Entró(+) la persona número " + str(cola[fin - 1])
                print_color = "green"

                fin = (fin % cola_size) + 1
                ocuped_places += 1
            elif people_enter and ocuped_places == cola_size:
                status_msg = (
                    "    No entró la persona número "
                    + str(entered_people + 1)
                    + " por falta de espacio."
                )
                print_color = "yellow"

                null_actions += 1
            elif ocuped_places > 0:
                status_msg = "    Salió(-) la persona número " + str(cola[inicio - 1])
                print_color = "red"

                cola[inicio - 1] = 0
                inicio = (inicio % cola_size) + 1
                ocuped_places -= 1
                leaved_people += 1
            elif ocuped_places == 0:
                status_msg = "    No salió ninguna persona por falta de personas."
                print_color = "yellow"

                null_actions += 1
            else:
                status_msg = "    No entró ni salió ninguna persona."
                print_color = "white"
                null_actions += 1

            print_with_color(status_msg, print_color)

            # time.sleep(1)
            # random sleep
            time.sleep(generate_random_decimal(0.5, 1.5))

        cola_representation = " ".join([str(x) for x in cola])

        final_msg = """

Resultado de la simulación:
  - Personas que entraron: {}
  - Personas que salieron: {}
  - Acciones nulas: {}
  - Estado de la cola: {}
  - Inicio: {}
  - Fin: {}
        """.format(
            entered_people,
            leaved_people,
            null_actions,
            cola_representation,
            inicio,
            fin,
        )

        print_with_color(final_msg, "magenta")

        print_with_color("Limpiando la cola, se cierra la cola por hoy...", "yellow")
        while ocuped_places > 0:
            # print that we are clearing the queue
            status_msg = "    Salió(-) la persona número " + str(cola[inicio - 1])
            print_with_color(status_msg, "red")

            cola[inicio - 1] = 0
            inicio = (inicio % cola_size) + 1
            ocuped_places -= 1
            leaved_people += 1

        repeat = input("¿Desea repetir la simulación? (s/n): ").strip().lower()
        if repeat != "s":
            repeat_simulation = False

        clear_console_screen()
