// Code notes on the C++ inroduction course from LinkedIn learning
// Created by Arkadii Semenov, 2022.12.06

#include <iostream>
#include <string>
#include <cstdint>

// Preprocessing directives, macros

#define CAPACITY 5000
#define DEBUG

/*
constants
- identifiers with values that won't change during the execution
- Useful parameters for the code
can be created in different ways:
-> #define -> uses find and replace method of input, BAD PRACTICE
-> const -> used in regular declaration, scope encapsulation is enforced
*/

int main() {
  int32_t large = CAPACITY;
  int8_t small = 37;
  
  large += small;

// if DEBUG was previously defined  
#ifdef DEBUG
  std::cout << "[About to perform the addition]" << std::endl;
#endif

  std::cout << "THe larger intereg is " << large << std::endl;

  return 0;
}
