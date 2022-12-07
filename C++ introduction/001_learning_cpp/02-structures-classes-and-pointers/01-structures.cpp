// Code notes on the C++ inroduction course from LinkedIn learning
// Created by Arkadii Semenov, 2022.12.07

#include <iostream>
#include <string>

// Enumerations ->
//    a set of constants
//    usually in a sequence
//    NB! use them for encapsulation of constants -> better readability

enum cow_purpose {
  dairy,
  meat,
  hide,
  pet
};

// Structures ->
//    container for heterogeneous data
//    It is now working like in C

struct cow{
  std::string name;
  int age;
  unsigned char purpose;
};


int main() {
  cow my_cow;
  // Assignment to the struct values
  my_cow.age = 5;
  my_cow.name = "Betsy";
  my_cow.purpose = dairy;

  std::cout << "Cow name:    " << my_cow.name << std::endl;
  std::cout << "Cow age:     " << my_cow.age << std::endl;
  std::cout << "Cow purpose: " << (int) my_cow.purpose << std::endl;

  return 0;
}
