import unittest
from service import *
from validators import *
class Tests(unittest.TestCase):

    def test_create_student(self):
        validation_stud = valid_stud()
        stud_id = "7"
        stud_name = "Andrei"
        stud= student(stud_id, stud_name)
        self.assertTrue(stud.get_stud_id() == "7")
        self.assertTrue (stud.get_name() == "Andrei")
        self.assertTrue(stud.__str__() == "student_id : 7    student_name : Andrei")
        new_name = "Mihai"
        stud.set_name(new_name)
        self.assertTrue (stud.get_name() == "Mihai")
        other_stud= student(stud_id, new_name)
        self.assertTrue (stud == other_stud)
        stud_id = ""
        stud_name=""
        stud3 = student(stud_id, stud_name)
        self.assertRaises(validerror, validation_stud.check_stud, stud3)

    def test_create_subject(self):
        validation_sub = valid_sub()
        sub_id = "1"
        sub_name = "Math"
        sub= subject(sub_id, sub_name)
        self.assertTrue(sub.get_sub_id() == "1")
        self.assertTrue (sub.get_name() == "Math")
        self.assertTrue(sub.__str__() == "subject_id : 1    subject_name : Math")
        new_name = "Algebra"
        sub.set_name(new_name)
        self.assertTrue (sub.get_name() == "Algebra")
        other_sub= subject(sub_id, new_name)
        self.assertTrue (sub == other_sub)
        sub_id = ""
        sub_name = ""
        sub3 = subject(sub_id, sub_name)
        self.assertRaises(validerror, validation_sub.check_sub, sub3)

    def test_create_grade(self):
        validation_grade= valid_grade()
        stud_id = "7"
        sub_id = "1"
        stud_name = "Andrei"
        sub_name = "Math"
        stud = student(stud_id, stud_name)
        sub = subject(sub_id, sub_name)
        val= 7.8
        grd= grade(stud, sub,val )
        self.assertTrue(grd.get_student() == stud)
        self.assertTrue(grd.get_subject() == sub)
        self.assertTrue(grd.get_val() == val)
        self.assertTrue(grd.__str__() == "Student Andrei with id : 7 took a 7.8 at object Math with id : 1")
        val = 0
        grd2 = grade(stud, sub, val)
        self.assertRaises(validerror, validation_grade.check_grade, grd2)

    def test_add_student(self):
        undo_srv = undo()
        validation_students = valid_stud()
        repo_studs = Repo_studs_subjs()
        srv_stud = service_students(undo_srv,repo_studs, validation_students)
        stud_id = "7"
        stud_name = "Andrei"
        stud = student(stud_id, stud_name)
        srv_stud.add(stud)
        self.assertTrue (srv_stud.get_students() == [stud])
        stud_id = "10"
        stud_name = "Mihai"
        stud2 = student(stud_id, stud_name)
        srv_stud.add(stud2)
        self.assertTrue (len(srv_stud.get_students()) == 2 )
        self.assertTrue(repo_studs.size() == 2)
        self.assertTrue (srv_stud.get_students()[-1] == stud2)
        self.assertRaises(repoerror, srv_stud.add, stud)

    def test_add_subject(self):
        undo_srv = undo()
        validation_subjects = valid_sub()
        repo_subjs = Repo_studs_subjs()
        srv_sub = service_subjects(undo_srv,repo_subjs, validation_subjects)
        sub_id = "1"
        sub_name = "Math"
        sub = subject(sub_id, sub_name)
        srv_sub.add(sub)
        self.assertTrue (srv_sub.get_subjects() == [sub])
        sub_id = "15"
        sub_name = "Logic"
        sub2 = subject(sub_id, sub_name)
        srv_sub.add(sub2)
        self.assertTrue (len(srv_sub.get_subjects()) == 2 )
        self.assertTrue(repo_subjs.size() == 2)
        self.assertTrue (srv_sub.get_subjects()[-1] == sub2)
        self.assertRaises(repoerror, srv_sub.add, sub)

    def test_add_grade(self):
        undo_srv= undo()
        validation_students = valid_stud()
        validation_subjects = valid_sub()
        validation_grades = valid_grade()
        repo_studs = Repo_studs_subjs()
        repo_subjs = Repo_studs_subjs()
        repo_grades = Repo_grades()
        srv_stud = service_students(undo_srv,repo_studs, validation_students)
        srv_sub = service_subjects(undo_srv,repo_subjs, validation_subjects)
        srv_grd = service_grades(undo_srv,repo_grades, repo_studs, repo_subjs, validation_grades, validation_students, validation_subjects)
        stud_id = "8"
        sub_id = "2"
        stud_name = "Andrei"
        sub_name = "Math"
        stud = student(stud_id, stud_name)
        sub = subject(sub_id, sub_name)
        srv_stud.add(stud)
        srv_sub.add(sub)
        val = 7.8
        grd = grade(stud, sub, val)
        srv_grd.add(grd)
        self.assertTrue (len(srv_grd.get_grades()) == 1)
        srv_grd.remove_last_grade()
        srv_grd.add(grd)
        self.assertTrue(len(srv_grd.return_grades()) == 1)

    def test_add_student_with_grades(self):
        l=list()
        undo_srv = undo()
        validation_students = valid_stud()
        validation_subjects = valid_sub()
        validation_grades = valid_grade()
        repo_studs = Repo_studs_subjs()
        repo_subjs = Repo_studs_subjs()
        repo_grades = Repo_grades()
        srv_stud = service_students(undo_srv, repo_studs, validation_students)
        srv_sub = service_subjects(undo_srv, repo_subjs, validation_subjects)
        srv_grd = service_grades(undo_srv, repo_grades, repo_studs, repo_subjs, validation_grades, validation_students,
                                 validation_subjects)
        stud_id = "8"
        sub_id = "2"
        stud_name = "Andrei"
        sub_name = "Math"
        stud = student(stud_id, stud_name)
        sub = subject(sub_id, sub_name)
        srv_sub.add(sub)
        val = 7.8
        grd = grade(stud, sub, val)
        l.append(grd)
        val = 8
        grd = grade(stud, sub, val)
        l.append(grd)
        srv_grd.add_student_with_grades(stud, l)
        self.assertTrue(len(srv_grd.return_grades()) == 2)
        self.assertTrue(len(srv_stud.get_students()) == 1)

    def test_add_subject_with_grades(self):
        l=list()
        undo_srv = undo()
        validation_students = valid_stud()
        validation_subjects = valid_sub()
        validation_grades = valid_grade()
        repo_studs = Repo_studs_subjs()
        repo_subjs = Repo_studs_subjs()
        repo_grades = Repo_grades()
        srv_stud = service_students(undo_srv, repo_studs, validation_students)
        srv_sub = service_subjects(undo_srv, repo_subjs, validation_subjects)
        srv_grd = service_grades(undo_srv, repo_grades, repo_studs, repo_subjs, validation_grades, validation_students,
                                 validation_subjects)
        stud_id = "8"
        sub_id = "2"
        stud_name = "Andrei"
        sub_name = "Math"
        stud = student(stud_id, stud_name)
        sub = subject(sub_id, sub_name)
        srv_stud.add(stud)
        val = 7.8
        grd = grade(stud, sub, val)
        l.append(grd)
        val = 8
        grd = grade(stud, sub, val)
        l.append(grd)
        srv_grd.add_subject_with_grades(sub, l)
        self.assertTrue(len(srv_grd.return_grades()) == 2)
        self.assertTrue(len(srv_stud.get_students()) == 1)

    def test_remove_student(self):
        undo_srv = undo()
        validation_students = valid_stud()
        repo_studs = Repo_studs_subjs()
        srv_stud = service_students(undo_srv,repo_studs, validation_students)
        stud_id = "7"
        stud_name = "Andrei"
        stud = student(stud_id, stud_name)
        stud_id2 = "8"
        stud2 = student(stud_id2, stud_name)
        srv_stud.add(stud)
        srv_stud.add(stud2)
        srv_stud.remove(stud)
        self.assertTrue (len(srv_stud.get_students()) == 1)

    def test_remove_subject(self):
        undo_srv = undo()
        validation_subjects = valid_sub()
        repo_subjs = Repo_studs_subjs()
        srv_sub = service_subjects(undo_srv,repo_subjs, validation_subjects)
        sub_id = "1"
        sub_name = "Math"
        sub = subject(sub_id, sub_name)
        srv_sub.add(sub)
        sub_id2 = "2"
        sub2 = subject(sub_id2, sub_name)
        srv_sub.add(sub2)
        sub_id3 = "3"
        sub3 = subject(sub_id3, sub_name)
        srv_sub.remove(sub)
        self.assertTrue (len(srv_sub.get_subjects()) == 1)
        self.assertRaises(repoerror, srv_sub.remove, sub3)

    def test_remove_grades(self):
        undo_srv = undo()
        validation_students = valid_stud()
        validation_subjects = valid_sub()
        validation_grades = valid_grade()
        repo_studs = Repo_studs_subjs()
        repo_subjs = Repo_studs_subjs()
        repo_grades = Repo_grades()
        srv_stud = service_students(undo_srv,repo_studs, validation_students)
        srv_sub = service_subjects(undo_srv,repo_subjs, validation_subjects)
        srv_grd = service_grades(undo_srv,repo_grades, repo_studs, repo_subjs, validation_grades, validation_students, validation_subjects)
        stud_id = "8"
        sub_id = "2"
        stud_name = "Andrei"
        sub_name = "Math"
        stud = student(stud_id, stud_name)
        sub = subject(sub_id, sub_name)
        srv_stud.add(stud)
        srv_sub.add(sub)
        val = 7.8
        grd = grade(stud, sub, val)
        srv_grd.add(grd)
        stud_id2 = "9"
        stud2 = student(stud_id2, stud_name)
        srv_stud.add(stud2)
        val = 8
        grd2 = grade(stud2, sub, val)
        srv_grd.add(grd2)
        srv_grd.remove_by_student(stud)
        srv_stud.add(stud)
        self.assertTrue(repo_grades.size() == 1)
        sub_id2 = "10"
        sub2= subject(sub_id2, sub_name)
        srv_sub.add(sub2)
        val = 5
        grd3 = grade(stud, sub2, val)
        srv_grd.add(grd3)
        srv_grd.remove_by_subject(sub)
        self.assertTrue(repo_grades.size() == 1)

    def test_update_student(self):
        undo_srv = undo()
        validation_students = valid_stud()
        repo_studs = Repo_studs_subjs()
        srv_stud = service_students(undo_srv, repo_studs, validation_students)
        stud_id = "7"
        stud_name = "Andrei"
        stud = student(stud_id, stud_name)
        srv_stud.add(stud)
        new_name= "Mihai"
        stud2 = student(stud_id, new_name)
        srv_stud.update(stud2, new_name)
        self.assertTrue (stud.get_name() == "Mihai")
        self.assertTrue(srv_stud.search_element(stud2) == stud)

    def test_update_subject(self):
        undo_srv = undo()
        validation_subjects = valid_sub()
        repo_subjs = Repo_studs_subjs()
        srv_sub = service_subjects(undo_srv,repo_subjs, validation_subjects)
        sub_id = "1"
        sub_name = "Math"
        sub = subject(sub_id, sub_name)
        srv_sub.add(sub)
        new_name= "Algebra"
        sub2 = subject(sub_id, new_name)
        srv_sub.update(sub2, new_name)
        self.assertTrue (sub.get_name() == "Algebra")
        self.assertTrue(srv_sub.search_element(sub2) == sub)

    def test_partial_student(self):
        undo_srv = undo()
        validation_students = valid_stud()
        repo_studs = Repo_studs_subjs()
        srv_stud = service_students(undo_srv,repo_studs, validation_students)
        stud_id = "an"
        stud_name = "Andrei"
        stud = student(stud_id, stud_name)
        srv_stud.add(stud)
        stud_id = "al"
        stud_name = "Alexandru"
        stud2 = student(stud_id, stud_name)
        srv_stud.add(stud2)
        l = srv_stud.search_partial_student("ID", "a")
        self.assertTrue(len(l) == 2)
        m = srv_stud.search_partial_student("name", "ndr")
        self.assertTrue(len(m) == 2)

    def test_partial_subject(self):
        undo_srv= undo()
        validation_subjects = valid_sub()
        repo_subjs = Repo_studs_subjs()
        srv_sub = service_subjects(undo_srv,repo_subjs, validation_subjects)
        sub_id = "math1"
        sub_name = "Algebra"
        sub = subject(sub_id, sub_name)
        srv_sub.add(sub)
        sub_id = "math2"
        sub_name = "Analysis"
        sub2 = subject(sub_id, sub_name)
        srv_sub.add(sub2)
        l = srv_sub.search_partial_subject("ID", "math")
        self.assertTrue(len(l) == 2)
        m = srv_sub.search_partial_subject("name", "al")
        self.assertTrue(len(m) == 2)

    def test_failing_students(self):
        undo_srv = undo()
        validation_students = valid_stud()
        validation_subjects = valid_sub()
        validation_grades = valid_grade()
        repo_studs = Repo_studs_subjs()
        repo_subjs = Repo_studs_subjs()
        repo_grades = Repo_grades()
        srv_stud = service_students(undo_srv,repo_studs, validation_students)
        srv_sub = service_subjects(undo_srv,repo_subjs, validation_subjects)
        srv_grd = service_grades(undo_srv,repo_grades, repo_studs, repo_subjs, validation_grades, validation_students, validation_subjects)
        stud_id = "8"
        sub_id = "2"
        stud_name = "Andrei"
        sub_name = "Math"
        stud = student(stud_id, stud_name)
        sub = subject(sub_id, sub_name)
        srv_stud.add(stud)
        srv_sub.add(sub)
        val = 8
        grd = grade(stud, sub, val)
        srv_grd.add(grd)
        stud_id = "5"
        sub_id = "3"
        stud_name = "Alex"
        sub_name = "Computer_Science"
        stud2 = student(stud_id, stud_name)
        sub2 = subject(sub_id, sub_name)
        srv_stud.add(stud2)
        srv_sub.add(sub2)
        val = 1
        grd = grade(stud2, sub2, val)
        srv_grd.add(grd)
        l = srv_grd.failing_students()
        self.assertTrue(len(l) == 1)
        self.assertTrue(l[0]["student"] == stud2)
        self.assertTrue(l[0]["subject"] == sub2)
        self.assertTrue(l[0]["average"] == 1)

    def test_best_students(self):
        undo_srv = undo()
        validation_students = valid_stud()
        validation_subjects = valid_sub()
        validation_grades = valid_grade()
        repo_studs = Repo_studs_subjs()
        repo_subjs = Repo_studs_subjs()
        repo_grades = Repo_grades()
        srv_stud = service_students(undo_srv,repo_studs, validation_students)
        srv_sub = service_subjects(undo_srv,repo_subjs, validation_subjects)
        srv_grd = service_grades(undo_srv,repo_grades, repo_studs, repo_subjs, validation_grades, validation_students, validation_subjects)
        stud_id = "8"
        sub_id = "2"
        stud_name = "Andrei"
        sub_name = "Math"
        stud = student(stud_id, stud_name)
        sub = subject(sub_id, sub_name)
        srv_stud.add(stud)
        srv_sub.add(sub)
        val = 8
        grd = grade(stud, sub, val)
        srv_grd.add(grd)
        sub_id = "3"
        sub_name = "Computer_Science"
        sub2 = subject(sub_id, sub_name)
        srv_sub.add(sub2)
        val = 5
        grd = grade(stud, sub2, val)
        srv_grd.add(grd)
        stud_id = "7"
        stud_name = "Alex"
        stud2 = student(stud_id, stud_name)
        srv_stud.add(stud2)
        val = 10
        grd = grade(stud2, sub, val)
        srv_grd.add(grd)
        l = srv_grd.best_students()
        self.assertTrue(len(l) == 2)
        self.assertTrue(l[0]["student"] == stud2 )
        self.assertTrue(l[1]["student"] == stud)

    def test_sorted_subjects(self):
        undo_srv = undo()
        validation_students = valid_stud()
        validation_subjects = valid_sub()
        validation_grades = valid_grade()
        repo_studs = Repo_studs_subjs()
        repo_subjs = Repo_studs_subjs()
        repo_grades = Repo_grades()
        srv_stud = service_students(undo_srv,repo_studs, validation_students)
        srv_sub = service_subjects(undo_srv,repo_subjs, validation_subjects)
        srv_grd = service_grades(undo_srv,repo_grades, repo_studs, repo_subjs, validation_grades, validation_students, validation_subjects)
        stud_id = "8"
        sub_id = "2"
        stud_name = "Andrei"
        sub_name = "Math"
        stud = student(stud_id, stud_name)
        sub = subject(sub_id, sub_name)
        srv_stud.add(stud)
        srv_sub.add(sub)
        val = 6
        grd = grade(stud, sub, val)
        srv_grd.add(grd)
        sub_id = "3"
        sub_name = "Computer_Science"
        sub2 = subject(sub_id, sub_name)
        srv_sub.add(sub2)
        val = 9
        grd = grade(stud, sub2, val)
        srv_grd.add(grd)
        stud_id = "7"
        stud_name = "Alex"
        stud2 = student(stud_id, stud_name)
        srv_stud.add(stud2)
        val = 8
        grd = grade(stud2, sub, val)
        srv_grd.add(grd)
        l = srv_grd.sorted_subjects()
        self.assertTrue(len(l) == 2)
        self.assertTrue(l[0]["subject"] == sub2)
        self.assertTrue(l[0]["average"] == 9)
        self.assertTrue(l[1]["subject"] == sub)
        self.assertTrue(l[1]["average"] == 7)

    def test_undo(self):
        undo_srv = undo()
        validation_students = valid_stud()
        validation_subjects = valid_sub()
        validation_grades = valid_grade()
        repo_studs = Repo_studs_subjs()
        repo_subjs = Repo_studs_subjs()
        repo_grades = Repo_grades()
        srv_stud = service_students(undo_srv, repo_studs, validation_students)
        srv_sub = service_subjects(undo_srv, repo_subjs, validation_subjects)
        srv_grd = service_grades(undo_srv, repo_grades, repo_studs, repo_subjs, validation_grades, validation_students,
                                 validation_subjects)
        stud_id = "8"
        sub_id = "2"
        stud_name = "Andrei"
        sub_name = "Math"
        stud = student(stud_id, stud_name)
        sub = subject(sub_id, sub_name)
        srv_stud.add(stud)
        srv_sub.add(sub)
        val = 7.8
        grd = grade(stud, sub, val)
        srv_grd.add(grd)
        undo_srv.undo()
        self.assertTrue(len(srv_grd.return_grades()) == 0)
        undo_srv.redo()
        self.assertTrue(len(srv_grd.return_grades()) == 1)