from service import *

class ui(object) :

    def __init__(self, srv_stud, srv_sub, srv_grd, undo_srv):
        self.__srv_stud = srv_stud
        self.__srv_sub = srv_sub
        self.__srv_grd= srv_grd
        self.__undo_srv = undo_srv

    def ui_add_studs_subjs(self):
        t= input("Please introduce the type to be added (student/ subject) :").strip()
        if t != "student" and t != "subject" :
            raise typeerror("The type is not correct !")
        if t == "student" :
            self.ui_add_student()
        elif t == "subject":
            self.ui_add_subject()

    def ui_add_student(self) :
        stud_id= input("Please introduce the id of the student : ").strip()
        name=input("Please introduce the name of the student : ").strip()
        stud= student(stud_id, name)
        self.__srv_stud.add(stud)

    def ui_add_subject(self):
        sub_id = input("Please introduce the id of the subject : ").strip()
        name = input("Please introduce the name of the subject : ").strip()
        sub = subject(sub_id, name)
        self.__srv_sub.add(sub)

    def ui_add_grades(self):
        stud_id = input("Please introduce the id of the student : ").strip()
        sub_id = input("Please introduce the id of the subject : ").strip()
        val = input("Please introduce the value of the grade : ").strip()
        val = float(val)
        stud = student(stud_id, None)
        sub = subject(sub_id, None)
        grd = grade(stud, sub, val)
        self.__srv_grd.add(grd)

    def ui_remove(self):
        t = input("Please introduce the type to be removed (student/ subject) :").strip()
        if t != "student" and t != "subject" :
            raise typeerror("The type is not correct !")
        if t == "student" :
            stud_id= input("Please introduce the id of the student : ").strip()
            stud = student(stud_id, None)
            self.__srv_grd.remove_by_student(stud)
        elif t == "subject" :
            sub_id = input("Please introduce the id of the subject : ").strip()
            sub = subject(sub_id, None)
            self.__srv_grd.remove_by_subject(sub)

    def ui_update(self):
        t = input("Please introduce the type to be updated (student/ subject) :").strip()
        if t != "student" and t != "subject" :
            raise typeerror("The type is not correct !")
        if t == "student" :
            stud_id= input("Please introduce the id of the student : ").strip()
            name = input("Please introduce the new name of the student : ").strip()
            stud = student(stud_id, name)
            self.__srv_stud.update(stud, name)
        elif t == "subject" :
            sub_id = input("Please introduce the id of the subject : ").strip()
            name = input("Please introduce the new name of the subject : ").strip()
            sub = subject(sub_id, name)
            self.__srv_sub.update(sub, name)

    def ui_display(self):
        t = input("Please introduce the type to be displayed (student/ subject/ grade) :").strip()
        if t != "student" and t != "subject" and t != "grade" :
            raise typeerror("The type is not correct !")
        if t == "student" :
            self.ui_display_students()
        if t == "subject" :
            self.ui_display_subjects()
        if t == "grade" :
            self.ui_display_grades()

    def ui_display_students(self):
        ok = 0
        for stud in self.__srv_stud.get_students():
            ok = 1
            print(stud)
        if ok == 0:
            print("There are no students in the list.")

    def ui_display_subjects(self):
        ok = 0
        for sub in self.__srv_sub.get_subjects():
            ok = 1
            print(sub)
        if ok == 0:
            print("There are no subjects in the list.")

    def ui_display_grades(self):
        ok = 0
        l = self.__srv_grd.return_grades()
        for grd in l:
            ok = 1
            print(grd)
        if ok == 0:
            print("There are no grades in the list.")

    def ui_search(self):
        l=list()
        t = input("Please introduce the type to be searched (student/ subject) :").strip()
        if t != "student" and t != "subject" :
            raise typeerror("The type is not correct !")
        if t == "student":
            self.ui_search_student()
        elif t == "subject" :
            self.ui_search_subject()

    def ui_search_student(self):
        type_of_search = input("Please introduce how do you want to search the student (ID/ name) : ").strip()
        if type_of_search != "ID" and type_of_search != "name":
            raise typeerror("The type is not correct !")
        pattern = input("Introduce the student : ").strip()
        l = self.__srv_stud.search_partial_student(type_of_search, pattern)
        for i in range(len(l)):
            print(l[i])
        if len(l) == 0 :
            print("There are no such students in the list.")

    def ui_search_subject(self):
        type_of_search = input("Please introduce how do you want to search the subject (ID/ name) : ").strip()
        if type_of_search != "ID" and type_of_search != "name":
            raise typeerror("The type is not correct !")
        pattern = input("Introduce the subject : ").strip()
        l = self.__srv_sub.search_partial_subject(type_of_search, pattern)
        for i in range(len(l)):
            print(l[i])
        if len(l) == 0 :
            print("There are no such subjects in the list.")

    def ui_failing_students(self):
        l=list()
        l = self.__srv_grd.failing_students()
        for i in range(len(l)) :
            name_stud = l[i]["student"].get_name()
            stud_id = l[i]["student"].get_stud_id()
            name_sub = l[i]["subject"].get_name()
            sub_id = l[i]["subject"].get_sub_id()
            average = l[i]["average"]
            print("The student "+str(name_stud)+" with id : "+str(stud_id)+ " failed at object "+
                  str(name_sub)+" with id : "+str(sub_id)+ " having "+str(average))

    def ui_best_students(self):
        l=self.__srv_grd.best_students()
        for i in range(len(l)) :
            stud = l[i]["student"]
            name_stud = stud.get_name()
            stud_id = stud.get_stud_id()
            average = l[i]["average"]
            print("The student "+str(name_stud)+" with id : "+str(stud_id)+ " has the average : "
                  +str(average))

    def ui_sorted_subjects(self):
        l = self.__srv_grd.sorted_subjects()
        for i in range(len(l)) :
            sub = l[i]["subject"]
            name_sub = sub.get_name()
            sub_id = sub.get_sub_id()
            average = l[i]["average"]
            print("The subject "+str(name_sub)+" with id : "+str(sub_id)+ " has the average : "
                  +str(average))

    def ui_undo(self):
        self.__undo_srv.undo()

    def ui_redo(self):
        self.__undo_srv.redo()

    def ui_menu(self):
        commands = {
            "1" : self.ui_add_studs_subjs,
            "2" : self.ui_add_grades,
            "3" : self.ui_remove,
            "4" : self.ui_update,
            "5" : self.ui_display,
            "6" : self.ui_search,
            "7" : self.ui_failing_students,
            "8" : self.ui_best_students,
            "9" : self.ui_sorted_subjects,
            "10" : self.ui_undo,
            "11" : self.ui_redo
        }
        print("Command 1 is used to add a student or a subject.")
        print("Command 2 is used to grade a student.")
        print("Command 3 is used to remove a student or a subject.")
        print("Command 4 is used to update a student or a subject.")
        print("Command 5 is used to show the list of student, subjects or grades.")
        print("Command 6 is used to search for disciplines/students based on ID or name/title.")
        print("Command 7 is used to display all students failing at one or more disciplines")
        print("Command 8 is used to display students with the best school situation.")
        print("Command 9 is used to display all sorted disciplines.")
        print("Command 10 is used to undo.")
        print("Command 11 is used to redo.")
        print("Command 12 is used to exit the application.")
        while True :
            cmd = input("Please introduce your command : ")
            if cmd == "12" :
                return
            if cmd in commands :
                try:
                    commands[cmd]()
                except typeerror as te:
                    print(te)
                except validerror as valide:
                    print(valide)
                except repoerror as re:
                    print(re)
                except ValueError :
                    print("Incorrect value for grade !")
            else :
                print("Invalid command !")





