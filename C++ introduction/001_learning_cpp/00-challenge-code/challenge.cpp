// Code notes on the C++ inroduction course from LinkedIn learning
// Created by Arkadii Semenov, 2022.12.07
// The solution to the "challenge" from the chapters of the course

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

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
  Recorder(
    std::ifstream& in_stream,
    std::string& fn_students,
    std::string& fn_courses,
    std::string& fn_grades)
  {
    parse_students(in_stream, fn_students);
    parse_courses(in_stream, fn_courses);
    parse_grades(in_stream, fn_grades);
  }

  void parse_students(std::ifstream& in_stream, std::string fn) {
    std::string str, name;
    int sid, count;

    in_stream.open(fn);
    if(in_stream.fail()) {
      std::cout << "Couldn't open file : " << fn << std::endl;
    } else {
      while(!in_stream.eof()) {
        getline(in_stream, str);
        sid = stoi(str);
        getline(in_stream, str);
        name = str;
        add_student(Student(sid, name));
        count++;
        
        // std::cout << sid << name << std::endl;
      }
    }
    in_stream.close();
    std::cout << "Found " << count << " students" << std::endl;
  }

  void parse_courses(std::ifstream& in_stream, std::string fn) {
    std::string str, name;
    int cid, points, count;

    in_stream.open(fn);
    if(in_stream.fail()) {
      std::cout << "Couldn't open file : " << fn << std::endl;
    } else {
      while(!in_stream.eof()) {
        getline(in_stream, str);
        cid = stoi(str);
        getline(in_stream, str);
        name = str;
        getline(in_stream, str);
        points = stoi(str);
        add_course(Course(cid, name, points));
        count++;
        
        // std::cout << cid << name << points << std::endl;
      }
    }
    in_stream.close();
    std::cout << "Found " << count << " courses" << std::endl;
  }

  void parse_grades(std::ifstream& in_stream, std::string fn) {
    std::string str;
    char grade;
    int sid, cid, count;

    in_stream.open(fn);
    if(in_stream.fail()) {
      std::cout << "Couldn't open file : " << fn << std::endl;
    } else {
      while(!in_stream.eof()) {
        getline(in_stream, str);
        sid = stoi(str);
        getline(in_stream, str);
        cid = stoi(str);
        getline(in_stream, str);
        grade = str[0];
        add_grade(Grade(sid, cid, grade));
        count++;
        
        // std::cout << sid << cid << grade << std::endl;
      }
    }
    in_stream.close();
    std::cout << "Found " << count << " grades" << std::endl;
  }

  void add_student(Student student) { students.push_back(student); }
  void add_course(Course course)    { courses.push_back(course); }
  void add_grade(Grade grade)       { grades.push_back(grade); }

  void student_report(std::ofstream& out_stream, std::string fn) {
    out_stream.open(fn);

    for(auto& st : students) {
      out_stream << "Student name: " << st.get_name() << std::endl;
      out_stream << "Picked courses: " << std::endl;

      for(auto& crs : courses) {
        for(auto& grd : grades) {
          if (grd.get_course_id() == crs.get_id() &&
              grd.get_student_id() == st.get_id()) {
            out_stream << crs.get_name() << ": " << grd.get_grade() << std::endl;
            break;
          }
        }
      }
      out_stream << "GPA: " << get_gpa(st.get_id()) << std::endl;
      out_stream << "=================================================" << std::endl;
    }
    
    out_stream.close();
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

std::ifstream inFile;
std::ofstream outFile;

int main() {
  std::string fns = "students.txt";
  std::string fnc = "courses.txt";
  std::string fng = "grades.txt";
  std::string fnr = "report.txt";

  Recorder *rec = new Recorder(inFile, fns, fnc, fng);
  rec->student_report(outFile, fnr);
  return 0;
}
