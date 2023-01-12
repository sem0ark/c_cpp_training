// Code notes on the C++ inroduction course from LinkedIn learning
// Created by Arkadii Semenov, 2022.12.07

#include <iostream>

#define AGE_LENGTH 4

// Definition of a static array [0 : AGE_LENGTH-1]
int age[AGE_LENGTH];

// Definition os a static array on fly
float temperature[] = {31.5f, 32.7f, 38.9f};

int main() {
  // Setting values to the array
  age[0] = 25;
  age[1] = 21;
  age[2] = 22;
  age[3] = 27;

  std::cout << "Arr length = " << AGE_LENGTH << std::endl;
  std::cout << "Age[0] = " << age[0] << std::endl;
  std::cout << "Age[1] = " << age[1] << std::endl;
  std::cout << "Age[2] = " << age[2] << std::endl;
  std::cout << "Age[3] = " << age[3] << std::endl;

  std::cout << "temperature[1] = " << temperature[0] << std::endl;
  std::cout << "temperature[2] = " << temperature[1] << std::endl;
  std::cout << "temperature[3] = " << temperature[2] << std::endl;

  return 0;
}
