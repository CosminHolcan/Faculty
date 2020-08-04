from Repo import *
from Errors import *
from Validator import *
import random

class Service_squares(object) :

    def __init__(self, repo_squares_user,repo_squares_computer, validator_square):
        # this function creates a Service variable
        # input : repo_squares_user, repo_squares_computer - Repo_sqaures variables, validator_square - Validation_square variable
        # ouput : a Service variable
        self.__repo_squares_user = repo_squares_user
        self.__repo_squares_computer = repo_squares_computer
        self.__validator_square = validator_square
        self.__next_moves = [ ]

    def initialise_user(self):
        # this function initialise the board of user
        # input : -
        # output : the board of user is initialised with 64 squares
        letters = ["A", "B", "C", "D", "E", "F", "G", "H"]
        for i in range(8) :
            for j in range(8) :
                column = letters[j]
                row = i
                square = Square(row, column)
                self.__repo_squares_user.add_element(square)

    def initialise_computer(self):
        # this function initialise the board of computer
        # input : -
        # output : the board of computer is initialised with 64 squares
        letters = ["A", "B", "C", "D", "E", "F", "G", "H"]
        for i in range(8):
            for j in range(8):
                column = letters[j]
                row = i
                square = Square(row, column)
                self.__repo_squares_computer.add_element(square)

    def battleship_user(self, square, direction):
        # this function will try to create a battleship according to parameters square and direction
        # input : square - a Square variable and direction - string
        # output : a battleship if it is possible to create or an error message
        dict_letters = {
            "A" : 0,
            "B" : 1,
            "C" : 2,
            "D" : 3,
            "E" : 4,
            "F" : 5,
            "G" : 6,
            "H" : 7
        }
        letters =["A", "B", "C", "D", "E", "F", "G", "H"]
        self.__validator_square.check_square(square)
        if direction not in ["N", "S", "E", "W"] :
            raise ValueError ("Invalid direction !")
        column = square.get_column()
        nr_column = dict_letters[column]
        row = square.get_row()
        if direction == "N" :
            if row < 3 :
                raise RepoError("It's impossible to create a battleship here !")
            square2 = Square(row - 1, column)
            square3 = Square(row - 2, column)
            square4 = Square(row - 3, column)
        if direction == "S" :
            if row > 4 :
                raise RepoError("It's impossible to create a battleship here !")
            square2 = Square(row + 1, column)
            square3 = Square(row + 2, column)
            square4 = Square(row + 3, column)
        if direction == "E" :
            if column > "E" :
                raise RepoError("It's impossible to create a battleship here !")
            square2 = Square(row, letters[nr_column + 1])
            square3 = Square(row, letters[nr_column + 2])
            square4 = Square(row, letters[nr_column + 3])
        if direction == "W" :
            if column < "D" :
                raise RepoError("It's impossible to create a battleship here !")
            square2 = Square(row, letters[nr_column - 1])
            square3 = Square(row, letters[nr_column - 2])
            square4 = Square(row, letters[nr_column - 3])
        squares_list = [square, square2, square3, square4]
        for element in squares_list :
            if(self.__repo_squares_user.check_add_to_play(element)) == False :
                raise RepoError("This square was already chosen !")
        for element in squares_list :
            self.__repo_squares_user.modify_element(element, "1")

    def cruiser_user(self, square, direction):
        # this function will try to create a cruiser according to parameters square and direction
        # input : square - a Square variable and direction - string
        # output : a cruiser if it is possible to create or an error message
        dict_letters = {
            "A": 0,
            "B": 1,
            "C": 2,
            "D": 3,
            "E": 4,
            "F": 5,
            "G": 6,
            "H": 7
        }
        letters = ["A", "B", "C", "D", "E", "F", "G", "H"]
        self.__validator_square.check_square(square)
        if direction not in ["N", "S", "E","W"] :
            raise ValueError ("Invalid direction !")
        column = square.get_column()
        nr_column = dict_letters[column]
        row = square.get_row()
        if direction == "N":
            if row < 2:
                raise RepoError("It's impossible to create a cruiser here !")
            square2 = Square(row - 1, column)
            square3 = Square(row - 2, column)
        if direction == "S":
            if row > 5:
                raise RepoError("It's impossible to create a cruiser here !")
            square2 = Square(row + 1, column)
            square3 = Square(row + 2, column)
        if direction == "E":
            if column > "F":
                raise RepoError("It's impossible to create a cruiser here !")
            square2 = Square(row, letters[nr_column + 1])
            square3 = Square(row, letters[nr_column + 2])
        if direction == "W":
            if column < "C":
                raise RepoError("It's impossible to create a cruiser here !")
            square2 = Square(row, letters[nr_column - 1])
            square3 = Square(row, letters[nr_column - 2])
        squares_list = [square, square2, square3]
        for element in squares_list:
            if (self.__repo_squares_user.check_add_to_play(element)) == False:
                raise RepoError("This square was already chosen !")
        for element in squares_list:
            self.__repo_squares_user.modify_element(element, "1")

    def destroyer_user(self, square, direction):
        # this function will try to create a destroyer according to parameters square and direction
        # input : square - a Square variable and direction - string
        # output : a destroyer if it is possible to create or an error message
        dict_letters = {
            "A": 0,
            "B": 1,
            "C": 2,
            "D": 3,
            "E": 4,
            "F": 5,
            "G": 6,
            "H": 7
        }
        letters = ["A", "B", "C", "D", "E", "F", "G", "H"]
        self.__validator_square.check_square(square)
        if direction not in ["N", "S", "E","W"] :
            raise ValueError ("Invalid direction !")
        column = square.get_column()
        nr_column = dict_letters[column]
        row = square.get_row()
        if direction == "N":
            if row < 1:
                raise RepoError("It's impossible to create a destroyer here !")
            square2 = Square(row - 1, column)
        if direction == "S":
            if row > 6:
                raise RepoError("It's impossible to create a destroyer here !")
            square2 = Square(row + 1, column)
        if direction == "E":
            if column > "G":
                raise RepoError("It's impossible to create a destroyer here !")
            square2 = Square(row, letters[nr_column + 1])
        if direction == "W":
            if column < "H":
                raise RepoError("It's impossible to create a destroyer here !")
            square2 = Square(row, letters[nr_column - 1])
        squares_list = [square, square2]
        for element in squares_list:
            if (self.__repo_squares_user.check_add_to_play(element)) == False:
                raise RepoError("This square was already chosen !")
        for element in squares_list:
            self.__repo_squares_user.modify_element(element, "1")

    def battleship_computer(self):
        # this function will create a battleship for computer randomly
        # input : -
        # output : a battleship
        directions = ["N", "S", "W", "E"]
        letters = ["A", "B", "C", "D", "E", "F", "G", "H"]
        while self.__repo_squares_computer.number_of_ones() != 4 :
            try:
                nr_direction = random.randint(0,3)
                direction = directions[nr_direction]
                nr_column = random.randint(0, 7)
                column = letters[nr_column]
                row = random.randint(1, 8)
                square = Square(row, column)
                if direction == "N":
                    if row < 3:
                        raise RepoErrorComputer("It's impossible to create a battleship here !")
                    square2 = Square(row - 1, column)
                    square3 = Square(row - 2, column)
                    square4 = Square(row - 3, column)
                if direction == "S":
                    if row > 4:
                        raise RepoErrorComputer("It's impossible to create a battleship here !")
                    square2 = Square(row + 1, column)
                    square3 = Square(row + 2, column)
                    square4 = Square(row + 3, column)
                if direction == "E":
                    if column > "E":
                        raise RepoErrorComputer("It's impossible to create a battleship here !")
                    square2 = Square(row, letters[nr_column + 1])
                    square3 = Square(row, letters[nr_column + 2])
                    square4 = Square(row, letters[nr_column + 3])
                if direction == "W":
                    if column < "D":
                        raise RepoErrorComputer("It's impossible to create a battleship here !")
                    square2 = Square(row, letters[nr_column - 1])
                    square3 = Square(row, letters[nr_column - 2])
                    square4 = Square(row, letters[nr_column - 3])
                squares_list = [square, square2, square3, square4]
                for element in squares_list:
                    if (self.__repo_squares_computer.check_add_to_play(element)) == False:
                        raise RepoErrorComputer("This square was already chosen !")
                for element in squares_list:
                    self.__repo_squares_computer.modify_element(element, "1")
            except RepoErrorComputer as re:
                pass

    def cruiser_computer(self):
        # this function will create a cruiser for computer randomly
        # input : -
        # output : a cruiser
        directions = ["N", "S", "W", "E"]
        letters = ["A", "B", "C", "D", "E", "F", "G", "H"]
        while self.__repo_squares_computer.number_of_ones() != 7 :
            try:
                nr_direction = random.randint(0,3)
                direction = directions[nr_direction]
                nr_column = random.randint(0, 7)
                column = letters[nr_column]
                row = random.randint(1, 8)
                square = Square(row, column)
                if direction == "N":
                    if row < 2:
                        raise RepoErrorComputer("It's impossible to create a cruiser here !")
                    square2 = Square(row - 1, column)
                    square3 = Square(row - 2, column)
                if direction == "S":
                    if row > 5:
                        raise RepoErrorComputer("It's impossible to create a cruiser here !")
                    square2 = Square(row + 1, column)
                    square3 = Square(row + 2, column)
                if direction == "E":
                    if column > "F":
                        raise RepoErrorComputer("It's impossible to create a cruiser here !")
                    square2 = Square(row, letters[nr_column + 1])
                    square3 = Square(row, letters[nr_column + 2])
                if direction == "W":
                    if column < "C":
                        raise RepoErrorComputer("It's impossible to create a cruiser here !")
                    square2 = Square(row, letters[nr_column - 1])
                    square3 = Square(row, letters[nr_column - 2])
                squares_list = [square, square2, square3]
                for element in squares_list:
                    if (self.__repo_squares_computer.check_add_to_play(element)) == False:
                        raise RepoErrorComputer("This square was already chosen !")
                for element in squares_list:
                    self.__repo_squares_computer.modify_element(element, "1")
            except RepoErrorComputer as re:
                pass

    def destroyer_computer(self):
        # this function will create a destroyer for computer randomly
        # input : -
        # output : a destroyer
        directions = ["N", "S", "W", "E"]
        letters = ["A", "B", "C", "D", "E", "F", "G", "H"]
        while self.__repo_squares_computer.number_of_ones() != 9 :
            try:
                nr_direction = random.randint(0,3)
                direction = directions[nr_direction]
                nr_column = random.randint(0, 7)
                column = letters[nr_column]
                row = random.randint(1,8)
                square = Square(row, column)
                if direction == "N":
                    if row < 1:
                        raise RepoErrorComputer("It's impossible to create a destroyer here !")
                    square2 = Square(row - 1, column)
                if direction == "S":
                    if row > 6:
                        raise RepoErrorComputer("It's impossible to create a destroyer here !")
                    square2 = Square(row + 1, column)
                if direction == "E":
                    if column > "G":
                        raise RepoErrorComputer("It's impossible to create a destroyer here !")
                    square2 = Square(row, letters[nr_column + 1])
                if direction == "W":
                    if column < "H":
                        raise RepoErrorComputer("It's impossible to create a destroyer here !")
                    square2 = Square(row, letters[nr_column - 1])
                squares_list = [square, square2]
                for element in squares_list:
                    if (self.__repo_squares_computer.check_add_to_play(element)) == False:
                        raise RepoErrorComputer("This square was already chosen !")
                for element in squares_list:
                    self.__repo_squares_computer.modify_element(element, "1")
            except RepoErrorComputer as re:
                pass


    def trying_of_user(self, square):
        # this function will modify the symbol of square chosen by the user : if he hits, the symbol will become V, if not it will become X
        # input : square - a Square variable
        # output : the symbol will be modified
        self.__validator_square.check_square(square)
        square_in_list = self.__repo_squares_computer.search_element(square)
        if square_in_list.get_symbol() == "1" :
            self.__repo_squares_computer.modify_element(square_in_list, "V")
        if square_in_list.get_symbol() == "0" :
            self.__repo_squares_computer.modify_element(square_in_list, "X")

    def trying_of_computer(self):
        # this function will modify the symbol of a computer's square : if he hits, the symbol will become X, if not it will become V
        # input : square - a Square variable
        # output : the symbol will be modified
        letters = ["A", "B", "C", "D", "E", "F", "G", "H"]
        dict_letters = {
            "A" : 0,
            "B" : 1,
            "C" : 2,
            "D" : 3,
            "E" : 4,
            "F" : 5,
            "G" : 6,
            "H" : 7
        }
        if len(self.__next_moves) == 0 :
            nr_letter = random.randint(0, 7)
            letter = letters[nr_letter]
            column = letter
            row = random.randint(0, 7)
            square_computer = Square(row, column)
            square_in_list = self.__repo_squares_user.search_element(square_computer)
            while square_in_list.get_symbol() == "V" or square_in_list.get_symbol() == "X" :
                nr_letter = random.randint(0, 7)
                letter = letters[nr_letter]
                column = letter
                row = random.randint(0, 7)
                square_computer = Square(row, column)
                square_in_list = self.__repo_squares_user.search_element(square_computer)
            if square_in_list.get_symbol() == "1":
                self.__repo_squares_user.modify_element(square_in_list, "X")
                nr_letter_aux = nr_letter -1
                if nr_letter_aux >= 0  :
                    square = Square(row, letters[nr_letter_aux])
                    square_in_list = self.__repo_squares_user.search_element(square)
                    self.__next_moves.append(square_in_list)
                nr_letter_aux = nr_letter + 1
                if nr_letter_aux <= 7  :
                    square = Square(row, letters[nr_letter_aux])
                    square_in_list = self.__repo_squares_user.search_element(square)
                    self.__next_moves.append(square_in_list)
                row_aux = row - 1
                if row_aux >= 0  :
                    square = Square(row_aux, column)
                    square_in_list = self.__repo_squares_user.search_element(square)
                    self.__next_moves.append(square_in_list)
                row_aux = row+1
                if row_aux <= 7  :
                    square = Square(row_aux, column)
                    square_in_list = self.__repo_squares_user.search_element(square)
                    self.__next_moves.append(square_in_list)
            elif square_in_list.get_symbol() == "0" :
                self.__repo_squares_user.modify_element(square_in_list, "V")
        else :
            square = self.__next_moves[0]
            self.__next_moves.remove(square)
            while (square.get_symbol() == "X" or square.get_symbol() == "V") and len(self.__next_moves) >=1 :
                square = self.__next_moves[0]
                self.__next_moves.remove(square)
            if square.get_symbol() == "1":
                self.__repo_squares_user.modify_element(square, "X")
                column = square.get_column()
                row = square.get_row()
                nr_letter = dict_letters[column]
                nr_letter_aux = nr_letter - 1
                if nr_letter_aux >= 0:
                    square = Square(row, letters[nr_letter_aux])
                    square_in_list = self.__repo_squares_user.search_element(square)
                    if square_in_list not in self.__next_moves :
                        self.__next_moves.append(square_in_list)
                nr_letter_aux = nr_letter + 1
                if nr_letter_aux <= 7:
                    square = Square(row, letters[nr_letter_aux])
                    square_in_list = self.__repo_squares_user.search_element(square)
                    if square_in_list not in self.__next_moves :
                        self.__next_moves.append(square_in_list)
                row_aux = row - 1
                if row_aux >= 0:
                    square = Square(row_aux, column)
                    square_in_list = self.__repo_squares_user.search_element(square)
                    if square_in_list not in self.__next_moves :
                        self.__next_moves.append(square_in_list)
                row_aux = row + 1
                if row_aux <= 7:
                    square = Square(row_aux, column)
                    square_in_list = self.__repo_squares_user.search_element(square)
                    if square_in_list not in self.__next_moves :
                        self.__next_moves.append(square_in_list)
            elif square.get_symbol() == "0" :
                self.__repo_squares_user.modify_element(square, "V")

    def number_of_1_user(self):
        # this function returns the number of squares of user with symbol 1
        # input : -
        # output : the number of squares of user with symbol 1
        return self.__repo_squares_user.number_of_ones()

    def number_of_1_computer(self):
        # this function returns the number of squares of computer with symbol 1
        # input : -
        # output : the number of squares of computer with symbol 1
        return self.__repo_squares_computer.number_of_ones()

    def number_of_X_V_user(self):
        # this function returns the number of squares of computer with symbol X or V
        # input : -
        # output : the number of squares of computer with symbol X or V
        nr = 0
        for square in self.__repo_squares_user.get_entities():
            if square.get_symbol() == "X" or square.get_symbol() == "V":
                nr = nr + 1
        return nr

    def check_finish_user(self):
        # this function checks if user win
        # input : -
        # output : 1 if user won, 0 if not
        nr = 0
        for square in self.__repo_squares_computer.get_entities() :
            if square.get_symbol() == "V" :
                nr =nr +1
        if nr == 9 :
            return 1
        else :
            return 0

    def check_finish_computer(self):
        # this function checks if computer win
        # input : -
        # output : 1 if computer won, 0 if not
        nr = 0
        for square in self.__repo_squares_user.get_entities():
            if square.get_symbol() == "X":
                nr = nr + 1
        if nr == 9:
            return 1
        return 0

    def get_entities_computer(self):
        # returns the list of user's squares
        # input : -
        # output : the list of user's squares
        return self.__repo_squares_computer.get_entities()

    def get_entities_user(self):
        # returns the list of computer's squares
        # input : -
        # output : the list of computer's squares
        return self.__repo_squares_user.get_entities()


