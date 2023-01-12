// Code notes on the C++ inroduction course from LinkedIn learning
// Created by Arkadii Semenov, 2022.12.07

#include <iostream>
#include <string>

#include "cow.h"

/*
Idea of compilation of the C++ code
The C++ code is compiled from different parts

Compiler   : [C++ Source Code (by user)]
                    |
                    V
Assembler  : [Assembly File]  [Assembly File (by user for some goals)]
                    |                |
                    V                V
Linker     : [Object File]    [Object File]     [Object File (from libraries)]
                  \                  |            /
                        [[EXECUTABLE BINARY FILE]]
*/


int main() {
  cow my_cow("Hildy", 7, pet);
  
  std::cout << "Cow name:    " << my_cow.get_name() << std::endl;
  std::cout << "Cow age:     " << my_cow.get_age() << std::endl;
  std::cout << "Cow purpose: " << (int) my_cow.get_purpose() << std::endl;

  return 0;
}
