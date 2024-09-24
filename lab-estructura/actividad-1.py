import os
from random import randint

is_running = True
min_numbers_to_generate = 1
max_numbers_to_generate = 10
min_random_number = 1
max_random_number = 1000

while is_running:
    os.system("cls")
    print("Elige una de las siguientes opciones:")
    print("1) Mostrar una cantidad aleatoria de números aleatorios")
    print("2) Cambiar colores de la terminal aleatoriamente")
    print("3) Finalizar la ejecución del programa")

    print("")
    user_selection = input("Opción a elegir (número): ")

    if user_selection == "1":
        print("")
        print("")
        print("")
        generated_numbers = "Los números aleatorios son: "
        numbers_to_generate = randint(min_numbers_to_generate, max_numbers_to_generate)
        for random_number in range(numbers_to_generate):
            if random_number != (numbers_to_generate - 1):
                generated_numbers += (
                    str(randint(min_random_number, max_random_number)) + ", "
                )
            else:
                generated_numbers += str(randint(min_random_number, max_random_number))
        print("    " + generated_numbers)
    elif user_selection == "2":
        colors_codes = [
            "00",
            "01",
            "02",
            "03",
            "04",
            "05",
            "06",
            "07",
            "08",
            "09",
        ]
        colors_names = [
            "negro",
            "azul",
            "verde",
            "aguamarina",
            "rojo",
            "púrpura",
            "amarillo",
            "blanco",
            "gris",
            "azul claro",
        ]
        color_index = randint(1, len(colors_codes) - 1)
        selected_colors = colors_codes[color_index]
        selected_colors_names = colors_names[color_index]
        os.system("color " + selected_colors)
        print("")
        print("")
        print("")
        print("    El color del texto se cambió a " + selected_colors_names)
    elif user_selection == "3":
        is_running = False
    else:
        print("")
        print("")
        print("")
        print("    Opción inválida. Elija un número del uno al tres.")

    print("")
    os.system("pause")
