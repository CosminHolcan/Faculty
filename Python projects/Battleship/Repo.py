from Domain import *
from Errors import *

class Repo_squares(object) :

    def __init__(self):
        self._list = list()

    def __iter__(self):
        for i in self._list :
            yield i

    def add_element(self, square):
        if square in self._list :
            raise RepoError("This element is already in the list !")
        self._list.append(square)

    def check_add_to_play(self, square):
        for element in self._list :
            if element == square :
                if element.get_symbol() == "1" :
                    return False
                else :
                    return True

    def get_size(self):
        return len(self._list)

    def search_element(self, key):
        if key not in self._list :
            raise RepoError("This element is not in the list ")
        for element in self._list :
            if element == key :
                return element

    def get_entities(self):
        return self._list[:]

    def modify_element(self, element, new_symbol):
        for entity in self._list :
            if entity == element :
                entity.set_symbol(new_symbol)

    def number_of_ones(self):
        nr = 0
        for element in self._list :
            if element.get_symbol() == "1" :
                nr=nr+1
        return nr