from Domain import *
from Errors import *

class Validation_Square(object) :

    def check_square(self, square):
        errors = ""
        if square.get_column() not in ["A", "B", "C", "D", "E", "F", "G", "H"] :
            errors = errors + "The column should be a letter from A to H !"+"\n"
        if square.get_row() < 0 or square.get_row() > 7 :
            errors = errors + "The row should be a number from 1 to 8 !"
        if len(errors) != 0 :
            raise ValueError (errors)