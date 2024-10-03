import os
import random
import sys
from typing import Union

if sys.platform == "win32":
    import ctypes
    import msvcrt
else:
    import select


def clear_console_screen() -> None:
    """
    Clears the console screen on both Windows and non-Windows systems.

    Args:
        None

    Returns:
        None
    """
    if sys.platform == "win32":
        os.system("cls")
    else:
        os.system("clear")


def pause() -> None:
    """
    Pauses the execution until the user presses a key.

    Args:
        None

    Returns:
        None
    """
    if sys.platform == "win32":
        os.system("pause")
    else:
        os.system("read -n 1 -s -r -p 'Press any key to continue...'")


def print_with_color(text: str, color: str) -> None:
    """
    Prints a string with the specified color on both Windows and non-Windows systems.

    Args:
        text (str): The text to print.
        color (str): The color code (e.g., 'red', 'green', 'blue').

    Returns:
        None

    Note:
        Available colors:
        - red
        - green
        - blue
        - yellow
        - magenta
        - cyan
        - white
    """
    if sys.platform == "win32":
        colors = {
            "red": 0x04,
            "green": 0x02,
            "blue": 0x01,
            "yellow": 0x06,
            "magenta": 0x05,
            "cyan": 0x03,
            "white": 0x07,
        }

        if not all(isinstance(arg, str) for arg in [text, color]):
            raise ValueError("Both text and color must be strings")

        if color not in colors:
            raise ValueError("Invalid color")

        handle = ctypes.windll.kernel32.GetStdHandle(-11)
        ctypes.windll.kernel32.SetConsoleTextAttribute(handle, colors[color])
        print(text)
        ctypes.windll.kernel32.SetConsoleTextAttribute(
            handle, 0x07
        )  # Reset to default color
    else:
        colors = {
            "red": "\033[91m",
            "green": "\033[92m",
            "blue": "\033[94m",
            "yellow": "\033[93m",
            "magenta": "\033[95m",
            "cyan": "\033[96m",
            "white": "\033[97m",
        }

        if not isinstance(text, str):
            raise ValueError("text must be a string")

        if not isinstance(color, str):
            raise ValueError("color must be a string")

        if color not in colors:
            raise ValueError("Invalid color")

        print(colors[color] + text + "\033[0m")


def generate_random_int(min_value: int, max_value: int) -> int:
    """
    Generates a random integer within the specified range.

    Args:
        min_value (int): The minimum value.
        max_value (int): The maximum value.

    Returns:
        int: A random integer within the specified range.
    """
    if not isinstance(min_value, int) or not isinstance(max_value, int):
        raise ValueError("min_value and max_value must be integers")

    if min_value > max_value:
        raise ValueError("min_value must be less than or equal to max_value")

    return random.randint(min_value, max_value)


def check_probability(probability: Union[int, float]) -> bool:
    """
    Returns True with the specified probability.

    Args:
        probability (float): The probability of returning True (0.0-100.0).

    Returns:
        bool: True with the specified probability, False otherwise.
    """
    if not isinstance(probability, (int, float)):
        raise ValueError("probability must be a float or an integer")

    if probability < 0.0 or probability > 100.0:
        raise ValueError("probability must be between 0.0 and 100.0")

    return random.random() < (probability / 100.0)


# The imports for msvcrt and select are already handled at the top of the file.

def is_key_pressed() -> bool:
    """
    Checks if a key is pressed without waiting for input.

    Args:
        None

    Returns:
        bool: True if a key is pressed, False otherwise.
    """
    if sys.platform == "win32":
        return msvcrt.kbhit()
    else:
        return select.select([sys.stdin.fileno()], [], [], 0)[0]
