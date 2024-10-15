"""
mymodule.py

Utility functions for console I/O, random number generation, and keyboard input.

Functions:
    - clear_console_screen: Clear the console screen on both Windows and non-Windows systems.
    - pause: Pause the execution until the user presses a key.
    - print_with_color: Print a string with the specified color (and background color) on both Windows and non-Windows systems.
    - generate_random_int: Generate a random integer within the specified range.
    - generate_random_decimal: Generate a random decimal within the specified range.
    - check_probability: Return True with the specified probability.
    - flip_coin: Return True with a 50/50 chance.
    - is_key_pressed: Check if a key is pressed without waiting for input.
    - getch: Return a keyboard character after a key has been pressed.
    - ask_for_input: Ask the user for an input of the specified data type. Can validate.

Example:
    >>> from mymodule import *
    >>> clear_console_screen()

    >>> pause()

    >>> print_with_color("Hello, World!", "red")

    >>> generate_random_int(1, 10)
    7

    >>> check_probability(50)
    True

    >>> is_key_pressed()
    False

    >>> getch()
    'a'

References:
    - https://docs.python.org/3/library/os.html
    - https://docs.python.org/3/library/random.html
    - https://docs.python.org/3/library/sys.html
    - https://docs.python.org/3/library/ctypes.html
    - https://docs.python.org/3/library/msvcrt.html
    - https://docs.python.org/3/library/termios.html
    - https://docs.python.org/3/library/fcntl.html
    - https://docs.python.org/3/library/tty.html
    - https://docs.python.org/3/library/select.html
    - https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
    - https://en.wikipedia.org/wiki/ANSI_escape_code
    - https://en.wikipedia.org/wiki/Escape_character

"""

__author__ = "Cristian Hernández"

import os
import random
import sys
from typing import Union, Callable, Optional, Any

if sys.platform == "win32":
    import ctypes  # used for changing the console text color
    import msvcrt  # used for checking if a key is pressed
else:
    import termios  # used for terminal I/O control
    import fcntl  # used for file control
    import tty  # used for terminal control
    from select import select  # used for waiting for I/O completion


def clear_console_screen() -> None:
    """
    Clear the console screen on both Windows and non-Windows systems.

    Args:
        None

    Returns:
        None

    Example:
        >>> clear_console_screen()

    Raises:
        OSError: If the system command fails.
    """
    try:
        if sys.platform == "win32":
            os.system("cls")
        else:
            os.system("clear")
    except OSError as e:
        raise OSError(f"Failed to clear console screen: {e}")


def pause() -> None:
    """
    Pause the execution until the user presses a key.

    Args:
        None

    Returns:
        None

    Example:
        >>> pause()

    Raises:
        OSError: If the system command fails.
    """
    try:
        if sys.platform == "win32":
            print("Press any key to continue...", end="", flush=True)
            msvcrt.getch()
        else:
            os.system("read -n 1 -s -r -p 'Press any key to continue...'")
    except OSError as e:
        raise OSError(f"Failed to pause execution: {e}")


def print_with_color(text: str, color: str, background_color: str = "null") -> None:
    """
    Print a string with the specified color (and background color) on both Windows and non-Windows systems.

    Args:
        text (str): The text to print.
        color (str): The color code (e.g., 'red', 'green', 'blue').
        background_color (str): The background color code (e.g., 'red', 'green', 'blue'). Default is None.

    Returns:
        None

    Example:
        >>> print_with_color("Hello, World!", "red")
        # "Hello, World!" will be printed in red text

        >>> print_with_color("Hello, World!", "red", "blue")
        # "Hello, World!" will be printed in red text with a blue background

    Raises:
        ValueError: If text or color is not a string.
        ValueError: If color is not a valid color.
        ValueError: If background_color is not a valid color.

    Notes:
        - If the background_color parameter is not specified, the background color will not be changed
        - Avaible colors:
            - red, green, blue, yellow, magenta, cyan, white
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

        if not isinstance(text, str) or not isinstance(color, str):
            raise ValueError("Both text and color must be strings")

        if color not in colors:
            raise ValueError("Invalid color")

        if background_color != "null":
            background_colors = {
                "red": 0x40,
                "green": 0x20,
                "blue": 0x10,
                "yellow": 0x60,
                "magenta": 0x50,
                "cyan": 0x30,
                "white": 0x70,
            }

            if background_color not in background_colors:
                raise ValueError("Invalid background color")

            handle = ctypes.windll.kernel32.GetStdHandle(-11)
            ctypes.windll.kernel32.SetConsoleTextAttribute(
                handle, colors[color] | background_colors[background_color]
            )
        else:
            handle = ctypes.windll.kernel32.GetStdHandle(-11)
            ctypes.windll.kernel32.SetConsoleTextAttribute(handle, colors[color])

        try:
            print(text)
        finally:
            # Reset to default color
            ctypes.windll.kernel32.SetConsoleTextAttribute(handle, 0x07)

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

        if background_color != "null":
            background_colors = {
                "red": "\033[41m",
                "green": "\033[42m",
                "blue": "\033[44m",
                "yellow": "\033[43m",
                "magenta": "\033[45m",
                "cyan": "\033[46m",
                "white": "\033[47m",
            }

            if background_color not in background_colors:
                raise ValueError("Invalid background color")

            print(
                colors[color] + background_colors[background_color] + text + "\033[0m"
            )
        else:
            print(colors[color] + text + "\033[0m")


def generate_random_int(min_value: int, max_value: int) -> int:
    """
    Generate a random integer within the specified range.

    Args:
        min_value (int): The minimum value.
        max_value (int): The maximum value.

    Returns:
        int: A random integer within the specified range.

    Example:
        >>> generate_random_int(1, 10)
        7

    Raises:
        ValueError: If min_value or max_value is not an integer.
        ValueError: If min_value is greater than max_value.
    """
    if not isinstance(min_value, int) or not isinstance(max_value, int):
        raise ValueError("min_value and max_value must be integers")

    if min_value > max_value:
        raise ValueError("min_value must be less than or equal to max_value")

    return random.randint(min_value, max_value)


def generate_random_decimal(min_value: float, max_value: float) -> float:
    """
    Generate a random decimal within the specified range.

    Args:
        min_value (float): The minimum value.
        max_value (float): The maximum value.

    Returns:
        float: A random decimal within the specified range.

    Example:
        >>> generate_random_decimal(1.0, 10.0)
        7.5

    Raises:
        ValueError: If min_value or max_value is not a float.
        ValueError: If min_value is greater than max_value.
    """
    if not isinstance(min_value, float) or not isinstance(max_value, float):
        raise ValueError("min_value and max_value must be floats")

    if min_value > max_value:
        raise ValueError("min_value must be less than or equal to max_value")

    return random.uniform(min_value, max_value)


def check_probability(probability: Union[int, float]) -> bool:
    """
    Return True with the specified probability.

    Args:
        probability (Union[int, float]): The probability of returning True (0.0-100.0).

    Returns:
        bool: True with the specified probability, False otherwise.

    Example:
        >>> check_probability(50)
        True  # Approximately 50% of the time

    Raises:
        ValueError: If probability is not a float or an integer.
        ValueError: If probability is not between 0.0 and 100.0.
    """
    if not isinstance(probability, (int, float)):
        raise ValueError("probability must be a float or an integer")

    if probability < 0.0 or probability > 100.0:
        raise ValueError("probability must be between 0.0 and 100.0")

    return random.uniform(0, 100) < probability


def flip_coin() -> bool:
    """
    Return True with a 50/50 chance.

    Args:
        None

    Returns:
        bool: True with a 50/50 chance, False otherwise.

    Example:
        >>> flip_coin()
        True  # Approximately 50% of the time
    """
    return check_probability(50.0)


def is_key_pressed(timeout: float = 0.1) -> bool:
    """
    Check if a key is pressed without waiting for input.

    Args:
        timeout (float): The time to wait for a key press in seconds. Default is 0.1 seconds.

    Returns:
        bool: True if a key is pressed, False otherwise.

    Example:
        >>> is_key_pressed()
        False

    Raises:
        ValueError: If timeout is not a float or is negative.
    """
    if not isinstance(timeout, float) or timeout < 0:
        raise ValueError("timeout must be a non-negative float")

    if sys.platform == "win32":
        return msvcrt.kbhit()
    else:
        if not sys.stdin.isatty():
            return False

        fd = sys.stdin.fileno()
        old_term_settings = termios.tcgetattr(fd)
        new_term_settings = termios.tcgetattr(fd)
        new_term_settings[3] &= ~termios.ICANON & ~termios.ECHO
        termios.tcsetattr(fd, termios.TCSANOW, new_term_settings)
        old_flags = fcntl.fcntl(fd, fcntl.F_GETFL)
        fcntl.fcntl(fd, fcntl.F_SETFL, old_flags | os.O_NONBLOCK)

        try:
            readable, _, _ = select([sys.stdin], [], [], timeout)
            if readable:
                key = sys.stdin.read(1)
                if key:
                    return True
        except (OSError, IOError, ValueError):
            pass
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_term_settings)
            fcntl.fcntl(fd, fcntl.F_SETFL, old_flags)

        return False


def getch() -> str:
    """
    Return a keyboard character after a key has been pressed.

    Args:
        None

    Returns:
        str: The character of the key that was pressed.

    Example:
        >>> getch()
        'a'

    Raises:
        OSError: If there is an error reading the key press.
    """
    if sys.platform == "win32":
        return msvcrt.getch().decode("utf-8")
    else:
        if not sys.stdin.isatty():
            raise OSError("sys.stdin is not a terminal")

        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(fd)
            ch = sys.stdin.read(1)
        except OSError as e:
            raise OSError(f"Failed to read key press: {e}")
        finally:
            termios.tcsetattr(fd, termios.TCSANOW, old_settings)
        return ch


def safe_input(
    data_type: type,
    validation_function: Optional[Callable[..., bool]] = lambda x: True,
    *args: Any,
    **kwargs: Any,
) -> Union[None, Any]:
    """
    Safely get user input of the specified data type and validate it.

    Args:
        data_type (type): The desired data type of the input (e.g., int, float, str).
        validation_function (Optional[Callable[..., bool]]): A function that takes the user input and returns a boolean indicating whether the input is valid. Default is a function that always returns True.
        *args (Any): Variable length argument list.
        **kwargs (Any): Arbitrary keyword arguments.

    Returns:
        Union[None, Any]: The user input converted to the specified data type if valid, otherwise None.

    Example:
        >>> safe_input(int)
        5

        >>> safe_input(int)
        None

    Raises:
        ValueError: If the input cannot be converted to the specified data type.
    """
    if not isinstance(data_type, type):
        raise ValueError("data_type must be a type")

    if not callable(validation_function):
        raise ValueError("validation_function must be callable")

    user_input = input()

    try:
        user_input = data_type(user_input)
    except ValueError:
        return None

    if validation_function(user_input, *args, **kwargs):
        return user_input

    return None


def ask_for_input(
    data_type: type,
    prompt: str = "Please enter a value: ",
    re_ask_prompt: str = "Invalid input. Please try again: ",
    validation_function: Optional[Callable[..., bool]] = lambda x: True,
    *args: Any,
    **kwargs: Any,
) -> Any:
    """
    Ask the user for an input of the specified data type. Can validate.

    Args:
        data_type (type): The desired data type of the input (e.g., int, float, str).
        prompt (str): The message to display to the user. Default is "Please enter a value:".
        re_ask_prompt (str): The message to display to the user if the input is invalid. Default is "Invalid input. Please try again."
        validation_function (Optional[Callable[..., bool]]): A function that takes the user input and returns a boolean indicating whether the input is valid. Default is a function that always returns True.
        *args (Any): Variable length argument list.
        **kwargs (Any): Arbitrary keyword arguments.

    Returns:
        Any: The user input converted to the specified data type.

    Example:
        >>> ask_for_input(int, "Enter a number:")
        Enter a number: 5
        5

        >>> ask_for_input(int, "Enter a number:", "Invalid input. Please try again.", lambda x: x > 0)
        Enter a number: -5
        Invalid input. Please try again.
        Enter a number: 5
        5

    Raises:
        ValueError: If the input cannot be converted to the specified data type.
    """
    if not isinstance(data_type, type):
        raise ValueError("data_type must be a type")

    if not isinstance(prompt, str):
        raise ValueError("prompt must be a string")

    if not isinstance(re_ask_prompt, str):
        raise ValueError("re_ask_prompt must be a string")

    if not callable(validation_function):
        raise ValueError("validation_function must be callable")

    print(prompt)
    result = safe_input(data_type, validation_function, *args, **kwargs)

    while result is None:
        print(re_ask_prompt)
        result = safe_input(data_type, validation_function, *args, **kwargs)

    return result
