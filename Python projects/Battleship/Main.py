from UI import *
from GUI import *

def start() :

    validator_square = Validation_Square()
    repo_squares_user = Repo_squares()
    repo_squares_computer = Repo_squares()
    srv_squares = Service_squares(repo_squares_user, repo_squares_computer, validator_square)
    srv_squares.initialise_user()
    srv_squares.initialise_computer()
    srv_squares.battleship_computer()
    srv_squares.cruiser_computer()
    srv_squares.destroyer_computer()
    ui_var = UI(srv_squares)
    command = input("Type 1 for menu-based interface or 2 for graphic user interface :")
    while command != "1" and command != "2" :
        command = input("Please type 1 or 2 : ")
    if command == "1" :
        ui_var.menu()
    elif command == "2" :
        gui = GUI(srv_squares)

start()