// Code notes on the C++ inroduction course from LinkedIn learning
// Created by Arkadii Semenov, 2022.12.07

#include <iostream>
#include <vector>

std::vector<int> numbers = {1, 2, 3, 4, 5};

// For loop is used when teh number of steps is known in advance
// for (iterator declaration; condition; inclement) { CODE }

// for (auto x : iterable) { CODE } -> is used for iterabels objects
// traversing the specified range with iterator

float avg;

int main() {
  avg = 0.0f;
  for(int i=0; i<numbers.size(); i++) {
    avg += numbers[i];
  }
  avg /= numbers.size();
  std::cout << avg << std::endl;

  avg = 0.0f;
  for(auto x : numbers) { // copies the object to x !
    avg += x;
  }
  avg /= numbers.size();
  std::cout << avg << std::endl;
  return 0;
}
