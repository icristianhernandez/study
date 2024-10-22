"""
Battleship Terminal Game

The game is a terminal/text game where two player sets their ships on a
10x10 grid and then take turns to guess the position of the other
player's. The game ends when one of the player's ships are all sunk.

The design code take consideration of the following:
- Documentation
- Code Readability and Self-Explanatory
- Code Structure
- OOP Principles
- Code Reusability (Extensibility to graphics ui and game mechanics)
- Type hints, type validation and logic validation
"""

import random
import os
import time
from collections import namedtuple
from typing import Callable

SETTINGS: dict = {
    "grid_rows": 10,
    "grid_columns": 10,
    "ships_data": {},
    "player_count": 2,
    "player_names": ["Player 1", "Player 2"],
    "sprites": {
        "ship": "S",
        "hit": "X",
        "miss": "O",
        "empty": " ",
        "grid": " ",
        "separator": "|",
        "horizontal": "-",
        "vertical": "|",
        "corner": "+",
        "top": "ABCDEFGHIJ",
        "left": "0123456789",
    },
}

Coordinates = namedtuple("Coordinates", ["x", "y"])


def get_substrings(string: str, separator: str = " ") -> list[str]:
    return string.split(separator)


def ask_player_ships() -> dict[str, Coordinates]:
    """
    Ask the player to place the ships.

    Returns
    -------
    dict[str, Coordinates]
        The ships placement of the player.
    """
    ships = {}
    for ship_name, ship_data in SETTINGS["ships_data"].items():
        print(f"Place the {ship_name} with size {ship_data['size']}")
        location = get_substrings(input("Enter the location: "))
        ships[ship_name] = Coordinates(int(location[0]), int(location[1]))
    return ships


def ask_player_guess() -> Coordinates:
    """
    Ask the player to make a guess.

    Returns
    -------
    Coordinates
        The guess of the player.
    """
    guess = get_substrings(input("Enter your guess: "))
    return Coordinates(int(guess[0]), int(guess[1]))


class BoardElement:
    """
    A class to represent a board element. Can be an unique entitie or a
    repeatable one.

    Attributes
    ----------
    element_id: int
        The id of the element in the game. Only the GameElementsManager should
        be able to set this attribute
    name : str
        The name of the element
    shape: str
        The sprite of the element
    is_repeatable: bool
        If the element can be repeated in the board
    take_action: function(action: str) -> TODO: Define the return
        The action that the element takes when is hit
    initial_coordinate : Coordinates
        The initial coordinate of the element
    direction : str
        The direction of the element

    Methods
    -------
    take_action(action: str) -> TODO: Define the return
        The action that the element takes when is hit
    """

    # TODO: Define the return and argument of the take_action method

    def __init__(
        self,
        name: str,
        shape: str,
        is_repeatable: bool,
        take_action_behaviour: Callable,
        initial_coordinate: Coordinates,
        direction: str,
    ) -> None:

        self._element_id = 0
        self._name = name
        self._shape = shape
        self.is_repeatable = is_repeatable
        self._take_action_behaviour = take_action_behaviour
        self._initial_coordinate = initial_coordinate
        self._direction = direction

    def __str__(self) -> str:
        return self._shape

    def __repr__(self) -> str:
        return self.shape

    # TODO:
    def take_action(self, action: str):
        """
        The action that the element takes when is hit.

        Parameters
        ----------
        action : str
            The action to take.

        Returns
        -------

        """
        return self._take_action_behaviour(action)

    @property
    def id(self) -> int:
        """The id property."""
        return self._element_id

    @property
    def name(self) -> str:
        """The name property."""
        return self._name

    @name.setter
    def name(self, value: str) -> None:
        self._name = value

    @property
    def shape(self) -> str:
        """The shape property."""
        return self._shape

    @shape.setter
    def shape(self, value: str) -> None:
        self._shape = value

    @property
    def is_repeatable(self) -> bool:
        """The is_repeatable property."""
        return self.is_repeatable

    @is_repeatable.setter
    def is_repeatable(self, value: bool) -> None:
        self.is_repeatable = value

    @property
    def take_action_behaviour(self) -> Callable:
        """The take_action_behaviour property."""
        return self._take_action_behaviour

    @take_action_behaviour.setter
    def take_action_behaviour(self, value: Callable) -> None:
        self._take_action_behaviour = value

    @property
    def initial_coordinate(self) -> Coordinates:
        """The initial_coordinate property."""
        return self._initial_coordinate

    @initial_coordinate.setter
    def initial_coordinate(self, value: Coordinates) -> None:
        self._initial_coordinate = value

    @property
    def direction(self) -> str:
        """The direction property."""
        return self._direction

    @direction.setter
    def direction(self, value: str) -> None:
        self._direction = value


class GameElementsManager:
    """
    A class to manage the game elements. This class is responsible to set ids and
    index based on the elements.

    Attributes
    ----------
    elements: dict[id: int, element: BoardElement]
        The dictionary of elements in the game

    Methods
    -------
    add_element(element: BoardElement) -> None
        Add an element to the elements dictionary and set the id
    get_element_by_id(id: int) -> BoardElement
        Get an element by id from the elements dictionary
    get_element_by_filter(filter: Callable) -> BoardElement
        Get an element by filter from the elements dictionary
    get_elements() -> dict[id: int, element: BoardElement]
        Get all the elements in the elements dictionary
    """

    def __init__(self) -> None:
        self._elements = {}
        self._next_available_id = 1

    def add_element(self, element: BoardElement) -> None:
        """
        Add an element to the elements dictionary and set the id.

        Parameters
        ----------
        element : BoardElement
            The element to be added to the game.
        """
        if not element.is_repeatable:
            for existing_element in self._elements.values():
                if existing_element.name == element.name:
                    raise ValueError(
                        f"Element '{element.name}' is not repeatable and already exists on the board."
                    )
        element._element_id = self._next_available_id
        self._elements[self._next_available_id] = element
        self._next_available_id += 1

    def get_element_by_id(self, id: int) -> BoardElement:
        """
        Get an element by id from the elements dictionary.

        Parameters
        ----------
        id : int
            The id of the element to retrieve.

        Returns
        -------
        BoardElement
            The element with the specified id.

        Raises
        ------
        KeyError
            If the element with the specified id is not found.
        """
        return self._elements[id]

    def get_element_by_filter(
        self, filter: Callable[[BoardElement], bool]
    ) -> BoardElement:
        """
        Get an element by filter from the elements dictionary.

        Parameters
        ----------
        filter : Callable[[BoardElement], bool]
            A function to filter elements.

        Returns
        -------
        BoardElement
            The element that matches the filter.

        Raises
        ------
        ValueError
            If no element matches the filter.
        """
        for element in self._elements.values():
            if filter(element):
                return element

        raise ValueError("Element not found with the given filter.")


class GameBoard:
    """
    A class to represent a game board.

    Attributes
    ----------
    grid: list[list[int]]
        The grid of the game board. Stores the id of the elements in the board.

    Methods
    -------
    get_element_id_at_coordinate(coordinate: Coordinates, elements_manager: GameElementsManager) -> BoardElement
        Get the element at the specified coordinate
    set_element_id_at_coordinate(coordinate: Coordinates, element_id: int) -> None
        Set the element at the specified coordinate
    """

    def __init__(self, grid_rows: int, grid_columns: int) -> None:
        self._grid = [[0 for _ in range(grid_columns)] for _ in range(grid_rows)]

    def get_element_id_at_coordinate(self, coordinate: Coordinates) -> BoardElement:
        """
        Get the element at the specified coordinate.

        Parameters
        ----------
        coordinate : Coordinates
            The coordinate to get the element.

        Returns
        -------
        BoardElement
            The element at the specified coordinate.
        """

        if (
            coordinate.x < 0
            or coordinate.x >= len(self._grid[0])
            or coordinate.y < 0
            or coordinate.y >= len(self._grid)
        ):
            raise ValueError("Coordinate out of bounds.")

        return self._grid[coordinate.y][coordinate.x]

    def set_element_id_at_coordinate(
        self, coordinate: Coordinates, element_id: int
    ) -> None:
        """
        Set the element at the specified coordinate.

        Parameters
        ----------
        coordinate : Coordinates
            The coordinate to set the element.
        element_id : int
            The id of the element to set.
        """
        self._grid[coordinate.y][coordinate.x] = element_id


class Player:
    """
    A class to represent a player.

    Attributes
    ----------
    name: str
        The name of the player
    ships_id: list[int]
        The ships id of the player

    Methods
    -------
    ask_placement_ships() -> dict[name: str, location: Coordinates]
        Ask the player to place the ships
    ask_guess() -> Coordinates
        Ask the player to make a guess
    """

    def __init__(
        self,
        name: str,
        ask_placement_ship_function: Callable = ask_player_ships,
        ask_player_guess: Callable = ask_player_guess,
    ) -> None:

        self._name = name
        self._ships_id = []
        # ask_player function that return an string with each value separated by a space
        self.ask_placement_ship_function = ask_placement_ship_function
        self.ask_guess_function = ask_player_guess

    def ask_placement_ships(self) -> dict[str, Coordinates]:
        """
        Ask the player to place the ships.

        Returns
        -------
        dict[str, Coordinates]
            The ships placement of the player.
        """
        return self.ask_placement_ship_function()

    def ask_guess(self) -> Coordinates:
        """
        Ask the player to make a guess.

        Returns
        -------
        Coordinates
            The guess of the player.
        """
        return self.ask_guess_function()
