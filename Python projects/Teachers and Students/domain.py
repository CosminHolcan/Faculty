class student(object) :

    def __init__(self, stud_id, name):
        # this function creates a student object
        # input : stud_id, name - strings
        # output : a student object
        self._stud_id = stud_id
        self._name=name

    def __eq__(self,second):
        # this function determines if two students are equals, comparing their id-s
        # input : second - a student
        # output : -
        return self._stud_id == second._stud_id

    def __str__(self):
        # this function creates a string for a student
        # input : -
        # output : a string
        return "student_id : "+str(self._stud_id)+"    student_name : "+str(self._name)

    def get_stud_id(self):
        # this function return the id of a student
        return self._stud_id

    def get_name(self):
        # this function returns the name of a student
        return self._name

    def set_name(self,new_name):
        # this function set a new name for a student
        # input : new_name - a string
        self._name= new_name


    @staticmethod
    def read_student(line):
        params = line.split(",")
        student_id = str(params[0]).strip()
        student_name = str(params[1]).strip()
        stud = student(student_id, student_name)
        return stud

    @staticmethod
    def write_student(stud):
        student_id = stud.get_stud_id()
        student_name = stud.get_name()
        return str(student_id)+" , " + str(student_name)

class subject(object) :

    def __init__(self, sub_id, name):
        # this function creates a subject object
        # input : sub_id, name - strings
        # output : a subject object
        self._sub_id = sub_id
        self._name=name

    def __eq__(self,second):
        # this function determines if two subjects are equals, comparing their id-s
        # input : second - a subject
        # output : -
        return self._sub_id == second._sub_id

    def __str__(self):
        # this function creates a string for a subject
        # input : -
        # output : a string
        return "subject_id : "+str(self._sub_id)+"    subject_name : "+str(self._name)

    def get_sub_id(self):
        # this function return the id of a subject
        return self._sub_id

    def get_name(self):
        # this function returns the name of a student
        return self._name

    def set_name(self,new_name):
        # this function changes the name of a student
        # input : new_name - a string
        self._name= new_name

    @staticmethod
    def read_subject(line):
        params = line.split(",")
        subject_id = str(params[0]).strip()
        subject_name = str(params[1]).strip()
        sub = subject(subject_id, subject_name)
        return sub

    @staticmethod
    def write_subject(sub):
        subject_id = sub.get_sub_id()
        subject_name = sub.get_name()
        return str(subject_id) + " , " + str(subject_name)

class grade(object) :

    def __init__(self, stud, sub, val):
        # this function creates a grade object
        # input : stud - a student, sub - a subject, val - float
        # output : a grade
        self._student = stud
        self._subject=sub
        self._value = val

    def __eq__(self,second):
        # this function determines if two grades are equals, comparing their id-s
        # input : second - a grade
        # output :
        return self._student == second._student and self._subject == second._subject

    def __str__(self):
        # this function creates a string for a grade
        # input : -
        # output : a string
        stud = self._student
        sub= self._subject
        return "Student " + str(stud.get_name()) +" with id : "+str(stud.get_stud_id()) + " took a " +\
               str(self.get_val())+ " at object "+ str(sub.get_name()) + " with id : " +str(sub.get_sub_id())

    def get_student(self):
        # this function returns the student of a grade
        return self._student

    def get_subject(self):
        # this function returns the subject of a grade
        return self._subject

    def get_val(self):
        # this function returns the value of a grade
        return self._value

    def set_val(self,new_val):
        # this function changes the value for a grade
        self._value = new_val

    @staticmethod
    def read_grade(line):
        params = line.split(",")
        student_id = str(params[0]).strip()
        subject_id = str(params[1]).strip()
        grade_value = float(params[2])
        grd = grade(student(student_id, None), subject(subject_id, None), grade_value)
        return grd

    @staticmethod
    def write_grade(grd):
        stud = grd.get_student()
        sub = grd.get_subject()
        grade_value = grd.get_val()
        return str(stud.get_stud_id()) + " , " + str(sub.get_sub_id())+ " , " +str(grade_value)

class call_function :

    def __init__(self, function, *params):
        self.__function = function
        self.__params = params

    def __call__(self):
        self.call()

    def call(self):
        self.__function(*self.__params)

class Operation :
    def __init__(self, undoFunction, redoFunction):
        # this function creates an object of class Operation
        # input : 2 function, undoFunction, redoFunction
        # output : an object of class Operation
        self._undo = undoFunction
        self._redo = redoFunction

    def undo(self):
        # this function calls the function undo
        self._undo()

    def redo(self):
        # this function calls the function redo
        self._redo()
