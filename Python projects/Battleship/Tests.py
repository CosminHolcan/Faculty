import unittest
from Service import *
from Validator import *

class Tests(unittest.TestCase) :

    def test_create_square(self):
        validator_square = Validation_Square()
        row = 0
        column = "A"
        square = Square(row, column)
        self.assertTrue(square.get_row() == 0)
        self.assertTrue(square.get_column() == "A")
        self.assertTrue(square.get_symbol() == "0")
        new_symbol = "X"
        square.set_symbol(new_symbol)
        self.assertTrue(square.get_symbol() == "X")
        other_square = Square(row, column)
        self.assertTrue(square == other_square)
        row = 10
        column = ""
        square3 = Square(row, column)
        self.assertRaises(ValueError, validator_square.check_square, square3)

    def test_initialise_user(self):
        validator_square = Validation_Square()
        repo_squares_user = Repo_squares()
        repo_squares_computer = Repo_squares()
        srv_squares = Service_squares(repo_squares_user, repo_squares_computer, validator_square)
        srv_squares.initialise_user()
        self.assertTrue(len(srv_squares.get_entities_user()) == 64)
        square= Square(0, "A")
        self.assertTrue(srv_squares.get_entities_user()[0] == square)

    def test_initialise_computer(self):
        validator_square = Validation_Square()
        repo_squares_user = Repo_squares()
        repo_squares_computer = Repo_squares()
        srv_squares = Service_squares(repo_squares_user, repo_squares_computer, validator_square)
        srv_squares.initialise_computer()
        self.assertTrue(len(srv_squares.get_entities_computer()) == 64)
        square = Square(7, "H")
        self.assertTrue(srv_squares.get_entities_computer()[-1] == square)

    def test_battleship_computer(self):
        validator_square = Validation_Square()
        repo_squares_user = Repo_squares()
        repo_squares_computer = Repo_squares()
        srv_squares = Service_squares(repo_squares_user, repo_squares_computer, validator_square)
        srv_squares.initialise_user()
        srv_squares.initialise_computer()
        srv_squares.battleship_computer()
        self.assertTrue(srv_squares.number_of_1_computer() == 4)

    def test_cruiser_computer(self):
        validator_square = Validation_Square()
        repo_squares_user = Repo_squares()
        repo_squares_computer = Repo_squares()
        srv_squares = Service_squares(repo_squares_user, repo_squares_computer, validator_square)
        srv_squares.initialise_user()
        srv_squares.initialise_computer()
        srv_squares.battleship_computer()
        srv_squares.cruiser_computer()
        self.assertTrue(srv_squares.number_of_1_computer() == 7)

    def test_destroyer_computer(self):
        validator_square = Validation_Square()
        repo_squares_user = Repo_squares()
        repo_squares_computer = Repo_squares()
        srv_squares = Service_squares(repo_squares_user, repo_squares_computer, validator_square)
        srv_squares.initialise_user()
        srv_squares.initialise_computer()
        srv_squares.battleship_computer()
        srv_squares.cruiser_computer()
        srv_squares.destroyer_computer()
        self.assertTrue(srv_squares.number_of_1_computer() == 9)
        self.assertTrue(srv_squares.check_finish_user() == 0)

    def test_battleship_user(self):
        validator_square = Validation_Square()
        repo_squares_user = Repo_squares()
        repo_squares_computer = Repo_squares()
        srv_squares = Service_squares(repo_squares_user, repo_squares_computer, validator_square)
        srv_squares.initialise_user()
        srv_squares.initialise_computer()
        square = Square(0, "A")
        srv_squares.battleship_user(square, "S")
        self.assertTrue(srv_squares.get_entities_user()[0].get_symbol() == "1")
        self.assertTrue(srv_squares.get_entities_user()[8].get_symbol() == "1")
        self.assertTrue(srv_squares.get_entities_user()[16].get_symbol() == "1")
        self.assertTrue(srv_squares.get_entities_user()[24].get_symbol() == "1")
        self.assertTrue(srv_squares.number_of_1_user() == 4)

    def test_cruiser_user(self):
        validator_square = Validation_Square()
        repo_squares_user = Repo_squares()
        repo_squares_computer = Repo_squares()
        srv_squares = Service_squares(repo_squares_user, repo_squares_computer, validator_square)
        srv_squares.initialise_user()
        srv_squares.initialise_computer()
        square = Square(0, "A")
        srv_squares.cruiser_user(square, "S")
        self.assertTrue(srv_squares.get_entities_user()[0].get_symbol() == "1")
        self.assertTrue(srv_squares.get_entities_user()[8].get_symbol() == "1")
        self.assertTrue(srv_squares.get_entities_user()[16].get_symbol() == "1")
        self.assertTrue(srv_squares.get_entities_user()[24].get_symbol() == "0")

    def test_destroyer_user(self):
        validator_square = Validation_Square()
        repo_squares_user = Repo_squares()
        repo_squares_computer = Repo_squares()
        srv_squares = Service_squares(repo_squares_user, repo_squares_computer, validator_square)
        srv_squares.initialise_user()
        srv_squares.initialise_computer()
        square = Square(0, "A")
        srv_squares.destroyer_user(square, "S")
        self.assertTrue(srv_squares.get_entities_user()[0].get_symbol() == "1")
        self.assertTrue(srv_squares.get_entities_user()[8].get_symbol() == "1")
        self.assertTrue(srv_squares.get_entities_user()[16].get_symbol() == "0")
        self.assertTrue(srv_squares.get_entities_user()[24].get_symbol() == "0")

    def test_trying_computer(self):
        validator_square = Validation_Square()
        repo_squares_user = Repo_squares()
        repo_squares_computer = Repo_squares()
        srv_squares = Service_squares(repo_squares_user, repo_squares_computer, validator_square)
        srv_squares.initialise_user()
        srv_squares.initialise_computer()
        srv_squares.battleship_computer()
        srv_squares.cruiser_computer()
        srv_squares.destroyer_computer()
        square = Square(0, "A")
        square2 = Square(0, "B")
        square3 = Square(0, "C")
        srv_squares.battleship_user(square, "S")
        srv_squares.cruiser_user(square2, "S")
        srv_squares.destroyer_user(square3, "S")
        srv_squares.trying_of_computer()
        self.assertTrue(srv_squares.number_of_X_V_user() == 1)
        self.assertTrue(srv_squares.check_finish_computer() == 0)
        for i in range(20) :
            srv_squares.trying_of_computer()
            self.assertTrue(srv_squares.number_of_X_V_user() <= i+2)



