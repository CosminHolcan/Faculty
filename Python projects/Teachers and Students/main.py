from ui_functions import *
from GUI import *
import random

def start() :
    validation_students = valid_stud()
    validation_subjects = valid_sub()
    validation_grades = valid_grade()
    dict_settings = {
        "repository" : None,
        "students" : None,
        "subjects" : None,
        "grades" : None,
        "ui" : None
    }
    with open("settings.properties.txt", "r") as settings_file :
        lines = settings_file.readlines()
        for line in lines :
            line = line.strip()
            params = line.split("=")
            dict_settings[params[0].strip()] = params[1].strip()
    if dict_settings["repository"] == "in memory" :
        repo_studs = Repo_studs_subjs()
        repo_subjs = Repo_studs_subjs()
        repo_grades = Repo_grades()
    if dict_settings["repository"] == "text files" :
        repo_studs = File_Repo_studs_subjs(dict_settings["students"], student.read_student, student.write_student)
        repo_subjs = File_Repo_studs_subjs(dict_settings["subjects"], subject.read_subject, subject.write_subject)
        repo_grades = File_Repo_grades(dict_settings["grades"], grade.read_grade, grade.write_grade)
        repo_studs.read_from_file()
        repo_subjs.read_from_file()
        repo_grades.read_from_file()
    if dict_settings["repository"] == "binary files" :
        repo_studs = Binary_Files_Repo_studs_subjs(dict_settings["students"], student.read_student, student.write_student)
        repo_subjs = Binary_Files_Repo_studs_subjs(dict_settings["subjects"], subject.read_subject, subject.write_subject)
        repo_grades = Binary_Files_Repo_grades(dict_settings["grades"], grade.read_grade, grade.write_grade)
        repo_studs.read_from_file()
        repo_subjs.read_from_file()
        repo_grades.read_from_file()
    undo_srv = undo()
    srv_stud = service_students(undo_srv, repo_studs, validation_students)
    srv_sub = service_subjects(undo_srv, repo_subjs, validation_subjects)
    srv_grd = service_grades(undo_srv, repo_grades, repo_studs, repo_subjs, validation_grades, validation_students,
                             validation_subjects)
    if dict_settings["repository"] == "in memory":
        l1 = ["John", "James", "William", "Michael", "David", "Maria", "Emma", "Victoria", "Ellie", "Sarah"]
        l2 = ["Adams", "Smith", "Simpson", "Brown", "Thompson", "Martin", "Walker", "King", "Nelson", "Carter"]
        for i in range(5):
            nr1 = random.randint(0, 9)
            nr2 = random.randint(0, 9)
            name = ""
            name += l1[nr1]
            name += " "
            name += l2[nr2]
            stud_id = l1[nr1][0]
            stud_id += l2[nr2][0]
            for j in range(3):
                cif = random.randint(0, 9)
                cif = str(cif)
                stud_id += cif
            stud = student(stud_id, name)
            srv_stud.add(stud)
        sub = subject("Math1", "Algebra")
        srv_sub.add(sub)
        sub = subject("Math2", "Analysis")
        srv_sub.add(sub)
        sub = subject("Math3", "Logic")
        srv_sub.add(sub)
        sub = subject("CS1", "FP")
        srv_sub.add(sub)
        sub = subject("CS2", "ASC")
        srv_sub.add(sub)
        for i in range(10):
            nr = random.randint(0, 4)
            nr2 = random.randint(0, 4)
            val = round(random.uniform(1, 10), 2)
            stud = srv_stud.get_students()[nr]
            sub = srv_sub.get_subjects()[nr2]
            grd = grade(stud, sub, val)
            srv_grd.add(grd)
    ui_var = ui(srv_stud, srv_sub, srv_grd, undo_srv)
    if dict_settings["ui"] == "menu_based" :
        ui_var.ui_menu()
    elif dict_settings["ui"] == "GUI" :
        gui_var = GUI(srv_stud, srv_sub, srv_grd, undo_srv)
start()
