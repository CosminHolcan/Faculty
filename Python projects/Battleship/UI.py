from Service import *
from texttable import Texttable

class UI(object) :

    def __init__(self, srv_squares):
        self.__srv_squares = srv_squares

    def ui_add_battleship(self):
        column = input("Please introduce the column of the first square(A->H) : ").strip()
        row = input("Please introduce the row of the first square(1->8) : ").strip()
        direction= input("Please introduce the direction of the battleship(N,S,E,W) : ").strip()
        if row.isdigit() == False :
            raise ValueError("The row should be a number from 1 to 8 !")
        row = int(row)
        row = row- 1
        square = Square(row, column)
        self.__srv_squares.battleship_user(square, direction)

    def ui_add_cruiser(self):
        column = input("Please introduce the column of the first square(A->H) : ").strip()
        row = input("Please introduce the row of the first square(1->8) : ").strip()
        direction = input("Please introduce the direction of the cruiser(N,S,E,W) : ").strip()
        if row.isdigit() == False :
            raise ValueError("The row should be a number from 1 to 8 !")
        row = int(row)
        row = row - 1
        square = Square(row, column)
        self.__srv_squares.cruiser_user(square, direction)

    def ui_add_destroyer(self):
        column = input("Please introduce the column of the first square(A->H) : ").strip()
        row = input("Please introduce the row of the first square(1->8) : ").strip()
        direction = input("Please introduce the direction of the destroyer(N,S,E,W) : ").strip()
        flag = False
        if row.isdigit() == False :
            raise ValueError("The row should be a number from 1 to 8 !")
        row = int(row)
        row = row - 1
        square = Square(row, column)
        self.__srv_squares.destroyer_user(square, direction)

    def ui_trying_user(self):
        column = input("Please introduce the column of the first square(A->H) : ").strip()
        row = input("Please introduce the row of the first square(1->8) : ").strip()
        if row.isdigit() == False :
            raise ValueError("The row should be a number from 1 to 8 !")
        row = int(row)
        row = row - 1
        square = Square(row, column)
        self.__srv_squares.trying_of_user(square)
        self.__srv_squares.trying_of_computer()

    def ui_display_repo_user(self):
        list_squares = self.__srv_squares.get_entities_user()
        table = Texttable()
        list_letters = ["","A", "B", "C", "D", "E", "F", "G", "H"]
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
        for x in range(0, 81, 9):
            if x == 0 :
                row = list()
                for y in range(9) :
                    row.append(list_letters[y])
                table.add_row(row)
            else :
                row = list()
                for y in range(9) :
                    if y == 0 :
                        row.append(x/9)
                    else :
                        if list_squares[(x//9-1)*8+y-1].get_symbol() == "1" :
                            row.append("OK")
                        elif list_squares[(x//9-1)*8+y-1].get_symbol() == "0" :
                            row.append("0")
                        elif list_squares[(x // 9 - 1) * 8 + y - 1].get_symbol() == "X":
                            row.append("HIT")
                        elif list_squares[(x // 9 - 1) * 8 + y - 1].get_symbol() == "V":
                            row.append("MISSED")
                table.add_row(row)
        print(table.draw())

    def ui_display_repo_computer(self):
        list_squares = self.__srv_squares.get_entities_computer()
        table = Texttable()
        list_letters = ["", "A", "B", "C", "D", "E", "F", "G", "H"]
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
        for x in range(0, 81, 9):
            if x == 0:
                row = list()
                for y in range(9):
                    row.append(list_letters[y])
                table.add_row(row)
            else:
                row = list()
                for y in range(9):
                    if y == 0:
                        row.append(x / 9)
                    else:
                        if list_squares[(x//9-1)*8+y-1].get_symbol() == "1" :
                            row.append("0")
                        elif list_squares[(x//9-1)*8+y-1].get_symbol() == "0" :
                            row.append("0")
                        elif list_squares[(x // 9 - 1) * 8 + y - 1].get_symbol() == "X":
                            row.append("MISSED")
                        elif list_squares[(x // 9 - 1) * 8 + y - 1].get_symbol() == "V":
                            row.append("HIT")
                table.add_row(row)
        print(table.draw())

    def menu(self):
        commands = {
            "1" : self.ui_add_battleship,
            "2" : self.ui_add_cruiser,
            "3" : self.ui_add_destroyer,
            "4" : self.ui_trying_user,
            "5" : self.ui_display_repo_computer,
            "6" : self.ui_display_repo_user
        }
        list_of_commands = list()
        print("The command 1 is used to add a battleship. This command can be done just one time !!")
        print("The command 2 is used to add a cruiser. This command can be done just one time !!")
        print("The command 3 is used to add a destroyer. This command can be done just one time !!")
        print("The command 4 is used to try to destroy a ship of the opponent . The computer will also make a move.")
        print("The command 5 is used to display the grid of the computer.")
        print("The command 6 is used to display the grid of the user.")
        while True :
            cmd = input("Please introduce your command : ").strip()
            if cmd in commands :
                if cmd == "1" or cmd == "2" or cmd == "3" :
                    if cmd in list_of_commands :
                        print("This operation can't be done anymore !")
                    else :
                        try :
                            commands[cmd]()
                            list_of_commands.append(cmd)
                        except ValueError as ve :
                            print(ve)
                        except RepoError as re:
                            print(re)
                else :
                    if cmd == "4" and ( "1" not in list_of_commands or "2" not in list_of_commands or "3" not in list_of_commands) :
                            print("You have to introduce first a valid battleship, cruiser and destroyer !")
                    else :
                        try :
                            commands[cmd]()
                            if self.__srv_squares.check_finish_user() == 1 :
                                print("The user won ! Congratulations !")
                                return
                            elif self.__srv_squares.check_finish_computer() == 1 :
                                print("The computer won ! :(")
                                return
                        except ValueError as ve:
                            print(ve)
                        except RepoError as re:
                            print(re)
            else :
                print("Invalid command !")
