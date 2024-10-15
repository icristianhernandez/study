"""
2.- Elabore un programa que Ingrese 20 números mayores que 50  Calcule y almacene sus 5 primeros divisores. Usando estructuras de arreglo y registros
"""

from mymodule import *


def divisors_of(number: int, divisors_ammount: int = 0) -> list[int]:
    """
    This function returns the divisors of a number. The ammount of divisors to get can be specified.

    Args:
        number (int): The number to get the divisors from.
        divisors_ammount (int): The ammount of divisors to get. (0 is all
        [default: 0])

    Returns:
        divisors_list: The list of divisors.
    """

    divisors_list: list[int] = []

    for i in range(1, number + 1):
        if number % i == 0:
            divisors_list.append(i)

            if len(divisors_list) == divisors_ammount:
                break

    return divisors_list


class NumberWithDivisors:
    def __init__(self, number: int = 0, first_five_divisors: list[int] = []):
        self.number: int = number
        self.first_five_divisors: list[int] = first_five_divisors

    def __str__(self) -> str:
        return f"Number: {self.number}, First five divisors: {self.first_five_divisors}"


SETTINGS = {
    "ammount_of_numbers": 20,
    "insert_random_numbers": True,
    "min_number_to_get": 50,
    "max_number_to_get": 10000,
}


def main():
    numbers_to_get_divisors: list[NumberWithDivisors] = []
    welcome_msg = (
        "Este programa calcula los 5 primeros divisores de 20 números mayores a 50."
    )
    config_msg = (
        "¿Desea ingresar los números manualmente? (s/n/enter para no cambiar): "
    )
    re_ask_config = "Por favor, ingrese una opción válida (s/n/enter para no cambiar): "
    change_input_mode = ""
    change_max_number = ""

    clear_console_screen()

    print(welcome_msg)

    change_input_mode = ask_for_input(
        str, config_msg, re_ask_config, lambda x: x in ["s", "n", ""]
    )

    if change_input_mode == "s":
        SETTINGS["insert_random_numbers"] = False
    elif change_input_mode == "n":
        SETTINGS["insert_random_numbers"] = True

    if SETTINGS["insert_random_numbers"]:
        for i in range(SETTINGS["ammount_of_numbers"]):
            number = generate_random_int(
                SETTINGS["min_number_to_get"], SETTINGS["max_number_to_get"]
            )
            numbers_to_get_divisors.append(NumberWithDivisors(number))
    else:
        for i in range(SETTINGS["ammount_of_numbers"]):
            number = ask_for_input(
                int,
                f"Por favor, ingrese el número {i + 1}: ",
                "Por favor, ingrese un número válido: ",
                lambda x: x > SETTINGS["min_number_to_get"],
            )
            numbers_to_get_divisors.append(NumberWithDivisors(number))

    for number in numbers_to_get_divisors:
        number.first_five_divisors = divisors_of(number.number, 5)

    # Print the numbers with their divisors
    print("\n")
    print("Los 20 números con sus 5 primeros divisores son:")
    for number in numbers_to_get_divisors:
        print(
            f"    - Los 5 primeros divisores de {number.number} son: {number.first_five_divisors}"
        )

    print("\n")
    pause_console()
    clear_console_screen()

    return 0


if __name__ == "__main__":
    main()
