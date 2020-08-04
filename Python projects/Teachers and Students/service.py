from domain import *
from validators import *
from repo import *

class service_students(object) :

    def __init__(self,undo_srv, repo_studs, validation_students):
        # this function creates a service_student object
        # input : repo_studs - repository, validation_student - valid_stud object
        # output : a service_student object
        self.__list_students = repo_studs
        self.__validator_students = validation_students
        self.__undo_srv = undo_srv

    def get_students(self):
        # this function return the students
        # input :
        # output : the list with students
        return self.__list_students.get_entities()

    def add(self, stud, var_undo=True):
        # this function adds a student to the list
        # input : stud- a student object
        # output : -
        self.__validator_students.check_stud(stud)
        self.__list_students.add(stud)
        if var_undo == True :
            redo = call_function(self.add, stud)
            undo = call_function(self.remove, stud)
            op = Operation(undo, redo)
            self.__undo_srv.keep_function(op)

    def remove(self, stud):
        # this function removes a student from the list
        # input : stud - a student object
        # output :
        self.__validator_students.check_stud(stud)
        self.__list_students.search_element(stud)
        self.__list_students.delete_element(stud)

    def update(self, stud,new_name, var_undo= True):
        # input : this function updates the name of a student
        # input : stud - a student object
        # output : -
        self.__validator_students.check_stud(stud)
        self.__list_students.search_element(stud)
        stud1 = self.__list_students.search_element(stud)
        old_name = stud1.get_name()
        self.__list_students.update_element(stud, new_name)
        if var_undo == True :
            redo = call_function(self.update, stud, new_name)
            undo = call_function(self.update, stud1, old_name)
            op = Operation(undo, redo)
            self.__undo_srv.keep_function(op)

    def search_element(self,stud):
        # this function returns a specific student from the list
        # input : stud - a student object
        # output : the student
        return self.__list_students.search_element(stud)

    def search_partial_student(self,type_of_search, pattern):
        # this function searches for students based on ID or name/title
        # type of search - ID/ name
        # pattern - string
        l = list()
        if type_of_search == "ID":
            for stud in self.__list_students.get_entities():
                stud_id = stud.get_stud_id()
                stud_id = stud_id.lower()
                pattern = pattern.lower()
                if pattern in stud_id or stud_id in pattern:
                    l.append(stud)
        if type_of_search == "name":
            for stud in self.__list_students.get_entities() :
                name = stud.get_name()
                name = name.lower()
                pattern = pattern.lower()
                if pattern in name or name in pattern:
                    l.append(stud)
        return l

class service_subjects(object) :

    def __init__(self,undo_srv, repo_subjs, validation_subjects):
        # this function creates an object of type service_subjects
        # input : repo-subjs - a repository, validation_subjects - a valid_sub object
        # output : a service_subjects object
        self.__list_subjects = repo_subjs
        self.__validator_subjects = validation_subjects
        self.__undo_srv = undo_srv

    def get_subjects(self):
        # this function returns a list with all subjects
        # input : -
        # output : the list with all subjects
        return self.__list_subjects.get_entities()

    def add(self, sub, var_undo=True):
        # this function adds a subject to the list
        # input : sub - a subject
        # output : -
        self.__validator_subjects.check_sub(sub)
        self.__list_subjects.add(sub)
        if var_undo == True :
            redo = call_function(self.add, sub)
            undo = call_function(self.remove, sub)
            op = Operation(undo, redo)
            self.__undo_srv.keep_function(op)


    def remove(self, sub):
        # this function removes a subject from the list
        # input : sub - a subject
        # output : -
        self.__validator_subjects.check_sub(sub)
        self.__list_subjects.search_element(sub)
        self.__list_subjects.delete_element(sub)

    def update(self, sub,new_name, var_undo=True):
        # this function updates the name of a subject
        # input : sub - a subject
        # output : -
        self.__validator_subjects.check_sub(sub)
        self.__list_subjects.search_element(sub)
        sub1 = self.__list_subjects.search_element(sub)
        old_name = sub1.get_name()
        self.__list_subjects.update_element(sub, new_name)
        if var_undo == True :
            redo = call_function(self.update, sub, new_name)
            undo = call_function(self.update, sub, old_name)
            op = Operation(undo, redo)
            self.__undo_srv.keep_function(op)

    def search_element(self,sub):
        # this function returns a subject from the list
        # input : sub - a subject
        # output : -
        return self.__list_subjects.search_element(sub)

    def search_partial_subject(self, type_of_search, pattern):
        # this function searches for disciplines based on ID or name/title
        # type of search - ID/ name
        # pattern - string
        l=list()
        if type_of_search == "ID" :
            for sub in self.__list_subjects.get_entities() :
                sub_id = sub.get_sub_id()
                sub_id = sub_id.lower()
                pattern = pattern.lower()
                if pattern in sub_id or sub_id in pattern:
                    l.append(sub)
        if type_of_search == "name" :
            for sub in self.__list_subjects.get_entities() :
                name = sub.get_name()
                name = name.lower()
                pattern = pattern.lower()
                if pattern in name or name in pattern:
                    l.append(sub)
        return l

class service_grades(object) :

    def __init__(self,undo_srv, repo_grades, repo_studs, repo_subjs, validation_grades, validation_students, validation_subjects):
        # this function creates a service_grades object
        # input : repo_grades, repo_studs, repo_subjs - repositories, validation_grades - a valid_grade object
        # output : a service_grades object
        self.__list_grades = repo_grades
        self.__list_students = repo_studs
        self.__list_subjects = repo_subjs
        self.__validator_grades = validation_grades
        self.__validator_students = validation_students
        self.__validator_subjects = validation_subjects
        self.__undo_srv = undo_srv

    def get_grades(self):
        # this function returns a list with all grades
        # input : -
        # output : the list with all grades
        return self.__list_grades.get_entities()

    def return_grades(self):
        l=list()
        for grd in self.__list_grades.get_entities() :
            stud = grd.get_student()
            sub = grd.get_subject()
            stud = self.__list_students.search_element(stud)
            sub = self.__list_subjects.search_element(sub)
            val = grd.get_val()
            grd = grade(stud, sub, val)
            l.append(grd)
        return l

    def add(self, grd, var_undo=True):
        # this function adds a grade to the list
        # input : grd - a grade object
        # output : -
        stud = grd.get_student()
        sub = grd.get_subject()
        self.__validator_grades.check_grade(grd)
        self.__list_students.search_element(stud)
        self.__list_subjects.search_element(sub)
        self.__list_grades.add(grd)
        if var_undo ==True :
            redo = call_function(self.add, grd)
            undo = call_function(self.remove_last_grade)
            op = Operation(undo, redo)
            self.__undo_srv.keep_function(op)

    def remove_last_grade(self):
        length = self.__list_grades.size()
        self.__list_grades.pop = self.__list_grades.remove(length-1)

    def add_student_with_grades(self, stud, grade_list):
        self.__list_students.add(stud)
        if len(grade_list) != 0 :
            for grd in grade_list:
                self.__list_grades.add(grd)

    def add_subject_with_grades(self, sub, grade_list):
        self.__list_subjects.add(sub)
        if len(grade_list) != 0 :
            for grd in grade_list:
                self.__list_grades.add(grd)

    # changes for assigment 11

    def filter_student(self, grd):
        stud = grd.get_student()
        if stud == self.stud_filter :
            return True
        return False

    def filter_subject(self, grd):
        sub = grd.get_subject()
        if sub == self.sub_filter:
            return True
        return False

    def filter_by_student(self, stud):
         self.stud_filter = stud
         grades = self.get_grades()
         grades = filter(grades, self.filter_student)
         return grades[:]

    def filter_by_subject(self, sub):
         self.sub_filter = sub
         grades = self.get_grades()
         grades = filter(grades, self.filter_subject)
         return grades[:]

    # the next functions suffered modifications for assignment 11


    def remove_by_student(self, stud, var_undo=True):
        # this function removes all grades of a student
        # input : stud - a student
        # output : -
        self.__validator_students.check_stud(stud)
        self.__list_students.search_element(stud)
        stud = self.__list_students.search_element(stud)
        grade_list = self.filter_by_student(stud)
        self.__list_students.delete_element(stud)
        self.__list_grades.delete_by_student(stud)
        if var_undo == True :
            redo = call_function(self.remove_by_student, stud)
            undo = call_function(self.add_student_with_grades, stud, grade_list)
            op = Operation(undo, redo)
            self.__undo_srv.keep_function(op)

    def remove_by_subject(self, sub, var_undo=True):
        # this function removes all grades from a subject
        # input : sub - a subject
        # output : -
        self.__validator_subjects.check_sub(sub)
        self.__list_subjects.search_element(sub)
        sub = self.__list_subjects.search_element(sub)
        grade_list = self.filter_by_subject(sub)
        self.__list_subjects.delete_element(sub)
        self.__list_grades.delete_by_subject(sub)
        if var_undo == True :
            redo = call_function(self.remove_by_subject, sub)
            undo = call_function(self.add_subject_with_grades, sub, grade_list)
            op = Operation(undo, redo)
            self.__undo_srv.keep_function(op)

    def failing_students(self):
        # this function returns a list with all failing students
        # input : -
        # output : a list with all failing students
        l=list()
        for stud in self.__list_students.get_entities() :
            for sub in self.__list_subjects.get_entities() :
                ind = 0
                sum = 0
                grd1 = grade(stud, sub, 0)
                for grd2 in self.__list_grades.get_entities() :
                    if grd1 == grd2 :
                        ind = ind + 1
                        val = grd2.get_val()
                        sum = sum + val
                if ind != 0 :
                    average = sum / ind
                    average = float("{0:.2f}".format(average))
                    if average < 5 :
                        name_stud = stud.get_name()
                        name_sub = sub.get_name()
                        sub_id = sub.get_sub_id()
                        stud_id = stud.get_stud_id()
                        dict = {
                            "student" : stud,
                            "subject" : sub,
                            "average" : average
                        }
                        l.append(dict)
        return l

    def compare_students(self, first_student, second_student):
        return first_student["average"] >= second_student["average"]

    def compare_subjects(self, first_subject, second_subject):
        return first_subject["average"] >= second_subject["average"]

    def best_students(self):
        # this function returns a list with the best 5 students
        # input : -
        # output : a list with the best 5 students
        l = list()
        for stud in self.__list_students.get_entities():
            ind_sub = 0
            sum_sub = 0
            for sub in self.__list_subjects.get_entities():
                ind = 0
                sum = 0
                grd1 = grade(stud, sub, 0)
                for grd2 in self.__list_grades.get_entities():
                    if grd1 == grd2:
                        ind = ind + 1
                        val = grd2.get_val()
                        sum = sum + val
                if ind != 0:
                    average = sum / ind
                    average = float("{0:.2f}".format(average))
                    sum_sub += average
                    ind_sub += 1
            if ind_sub != 0 :
                average = sum_sub / ind_sub
                average = float("{0:.2f}".format(average))
                dict = {
                    "student" : stud,
                    "average" : average
                }
                l.append(dict)
        sorted_students = shellSort(l, self.compare_students)
        if len(sorted_students) > 5 :
            sorted_students =sorted_students[:4]
        return sorted_students

    def sorted_subjects(self):
        # this function returns a list with all sorted subject
        # input :
        # output : a list with all sorted subject
        l = list()
        for sub in self.__list_subjects.get_entities() :
            ind_stud = 0
            sum_stud = 0
            for stud in self.__list_students.get_entities():
                ind = 0
                sum = 0
                grd1 = grade(stud, sub, 0)
                for grd2 in self.__list_grades.get_entities():
                    if grd1 == grd2:
                        ind = ind + 1
                        val = grd2.get_val()
                        sum = sum + val
                if ind != 0:
                    average = sum / ind
                    average = float("{0:.2f}".format(average))
                    sum_stud += average
                    ind_stud += 1
            if ind_stud != 0 :
                average = sum_stud / ind_stud
                average = float("{0:.2f}".format(average))
                dict = {
                    "subject" : sub,
                    "average" : average
                }
                l.append(dict)
        sorted_subjects = shellSort(l, self.compare_subjects)
        return sorted_subjects

class undo :

    def __init__(self):
        # this function creates an object of type undo
        # input : -
        # output : an object of type undo
        self.__index = 0
        self.__history = []
        self.__in_process = False

    def keep_function(self, function):
        # this function keep in history a valid operation which is different from undo and redo
        # input : function - an operation/ function
        # output : -
        if self.__in_process == True :
            return
        if self.__index == len(self.__history) :
            self.__history.append(function)
        else :
            self.__history[self.__index] = function
            index_curent = self.__index+1
            while index_curent < len(self.__history) :
                self.__history.pop(index_curent)
        self.__index = self.__index +1

    def undo(self):
        # this function undo the last operation
        # input : -
        # output : an error message if undo can't be done
        if self.__index == 0 :
            raise validerror ("Undo operation can't be done anymore !")
        self.__in_process = True
        self.__index = self.__index - 1
        self.__history[self.__index].undo()
        self.__in_process = False

    def redo(self):
        # this function redo the last operation
        # input : -
        # output : an error message if redo can't be done
        if self.__index == len(self.__history):
            raise validerror("Redo operation can't be done anymore !")
        self.__in_process = True
        self.__history[self.__index].redo()
        self.__index += 1
        self.__in_process = False

