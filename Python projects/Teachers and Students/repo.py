from errors import *
from iterable import *
import pickle

class Repo_studs_subjs(object) :

    def __init__(self):
        # this function creates a repo for students / subjects
        self._list= Iterable_Data()

    def __iter__(self):
        # this function iterates the elements of the list
        for i in self._list :
            yield i

    def get_entities(self):
        # this function return a list with all elements
        return self._list[:]

    def size(self):
        # this function returns the size of the list
        return len(self._list)

    def add(self, entity):
        # this function adds a entity to the list
        # input : entity - student / subject
        if entity in self._list :
            raise repoerror("This id is already in the list !")
        self._list.append(entity)

    def search_element(self, key_entity):
        # this function returns a message if an element is not in the list or the element
        # input : key_entity - a student/ subject
        if key_entity not in self._list :
            raise repoerror("This id is not in the list !")
        for i in self._list :
            if i == key_entity :
                return i

    def delete_element(self, key_entity):
        # this function removes a entity from the list
        # input : key_entity - a student / subject
        i=0
        while i < len(self._list) :
            if self._list[i] == key_entity :
                self._list.remove(self._list[i])
            else :
                i=i+1

    def update_element(self, key_entity, name):
        # this function changes the name for an entity
        # input : key_entity - a student / subject
        for i in range(len(self._list)) :
            if self._list[i] == key_entity :
                self._list[i].set_name(name)

class Repo_grades(object) :

    def __init__(self):
        # this function creates a repo for grades
        self._list = list()

    def __iter__(self):
        # this function iterates the elements of the list
        for i in self._list:
            yield i

    def size(self):
        # this function returns the size of the list
        return len(self._list)

    def get_entities(self):
        # this function return a list with all elements
        return self._list[:]

    def add(self, entity):
        # this function adds a entity to the list
        # input : entity - grade
        self._list.append(entity)

    def delete_by_student(self,stud) :
        # this function removes all grades of a student
        # input : stud - a student
        i = 0
        while i < len(self._list):
            grd = self._list[i]
            stud2 = grd.get_student()
            if stud == stud2 :
                self._list.remove(self._list[i])
            else:
                i = i + 1

    def delete_by_subject(self,sub) :
        # this function removes all grades of a subject
        # input : sub - a subject
        i = 0
        while i < len(self._list):
            grd = self._list[i]
            sub2 = grd.get_subject()
            if sub == sub2 :
                self._list.remove(self._list[i])
            else:
                i = i + 1

    def remove(self, index):
        self._list.pop(index)

class File_Repo_studs_subjs(Repo_studs_subjs) :

    def __init__(self, file_name, read_function, write_function):
        Repo_studs_subjs.__init__(self)
        self.__file_name = file_name
        self.__read_function = read_function
        self.__write_function = write_function

    def __iter__(self):
        self.read_from_file()
        Repo_studs_subjs.__iter__(self)

    def read_from_file(self):
        self._list = []
        with open(self.__file_name, "r") as file :
            lines = file.readlines()
            for line in lines :
                line = line.strip()
                if line != "" :
                    entity = self.__read_function(line)
                    self._list.append(entity)

    def write_to_file(self):
        with open(self.__file_name, "w") as file:
            for entity in self._list:
                file.write(self.__write_function(entity) + "\n")

    def get_entities(self):
        self.read_from_file()
        return Repo_studs_subjs.get_entities(self)

    def size(self):
        self.read_from_file()
        return Repo_studs_subjs.size(self)

    def add(self, entity):
        self.read_from_file()
        Repo_studs_subjs.add(self,entity)
        self.write_to_file()

    def delete_element(self, key_entity):
        self.read_from_file()
        Repo_studs_subjs.delete_element(self, key_entity)
        self.write_to_file()

    def update_element(self, key_entity, name):
        self.read_from_file()
        Repo_studs_subjs.update_element(self, key_entity, name)
        self.write_to_file()

class File_Repo_grades(Repo_grades) :

    def __init__(self, file_name, read_function, write_function):
        Repo_grades.__init__(self)
        self.__file_name = file_name
        self.__read_function = read_function
        self.__write_function = write_function

    def __iter__(self):
        self.read_from_file()
        Repo_grades.__iter__(self)

    def read_from_file(self):
        self._list = []
        with open(self.__file_name, "r") as file:
            lines = file.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    entity = self.__read_function(line)
                    self._list.append(entity)

    def write_to_file(self):
        with open(self.__file_name, "w") as file:
            for entity in self._list:
                file.write(self.__write_function(entity) + "\n")

    def get_entities(self):
        self.read_from_file()
        return Repo_grades.get_entities(self)

    def size(self):
        self.read_from_file()
        return Repo_grades.size(self)

    def add(self, entity):
        self.read_from_file()
        Repo_grades.add(self, entity)
        self.write_to_file()

    def delete_by_student(self,stud):
        self.read_from_file()
        Repo_grades.delete_by_student(self, stud)
        self.write_to_file()

    def delete_by_subject(self,sub):
        self.read_from_file()
        Repo_grades.delete_by_subject(self, sub)
        self.write_to_file()

    def remove(self, index):
        self.read_from_file()
        Repo_grades.remove(self, index)
        self.write_to_file()

class Binary_Files_Repo_studs_subjs(Repo_studs_subjs) :

    def __init__(self, file_name, read_function, write_function):
        Repo_studs_subjs.__init__(self)
        self.__file_name = file_name
        self.__read_function = read_function
        self.__write_function = write_function

    def __iter__(self):
        self.read_from_file()
        Repo_studs_subjs.__iter__(self)

    def read_from_file(self):
        self._list = []
        with open(self.__file_name, "rb") as file :
            while True :
                try :
                    line = pickle.load(file)
                    entity = self.__read_function(line)
                    self._list.append(entity)
                except EOFError :
                    break

    def write_to_file(self):
        with open(self.__file_name, "wb") as file :
            for element in self._list :
                pickle.dump(self.__write_function(element), file)

    def get_entities(self):
        self.read_from_file()
        return Repo_studs_subjs.get_entities(self)

    def size(self):
        self.read_from_file()
        return Repo_studs_subjs.size(self)

    def add(self, entity):
        self.read_from_file()
        Repo_studs_subjs.add(self, entity)
        self.write_to_file()

    def delete_element(self, key_entity):
        self.read_from_file()
        Repo_studs_subjs.delete_element(self, key_entity)
        self.write_to_file()

    def update_element(self, key_entity, name):
        self.read_from_file()
        Repo_studs_subjs.update_element(self, key_entity, name)
        self.write_to_file()

class Binary_Files_Repo_grades(Repo_grades) :

    def __init__(self, file_name, read_function, write_function):
        Repo_grades.__init__(self)
        self.__file_name = file_name
        self.__read_function = read_function
        self.__write_function = write_function

    def __iter__(self):
        self.read_from_file()
        Repo_grades.__iter__(self)

    def read_from_file(self):
        self._list = []
        with open(self.__file_name, "rb") as file :
            while True :
                try :
                    line = pickle.load(file)
                    entity = self.__read_function(line)
                    self._list.append(entity)
                except EOFError :
                    break

    def write_to_file(self):
        with open(self.__file_name, "wb") as file :
            for element in self._list :
                pickle.dump(self.__write_function(element), file)

    def get_entities(self):
        self.read_from_file()
        return Repo_grades.get_entities(self)

    def size(self):
        self.read_from_file()
        return Repo_grades.size(self)

    def add(self, entity):
        self.read_from_file()
        Repo_grades.add(self, entity)
        self.write_to_file()

    def delete_by_student(self, stud):
        self.read_from_file()
        Repo_grades.delete_by_student(self, stud)
        self.write_to_file()

    def delete_by_subject(self, sub):
        self.read_from_file()
        Repo_grades.delete_by_subject(self, sub)
        self.write_to_file()

    def remove(self, index):
        self.read_from_file()
        Repo_grades.remove(self, index)
        self.write_to_file()

