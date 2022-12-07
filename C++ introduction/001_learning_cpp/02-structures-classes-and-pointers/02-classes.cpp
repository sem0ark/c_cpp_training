// Code notes on the C++ inroduction course from LinkedIn learning
// Created by Arkadii Semenov, 2022.12.07

#include <iostream>
#include <string>

// Classes:
// - Basic elements of OOP
// - Contain data and functions
// - Useful for implementing models
// - The same as in Java and Python

// Types of data / methods:
// - Private -> only accessable to inner structure of class / object
// - Protected -> only accessable to inner structure of class / object and inheritans
// - Public -> accessable to everyone

// NB! You should keep data private as possible
//     Use *getters* and *setters* for changing and reading

enum cow_purpose {dairy, meat, hide, pet};

class cow{
public:
  // There we can see the example of overloading a function
  // We've created a new version of a constructor for the class
  //  so it'd contain parameters for initialisation
  cow(std::string name_i, int age_i, unsigned char purpose_i){
    name = name_i;
    age = age_i;
    purpose = purpose_i;
  }

  // Getters -> typed functions that return the value
  std::string get_name(){
    return name;
  }
  int get_age(){
    return age;
  }
  unsigned char get_purpose(){
    return purpose;
  }

  // Setters -> void functions that change some value to another
  void set_age(int new_age){
    age = new_age;
  }
  void set_name(std::string new_name){
    name = new_name;
  }
  void set_age(unsigned char new_purpose){
    purpose = new_purpose;
  }

private:
  std::string name;
  int age;
  unsigned char purpose;
};


int main() {
  cow my_cow("Hildy", 7, pet);
  
  std::cout << "Cow name:    " << my_cow.get_name() << std::endl;
  std::cout << "Cow age:     " << my_cow.get_age() << std::endl;
  std::cout << "Cow purpose: " << (int) my_cow.get_purpose() << std::endl;

  return 0;
}
