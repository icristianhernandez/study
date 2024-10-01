import sys
import random
import os


def clear_screen():
    """
    Clears the console screen.

    Args:
        None

    Returns:
        None
    """
    if sys.platform == "win32":
        os.system("cls")
    else:
        os.system("clear")


def stop():
    """
    Stops the app until the user presses a key.

    Args:
        None

    Returns:
        None
    """
    if sys.platform == "win32":
        os.system("pause")
    else:
        os.system("read -n 1 -s -p 'Press any key to continue...'")


if sys.platform == "win32":
    import ctypes

    def print_colored(text, color):
        """
        Prints a string with the specified color on Windows.

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
        colors = {
            "red": 0x04,
            "green": 0x02,
            "blue": 0x01,
            "yellow": 0x06,
            "magenta": 0x05,
            "cyan": 0x03,
            "white": 0x07,
        }

        handle = ctypes.windll.kernel32.GetStdHandle(-11)
        ctypes.windll.kernel32.SetConsoleTextAttribute(handle, colors[color])
        print(text)
        ctypes.windll.kernel32.SetConsoleTextAttribute(
            handle, 0x07
        )  # Reset to default color

else:

    def print_colored(text, color):
        """
        Prints a string with the specified color on Linux/macOS.

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
        colors = {
            "red": "\033[91m",
            "green": "\033[92m",
            "blue": "\033[94m",
            "yellow": "\033[93m",
            "magenta": "\033[95m",
            "cyan": "\033[96m",
            "white": "\033[97m",
        }

        if color not in colors:
            raise ValueError("Invalid color")

        if not isinstance(text, str):
            raise ValueError("text must be a string")

        print(colors[color] + text + "\033[0m")


def generate_random_int(min_value, max_value):
    """
    Generates a random integer within the specified range.

    Args:
        min_value (int): The minimum value.
        max_value (int): The maximum value.

    Returns:
        int: A random integer within the specified range.
    """
    if min_value > max_value:
        raise ValueError("min_value must be less than or equal to max_value")

    if not isinstance(min_value, int) or not isinstance(max_value, int):
        raise ValueError("min_value and max_value must be integers")

    return random.randint(min_value, max_value)


def probability_check(probability):
    """
    Returns True with the specified probability.

    Args:
        probability (int): The probability of returning True (0-100).

    Returns:
        bool: True with the specified probability, False otherwise.
    """
    if probability < 0 or probability > 100:
        raise ValueError("probability must be between 0 and 100")

    if not isinstance(probability, int):
        raise ValueError("probability must be an integer")

    return random.randint(0, 100) < probability


if sys.platform == "win32":
    import msvcrt

    def kbhit():
        """
        Checks if a key is pressed without waiting for input.

        Args:
            None

        Returns:
            bool: True if a key is pressed, False otherwise.
        """
        return msvcrt.kbhit()

else:
    import select

    def kbhit():
        """
        Checks if a key is pressed without waiting for input.

        Args:
            None

        Returns:
            bool: True if a key is pressed, False otherwise.
        """
        return select.select([sys.stdin], [], [], 0)[0]
