// Code notes on the C++ inroduction course from LinkedIn learning
// Created by Arkadii Semenov, 2022.12.07

#include <iostream>
#include <vector>

std::vector<int> numbers = {1, 2, 3, 4, 5};

// while loop
// while (condition) { CODE }
// first the condition is checked
// thenthe code is ran

// do-while loop
// do { CODE } while (condition);
// first the code is ran
// then the condition is checked

// NB! use this construction if the first
//      run definetly won't cause an error to occur


int main() {
  auto ptr = numbers.begin();

  while (ptr != numbers.end()) {
    std::cout << *ptr << " ";
    ptr = next(ptr, 1);
  }
  std::cout << std::endl;

  int i = 0;
  do {
    std::cout << numbers[i] << " ";
    i++; // postfix increment operator
  } while (i < numbers.size());

  return 0;
}
