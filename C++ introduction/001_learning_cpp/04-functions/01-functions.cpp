// Code notes on the C++ inroduction course from LinkedIn learning
// Created by Arkadii Semenov, 2022.12.08

#include <iostream>

// Functions:
//   Procedural blocks of code that return a value
//   Take parameters as the arguments

int add(int a, int b) {
  return a + b;
}

int square(int x) {
  x = x*x;
  return x;
}

void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

void swap(int& x, int& y) {
  int temp = x;
  x = y;
  y = temp;
}

int main() {
  std::cout << add(1, 3) << std::endl;

  int a = 9, b;
  b = square(a);

  std::cout << "a = " << a << ", b = " << b << std::endl;
  swap(&a, &b);

  std::cout << "a = " << a << ", b = " << b << std::endl;
  swap(a, b);
 
  std::cout << "a = " << a << ", b = " << b << std::endl;
  return 0;
}
