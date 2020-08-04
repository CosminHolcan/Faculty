from Service import *
from UI import *
import tkinter as tk
from PIL import ImageTk, Image

class GUI :

    def __init__(self, srv_squares):
        self.__srv_squares = srv_squares
        self.__battleship_var = False
        self.__cruiser_var = False
        self.__destroyer_var = False
        self.root = tk.Tk()
        self.canvas = tk.Canvas(self.root, height = 1200, width = 800)
        self.__main_background = ImageTk.PhotoImage(Image.open("background.png"))
        self.canvas.create_image(0, 0, anchor="nw", image=self.__main_background)
        self.canvas.pack()
        #self.frame = tk.Frame(self.canvas)
        #self.frame.place(relx=0, rely=0, relheight=1, relwidth=1)
        self.Tittle_button = tk.Button(self.canvas, text = "BATTLESHIP", bg = "orange",font = "bold 20")
        self.Tittle_button.place(relx = 0.33, rely = 0, relwidth = 0.33, relheight = 0.15)
        self.Game_button = tk.Button(self.canvas, text = "Start a new game", bg = "orange",font = "bold 15",
                                     command = self.start_game)
        self.Game_button.place( relx = 0.6, rely = 0.25, relwidth = 0.3, relheight = 0.1 )
        self.Help_button = tk.Button(self.canvas, text="How to play", bg="orange",font = "bold 15",
                                     command=self.how_to_play)
        self.Help_button.place(relx=0.6, rely=0.45, relwidth=0.3, relheight=0.1)
        self.root.mainloop()

    def create_again(self):
        try :
            self.canvas.destroy()
        except Exception :
            pass
        self.canvas = tk.Canvas(self.root, height=1200, width=800)
        self.__main_background = ImageTk.PhotoImage(Image.open("background.png"))
        self.canvas.create_image(0, 0, anchor="nw", image=self.__main_background)
        self.canvas.pack()
        self.Tittle_button = tk.Button(self.canvas, text="BATTLESHIP", bg="orange", font="bold 20")
        self.Tittle_button.place(relx=0.33, rely=0, relwidth=0.33, relheight=0.15)
        self.Game_button = tk.Button(self.canvas, text="Start a new game", bg="orange", font="bold 15",
                                     command=self.start_game)
        self.Game_button.place(relx=0.6, rely=0.25, relwidth=0.3, relheight=0.1)
        self.Help_button = tk.Button(self.canvas, text="How to play", bg="orange", font="bold 15",
                                     command=self.how_to_play)
        self.Help_button.place(relx=0.6, rely=0.45, relwidth=0.3, relheight=0.1)

    def clear_text(self):
        try :
            self.Error_text["text"] = "ERROR : "
        except Exception :
            pass

    def how_to_play(self):
        self.canvas.destroy()
        self.canvas = tk.Canvas(self.root, height=1200, width=800)
        self.__main_background = ImageTk.PhotoImage(Image.open("how_to_play.png"))
        self.canvas.create_image(0, 0, anchor="nw", image=self.__main_background)
        self.canvas.pack()
        #self.frame = tk.Frame(self.root, bg="dark blue")
        #self.frame.place(relx=0, rely=0, relheight=1, relwidth=1)
        descriptive_text = "The user will play against the computer.\n" \
               "First, the user has to 'build' his fleet,\n which contains a battleship, a cruiser and a destroyer.\n" \
                "The battleship occupies 4 squares, cruiser 3 squares and destroyer just 2.\n" \
               "To build a boat, the user will chose a square ( its column and row)\n and a direction : N, S, E, W.\n" \
                "If the direction is N then the boat will be built in the north direction\n ( by example : if an user chose the square 8A,\n and direction N for his battleship, then the battleship \nwill be built on squares : 8A, 7A, 6A, 5A.)\n" \
                "The process is similar for direction S(outh), E(st) and W(est).\n" \
                "After the user 'has built' his fleet, he will try to destroy\n the fleet of the computer and computer will also try to destroy the fleet of the user.\n" \
                "The winner will be the one who will distroy first the other's fleet."\

        self.text = tk.Label(self.canvas,  height=100, width=100, anchor="nw", padx=10, text=descriptive_text, font="bold 15",
                                   bg="orange")
        self.text.place(relx =0, rely =0, relwidth = 1, relheight = 0.5)
        self.how_to_play_button = tk.Button(self.canvas, text = "OK", font = "bold 20",bg = "orange", command = self.create_again)
        self.how_to_play_button.place(relx = 0.45, rely = 0.7, relheight = 0.1, relwidth = 0.1)

    def start_game(self):
        self.canvas.destroy()
        self.canvas = tk.Canvas(self.root, height=1200, width=800)
        self.__main_background = ImageTk.PhotoImage(Image.open("sky_background.png"))
        self.canvas.create_image(0, 0, anchor="nw", image=self.__main_background)
        self.canvas.pack()
        #self.frame = tk.Frame(self.root, bg="#643D01")
        #self.frame.place(relx=0, rely=0, relheight=1, relwidth=1)
        self.Grid_user = tk.Frame(self.canvas, bg= "white")
        self.Grid_user.place( relx = 0.1, rely = 0.1, relwidth = 0.32, relheight = 0.32)
        self.Grid_user_label = tk.Label(self.canvas, height=50, width=100, anchor="n", padx=10,
                                   text=" GRID OF PLAYER ",font = "bold", bg="dark blue", fg="white")
        self.Grid_user_label.place(relx = 0.1, rely = 0.05, relwidth = 0.32, relheight = 0.025)
        self.Grid_computer_label = tk.Label(self.canvas, height=50, width=100, anchor="n", padx=10,
                                        text=" GRID OF COMPUTER ", font="bold", bg="dark blue", fg="white")
        self.Grid_computer_label.place(relx=0.5, rely=0.05, relwidth=0.32, relheight=0.025)
        self.Grid_computer = tk.Frame(self.canvas, bg="white")
        self.Grid_computer.place(relx=0.5, rely=0.1, relwidth=0.32, relheight=0.32)
        letters = ["A", "B", "C", "D", "E", "F", "G", "H"]
        for i in range(8) :
            self.b = tk.Button(self.canvas,  text=letters[i],font = "bold", bg="orange", borderwidth = 3)
            self.b.place(relx = 0.1+i/8*0.32, rely = 0.075, relwidth = 0.04, relheight = 0.025 )
        for i in range(8) :
            self.b = tk.Button(self.canvas,  text=letters[i],font = "bold", bg="orange", borderwidth = 3)
            self.b.place(relx = 0.5+i/8*0.32, rely = 0.075, relwidth = 0.04, relheight = 0.025 )
        for i in range(8) :
            self.b = tk.Button(self.canvas,  text=str(i+1),font = "bold", bg="orange", borderwidth = 3)
            self.b.place(relx = 0.075, rely = 0.1+i/8*0.32, relwidth = 0.025, relheight = 0.04 )
        for i in range(8) :
            self.b = tk.Button(self.canvas, text=str(i+1),font = "bold", bg="orange", borderwidth = 3)
            self.b.place(relx = 0.82, rely = 0.1+i/8*0.32, relwidth = 0.025, relheight = 0.04 )
        for i in range(8) :
            for j in range(8) :
                self.b = tk.Button(self.Grid_user, bg = "gray", borderwidth =10)
                self.b.place(relx = i/8, rely = j/8, relwidth = 1/8, relheight = 1/8)
        for i in range(8) :
            for j in range(8) :
                self.b = tk.Button(self.Grid_computer, bg = "gray", borderwidth =10)
                self.b.place(relx = i/8, rely = j/8, relwidth = 1/8, relheight = 1/8)

        self.cmd_frame = tk.Frame(self.canvas, bg = "white")
        self.cmd_frame.place(relx = 0, rely = 0.5, relwidth = 1, relheight = 0.35)
        self.Error_frame = tk.Frame( self.root, bg = "pink")
        self.Error_frame.place(relx = 0, rely = 0.85, relwidth = 1, relheight = 0.15)
        self.Error_text = tk.Label(self.Error_frame, height=100, width=100, anchor="nw", padx=10, text="ERROR : ", font="bold",
                                   bg="red")
        self.Error_text.place(relx=0, rely=0, relwidth=1, relheight=1)
        self.battleship_frame = tk.Frame(self.cmd_frame, bg = "gray")
        self.battleship_frame.place(relx= 0, rely= 0, relheight = 1, relwidth = 0.33)
        self.cruiser_frame = tk.Frame(self.cmd_frame, bg = "blue")
        self.cruiser_frame.place(relx = 0.33, rely = 0, relheight = 1, relwidth = 0.33)
        self.destroyer_frame = tk.Frame(self.cmd_frame, bg = "purple")
        self.destroyer_frame.place(relx = 0.66, rely = 0, relwidth = 0.34, relheight = 1)
        self.battleship_label = tk.Label(self.battleship_frame, height=50, width=100, anchor="n", padx=10,
                                   text=" BATTLESHIP ", bg="gray", font = "bold 10")
        self.battleship_label.place(relwidth = 1, relheight = 0.2)
        self.battleship_row = tk.Label(self.battleship_frame, height=50, width=100, anchor="n", padx=10,
                                   text=" ROW : ", bg="orange", borderwidth = 1, relief = "solid")
        self.battleship_row.place(relx = 0, rely = 0.2, relwidth = 0.3, relheight = 0.1)
        self.write_battleship_row = tk.Entry(self.battleship_frame)
        self.write_battleship_row.place(relx = 0.3, rely = 0.2, relwidth = 0.7, relheight = 0.1)
        self.battleship_column = tk.Label(self.battleship_frame, height=50, width=100, anchor="n", padx=10,
                                       text=" COLUMN : ", bg="orange", borderwidth = 1, relief = "solid")
        self.battleship_column.place(relx=0, rely=0.3, relwidth=0.3, relheight=0.1)
        self.write_battleship_column = tk.Entry(self.battleship_frame)
        self.write_battleship_column.place(relx=0.3, rely=0.3, relwidth=0.7, relheight=0.1)
        self.battleship_direction = tk.Label(self.battleship_frame, height=50, width=100, anchor="n", padx=10,
                                       text=" DIRECTION : ", bg="orange", borderwidth = 1, relief = "solid")
        self.battleship_direction.place(relx =0, rely =0.4, relwidth = 0.3, relheight = 0.1)
        self.write_battleship_direction = tk.Entry(self.battleship_frame)
        self.write_battleship_direction.place(relx=0.3, rely=0.4, relwidth=0.7, relheight=0.1)
        self.battleship_button = tk.Button(self.battleship_frame, text = "Add battleship",font="bold", bg = "orange", command = self.gui_add_battleship)
        self.battleship_button.place(relx = 0.1, rely = 0.7, relheight = 0.2, relwidth = 0.8)
        self.cruiser_label = tk.Label(self.cruiser_frame, height=50, width=100, anchor="n", padx=10,
                                         text=" CRUISER ", bg="blue", font = "bold 10", fg="white")
        self.cruiser_label.place(relwidth=1, relheight=0.2)
        self.cruiser_row = tk.Label(self.cruiser_frame, height=50, width=100, anchor="n", padx=10,
                                       text=" ROW : ", bg="orange", borderwidth = 1, relief = "solid")
        self.cruiser_row.place(relx=0, rely=0.2, relwidth=0.3, relheight=0.1)
        self.write_cruiser_row = tk.Entry(self.cruiser_frame)
        self.write_cruiser_row.place(relx=0.3, rely=0.2, relwidth=0.7, relheight=0.1)
        self.cruiser_column = tk.Label(self.cruiser_frame, height=50, width=100, anchor="n", padx=10,
                                          text=" COLUMN : ", bg="orange", borderwidth = 1, relief = "solid")
        self.cruiser_column.place(relx=0, rely=0.3, relwidth=0.3, relheight=0.1)
        self.write_cruiser_column = tk.Entry(self.cruiser_frame)
        self.write_cruiser_column.place(relx=0.3, rely=0.3, relwidth=0.7, relheight=0.1)
        self.cruiser_direction = tk.Label(self.cruiser_frame, height=50, width=100, anchor="n", padx=10,
                                             text="DIRECTION :", bg="orange", borderwidth = 1, relief = "solid")
        self.cruiser_direction.place(relx=0, rely=0.4, relwidth=0.3, relheight=0.1)
        self.write_cruiser_direction = tk.Entry(self.cruiser_frame)
        self.write_cruiser_direction.place(relx=0.3, rely=0.4, relwidth=0.7, relheight=0.1)
        self.cruiser_button = tk.Button(self.cruiser_frame, text="Add cruiser",font = "bold", bg="orange", command=self.gui_add_cruiser)
        self.cruiser_button.place(relx=0.1, rely=0.7, relheight=0.2, relwidth=0.8)
        self.destroyer_label = tk.Label(self.destroyer_frame, height=50, width=100, anchor="n", padx=10,
                                      text=" DESTROYER ", bg="purple", font = "bold 10", fg="white")
        self.destroyer_label.place(relwidth=1, relheight=0.2)
        self.destroyer_row = tk.Label(self.destroyer_frame, height=50, width=100, anchor="n", padx=10,
                                    text=" ROW : ", bg="orange", borderwidth = 1, relief = "solid")
        self.destroyer_row.place(relx=0, rely=0.2, relwidth=0.3, relheight=0.1)
        self.write_destroyer_row = tk.Entry(self.destroyer_frame)
        self.write_destroyer_row.place(relx=0.3, rely=0.2, relwidth=0.7, relheight=0.1)
        self.destroyer_column = tk.Label(self.destroyer_frame, height=50, width=100, anchor="n", padx=10,
                                       text=" COLUMN : ", bg="orange", borderwidth = 1, relief = "solid")
        self.destroyer_column.place(relx=0, rely=0.3, relwidth=0.3, relheight=0.1)
        self.write_destroyer_column = tk.Entry(self.destroyer_frame)
        self.write_destroyer_column.place(relx=0.3, rely=0.3, relwidth=0.7, relheight=0.1)
        self.destroyer_direction = tk.Label(self.destroyer_frame, height=50, width=100, anchor="n", padx=10,
                                          text="DIRECTION :", bg="orange", borderwidth = 1, relief = "solid")
        self.destroyer_direction.place(relx=0, rely=0.4, relwidth=0.3, relheight=0.1)
        self.write_destroyer_direction = tk.Entry(self.destroyer_frame)
        self.write_destroyer_direction.place(relx=0.3, rely=0.4, relwidth=0.7, relheight=0.1)
        self.destroyer_button = tk.Button(self.destroyer_frame, text="Add destroyer",font = "bold", bg="orange", command=self.gui_add_destroyer)
        self.destroyer_button.place(relx=0.1, rely=0.7, relheight=0.2, relwidth=0.8)

    def gui_add_battleship(self):
        self.clear_text()
        row = self.write_battleship_row.get()
        column = self.write_battleship_column.get()
        direction = self.write_battleship_direction.get()
        try :
            if row.isdigit() == False :
                raise ValueError ("The row should be a number from 1 to 8 !")
            row = int(row)
            row = row - 1
            square = Square(row, column)
            self.__srv_squares.battleship_user(square, direction)
            self.__battleship_var = True
            self.clear_text()
        except ValueError as ve :
            self.Error_text["text"] = str("ERROR : ") +str(ve)
        except RepoError as re :
            self.Error_text["text"] = str("ERROR : ") + str(re)
        if self.__battleship_var == True :
            self.battleship_frame.destroy()
            self.battleship_frame = tk.Frame(self.cmd_frame, bg="gray")
            self.battleship_frame.place(relx=0, rely=0, relheight=1, relwidth=0.33)
            self.battleship_label = tk.Label(self.battleship_frame, height=50, width=100, anchor="n", padx=10,
                                             text=" The battleship was added ", bg="orange", font = "bold 12")
            self.battleship_label.place(relx=0.1, rely=0.4, relwidth=0.8, relheight=0.2)
            self.can_start()

    def gui_add_cruiser(self):
        self.clear_text()
        row = self.write_cruiser_row.get()
        column = self.write_cruiser_column.get()
        direction = self.write_cruiser_direction.get()
        try:
            if row.isdigit() == False:
                raise ValueError("Row should be a number from 1 to 8 !")
            row = int(row)
            row = row - 1
            square = Square(row, column)
            self.__srv_squares.cruiser_user(square, direction)
            self.__cruiser_var = True
            self.clear_text()
        except ValueError as ve:
            self.Error_text["text"] = str("ERROR : ") + str(ve)
        except RepoError as re:
            self.Error_text["text"] = str("ERROR : ") + str(re)
        if self.__cruiser_var == True :
            self.cruiser_frame.destroy()
            self.cruiser_frame = tk.Frame(self.cmd_frame, bg="blue")
            self.cruiser_frame.place(relx=0.33, rely=0, relheight=1, relwidth=0.33)
            self.cruiser_label = tk.Label(self.cruiser_frame, height=50, width=100, anchor="n", padx=10,
                                          text=" The cruiser was added ", bg="orange", font = "bold 12")
            self.cruiser_label.place(relx=0.1, rely=0.4, relwidth=0.8, relheight=0.2)
            self.can_start()

    def gui_add_destroyer(self):
        self.clear_text()
        row = self.write_destroyer_row.get()
        column = self.write_destroyer_column.get()
        direction = self.write_destroyer_direction.get()
        try:
            if row.isdigit() == False:
                raise ValueError("Row should be a number from 1 to 8 !")
            row = int(row)
            row = row - 1
            square = Square(row, column)
            self.__srv_squares.destroyer_user(square, direction)
            self.__destroyer_var = True
            self.clear_text()
        except ValueError as ve:
            self.Error_text["text"] =  str("ERROR : ") +str(ve)
        except RepoError as re:
            self.Error_text["text"] = str("ERROR : ") + str(re)
        if self.__destroyer_var == True :
            self.destroyer_frame.destroy()
            self.destroyer_frame = tk.Frame(self.cmd_frame, bg="purple")
            self.destroyer_frame.place(relx=0.66, rely=0, relheight=1, relwidth=0.34)
            self.destroyer_label = tk.Label(self.destroyer_frame, height=50, width=100, anchor="n", padx=10,
                                            text=" The destroyer was added ", bg="orange", font = "bold 10")
            self.destroyer_label.place(relx=0.1, rely=0.4, relwidth=0.8, relheight=0.2)
            self.can_start()

    def can_start(self):
        if self.__battleship_var == True and self.__cruiser_var == True and self.__destroyer_var == True :
            self.complete_grid_user()
            self.cmd_frame.destroy()
            self.cmd_frame = tk.Frame(self.canvas, bg="dark blue")
            self.cmd_frame.place(relx=0, rely=0.5, relwidth=1, relheight=0.35)
            self.cmd_label = tk.Label(self.cmd_frame,height=50, width=100, anchor="n", padx=10,
                                            text=" Try to destroy the boats of computer ", bg="orange", font = "bold 20" )
            self.cmd_label.place(relx =0, rely =0, relwidth =1, relheight = 0.2)
            self.cmd_row = tk.Label(self.cmd_frame, height=50, width=100, anchor="n", padx=10,
                                            text=" ROW ", bg="orange", font = "bold 15")
            self.cmd_row.place(relx = 0, rely = 0.4, relheight = 0.1, relwidth = 0.2)
            self.write_cmd_row = tk.Entry(self.cmd_frame)
            self.write_cmd_row.place(relx=0.2, rely = 0.4, relheight = 0.1, relwidth = 0.3)
            self.cmd_column = tk.Label(self.cmd_frame, height=50, width=100, anchor="n", padx=10,
                                    text=" COLUMN ", bg="orange", font = "bold 15")
            self.cmd_column.place(relx=0, rely=0.6, relheight=0.1, relwidth=0.2)
            self.write_cmd_column = tk.Entry(self.cmd_frame)
            self.write_cmd_column.place(relx=0.2, rely=0.6, relheight=0.1, relwidth=0.3)
            self.cmd_button = tk.Button(self.cmd_frame,  text="Try", bg="orange", font = "bold 15 ", command=self.gui_try)
            self.cmd_button.place(relx = 0.4, rely = 0.8, relheight = 0.2, relwidth = 0.2)

    def complete_grid_user(self):
        for i in range(8) :
            for j in range(8) :
                if self.__srv_squares.get_entities_user()[j*8+i].get_symbol() == "1" :
                    self.b = tk.Button(self.Grid_user, bg="green", borderwidth=10)
                    self.b.place(relx=i / 8, rely=j / 8, relwidth=1 / 8, relheight=1 / 8)
                elif self.__srv_squares.get_entities_user()[j*8+i].get_symbol() == "X" :
                    self.b = tk.Button(self.Grid_user, bg="red", borderwidth=10)
                    self.b.place(relx=i / 8, rely=j / 8, relwidth=1 / 8, relheight=1 / 8)
                elif self.__srv_squares.get_entities_user()[j*8+i].get_symbol() == "V" :
                    self.b = tk.Button(self.Grid_user, bg="purple", borderwidth=10)
                    self.b.place(relx=i / 8, rely=j / 8, relwidth=1 / 8, relheight=1 / 8)
                else :
                    self.b = tk.Button(self.Grid_user, bg="gray", borderwidth=10)
                    self.b.place(relx=i / 8, rely=j / 8, relwidth=1 / 8, relheight=1 / 8)

    def complete_grid_computer(self):
        for i in range(8) :
            for j in range(8) :
                if self.__srv_squares.get_entities_computer()[j*8+i].get_symbol() == "1" :
                    self.b = tk.Button(self.Grid_computer, bg="gray", borderwidth=10)
                    self.b.place(relx=i / 8, rely=j / 8, relwidth=1 / 8, relheight=1 / 8)
                elif self.__srv_squares.get_entities_computer()[j*8+i].get_symbol() == "V" :
                    self.b = tk.Button(self.Grid_computer, bg="green", borderwidth=10)
                    self.b.place(relx=i / 8, rely=j / 8, relwidth=1 / 8, relheight=1 / 8)
                elif self.__srv_squares.get_entities_computer()[j*8+i].get_symbol() == "X":
                    self.b = tk.Button(self.Grid_computer, bg="red", borderwidth=10)
                    self.b.place(relx=i / 8, rely=j / 8, relwidth=1 / 8, relheight=1 / 8)
                else :
                    self.b = tk.Button(self.Grid_computer, bg="gray", borderwidth=10)
                    self.b.place(relx=i / 8, rely=j / 8, relwidth=1 / 8, relheight=1 / 8)

    def gui_try(self):
        self.clear_text()
        row = self.write_cmd_row.get()
        column = self.write_cmd_column.get()
        try :
            if row.isdigit() == False:
                raise ValueError("Row should be a number from 1 to 8 !")
            row = int(row)
            row = row - 1
            square = Square(row, column)
            self.__srv_squares.trying_of_user(square)
            self.clear_text()
            self.complete_grid_computer()
            if self.__srv_squares.check_finish_user() == 1:
                self.user_won()
            self.__srv_squares.trying_of_computer()
            self.complete_grid_user()
            if self.__srv_squares.check_finish_computer() == 1:
                self.computer_won()
            if self.__srv_squares.check_finish_user() != 1 and self.__srv_squares.check_finish_computer() != 1:
                self.can_start()
        except ValueError as ve :
            self.Error_text["text"] =  str("ERROR : ") +str(ve)
        except RepoError as re :
            self.Error_text["text"] =  str("ERROR : ") +str(re)


    def user_won(self):
        self.cmd_frame.destroy()
        self.clear_text()
        self.cmd_frame = tk.Frame(self.canvas, bg="dark blue")
        self.cmd_frame.place(relx=0, rely=0.5, relwidth=1, relheight=0.35)
        self.cmd_label = tk.Label(self.cmd_frame, height=50, width=100, anchor="n", padx=10,
                                   text=" USER WON ! CONGRATULATIONS ! ", bg="orange", font = "bold 15")
        self.cmd_label.place(relx = 0.1, rely = 0.3, relheight = 0.2, relwidth = 0.8)


    def computer_won(self):
        self.cmd_frame.destroy()
        self.clear_text()
        self.cmd_frame = tk.Frame(self.canvas, bg="dark blue")
        self.cmd_frame.place(relx=0, rely=0.5, relwidth=1, relheight=0.35)
        self.cmd_label = tk.Label(self.cmd_frame, height=50, width=100, anchor="n", padx=10,
                                   text=" COMPUTER WON ! :( ", bg="orange", font = "bold 15")
        self.cmd_label.place(relx = 0.1, rely = 0.3, relheight = 0.2, relwidth = 0.8)

