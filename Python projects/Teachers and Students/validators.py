from domain import *
from errors import *

class valid_stud(object) :

    def check_stud(self, student):
        # this function validates if it is possible to create the student
        # input : student - a student
        # output : error if impossible
        error=""
        if student.get_stud_id() == "" :
            error += "Invalid id ! "
        if student.get_name() == "" :
            error += "Invalid name !"
        if len(error) != 0 :
            raise validerror(error)

class valid_sub(object) :

    def check_sub(self, subject):
        # this function validates if it is possible to create the subject
        # input : subject - a subject
        # output : error if impossible
        error=""
        if subject.get_sub_id() == "" :
            error += "Invalid id ! "
        if subject.get_name() == "" :
            error += "Invalid name !"
        if len(error) != 0 :
            raise validerror(error)

class valid_grade(object) :

    def check_grade(self, grd):
        # this function validates if it is possible to create the grade
        # input : grade - a grade
        # output : error if impossible
        error = ""
        if grd.get_val() < 1 or grd.get_val() > 10 :
            error += "Invalid value for grade !"
        if len(error) != 0 :
            raise validerror(error)