// Code notes on the C++ inroduction course from LinkedIn learning
// Created by Arkadii Semenov, 2022.12.06

#include <iostream>
/*

## Data types

Integers:
- signed / unsigned
- char (8 bits)
- int (implementation dependent)
- NB! -> stdint.h contains types like uint32_t
         Use them for readable and independent
         integers of specified properties

Floating point numbers:
 used for real numbers
 IEEE 754 floating point standard
- float (light and imprecise)
- double (heavier)
- long double (the heaviest and the most precise)

Boolean:
- bool {true==1, false==0}

String:
Created as a string class for C++ STD library
Lots of different functions

Pointers:
Used to show the place of the objects and data on the PC

> NB! -> use cppreference.com to get more information and types

==================================

## Variables declaration

int: 123, -5, 0b1100 {binary}, 023 {octal}, 0x3A {hex}, 23U {unsigned}
float: 23.0f, 0.0f
double: 23.4, -22.5
char: 'a', 'X, '\0', '\n'
string: "hi there"

*/

// global variables
// declared in static data
int a, b=5;

/* Multi
*  line 
*  comment */

int main() {
  bool flag; // single line comment
  
  a = 7;
  flag = false;
  
  // Output examples
  std::cout << "Hi There!" << std::endl;
  std::cout << "a = " << a << std::endl;
  std::cout << "b = " << b << std::endl;
  std::cout << "flag = " << flag << std::endl;
  std::cout << "b + a = " << b + a << std::endl;
  std::cout << "b - a = " << b - a << std::endl;

  unsigned int pos;
  pos = b - a;

  std::cout << "b - a (unsigned) = " << pos << std::endl;

  return 0;
}
