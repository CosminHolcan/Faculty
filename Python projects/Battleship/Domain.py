class Square(object) :

    def __init__(self, row, column):
        self.__row = row
        self.__column = column
        self.__symbol = "0"

    def __eq__(self, other):
        return self.__row == other.__row and self.__column == other.__column

    def get_row(self):
        return self.__row

    def get_column(self):
        return self.__column

    def get_symbol(self):
        return self.__symbol

    def set_symbol(self, new_symbol):
        self.__symbol = new_symbol

