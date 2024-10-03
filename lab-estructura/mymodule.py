"""
mymodule.py

Utility functions for console I/O, random number generation, and keyboard input.

Functions:
    - clear_console_screen: Clear the console screen on both Windows and non-Windows systems.
    - pause: Pause the execution until the user presses a key.
    - print_with_color: Print a string with the specified color on both Windows and non-Windows systems.
    - generate_random_int: Generate a random integer within the specified range.
    - check_probability: Return True with the specified probability.
    - is_key_pressed: Check if a key is pressed without waiting for input.
    - getch: Return a keyboard character after a key has been pressed.

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
from typing import Union

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


def print_with_color(text: str, color: str) -> None:
    """
    Print a string with the specified color on both Windows and non-Windows systems.

    Args:
        text (str): The text to print.
        color (str): The color code (e.g., 'red', 'green', 'blue').

    Returns:
        None

    Example:
        >>> print_with_color("Hello, World!", "red")

    Raises:
        ValueError: If text or color is not a string.
        ValueError: If color is not a valid color.
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
