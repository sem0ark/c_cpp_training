// Code notes on the C++ inroduction course from LinkedIn learning
// Created by Arkadii Semenov, 2022.12.07
// The solution to the "challenge" from the chapters of the course

#include <iostream>
#include <string>
#include <vector>

class Student {
public:
  Student(int id_i, std::string name_i) {
    id = id_i;
    name = name_i;
  }

  int get_id() {
    return id;
  }
  std::string get_name() {
    return name;
  }

private:
  int id;
  std::string name;
};

class Course {
public:
  Course(int id_i, std::string name_i, int p_i) {
    id = id_i;
    name = name_i;
    points = p_i;
  }

  int get_id() {
    return id;
  }
  int get_points() {
    return points;
  }
  std::string get_name() {
    return name;
  }

private:
  int id;
  int points;
  std::string name;
};

class Grade {
public:
  Grade(int id_s, int id_c, char grade_i) {
    id_course = id_c;
    id_student = id_s;
    grade = grade_i;
  }

  int get_course_id() {
    return id_course;
  }
  int get_student_id() {
    return id_student;
  }
  char get_grade() {
    return grade;
  }

private:
  int id_course;
  int id_student;
  char grade;
  std::string name;
};

float grade2f(char grd) {
  switch(grd) {
    case 'A': return 4.0f;
    case 'B': return 3.0f;
    case 'C': return 2.0f;
    case 'D': return 1.0f;
    default:  return 0.0f;
  }
}


class Recorder{
public:
  void add_student(Student student) { students.push_back(student); }
  void add_course(Course course)    { courses.push_back(course); }
  void add_grade(Grade grade)       { grades.push_back(grade); }

  void student_report(int student_id) {
    int student_ind = 0;
    while(students[student_ind].get_id() != student_id) student_ind++;

    if(student_ind == students.size()) return;

    std::cout << "Student name: " << students[student_ind].get_name() << std::endl;
    std::cout << "Picked courses: " << std::endl;

    for(auto& crs : courses) {
      bool picked = false;
      for(auto& grd : grades) {
        if (grd.get_course_id() == crs.get_id() &&
            grd.get_student_id() == students[student_ind].get_id()) {
          picked = true;
          break;
        }
      }
      if(picked) {
        std::cout << crs.get_name() << std::endl;
      }
    }
    std::cout << "GPA: " << get_gpa(student_id) << std::endl;

  }

  float get_gpa(int student_id) {
    float points  = 0.0f;
    float credits = 0.0f;

    for(auto& grd: grades) {
      if(grd.get_student_id() != student_id) continue;

      for(auto& crs : courses) {
        if(crs.get_id() == grd.get_course_id()) {
          credits += crs.get_points();
          points  += grade2f(grd.get_grade()) * crs.get_points();
          break;
        }
      }
    }

    return points / credits;
  }
private:
  std::vector<Student> students;
  std::vector<Course> courses;
  std::vector<Grade> grades;
};

Recorder rec = Recorder();

int main() {

  
  rec.add_student(Student(1,"George P. Burdell"));
  rec.add_student(Student(2,"Nancy Rhodes"));

  rec.add_course(Course(1,"Algebra",5));
  rec.add_course(Course(2,"Physics",4));
  rec.add_course(Course(3,"English",3));
  rec.add_course(Course(4,"Economics",4));

  
  rec.add_grade(Grade(1,1,'B'));
  rec.add_grade(Grade(1,2,'A'));
  rec.add_grade(Grade(1,3,'C'));
  rec.add_grade(Grade(2,1,'A'));
  rec.add_grade(Grade(2,2,'A'));
  rec.add_grade(Grade(2,4,'B'));

  rec.student_report(1);

  return 0;
}
