// Code notes on the C++ Templates and STL course from LinkedIn learning
// Created by Arkadii Semenov, 2023.01.12

#include<iostream>
#include<string>

template<typename T> // Here we specify the generics name
T maxof(const T & a, const T & b) { // So we can use it as a type specification
  return (a > b ? a : b);
}

template<typename T>
constexpr T pi = T(3.141592653589793285L); // It is much more type safe
// **With C++>=14** we can also use templates with variables, so we can 


template<typename T>
T circle_area(const T & r) {
  return r*r*pi<T>; // Here we use different pi's for different T-types
}

int main() {
  int a = 7, b = 9;

  std::cout << "max is " << maxof<int>(a, b) << std::endl;
  std::cout << "max is " << maxof<short int>(a, b) << std::endl; // Three different functions
  std::cout << "max is " << maxof<long int>(a, b) << std::endl;
  // The specilialization - an intire copy of a function
  //    created for the specific need

  std::cout.precision(16);
  std::cout << pi<long double> << circle_area<long double>(3) << std::endl;
  std::cout << pi<double> << circle_area<double>(3) << std::endl;
  std::cout << pi<float> << circle_area<float>(3) << std::endl;
  // so we can use the specification for the variables too
  // it is useful if we need to do some changes in the templated code

  // Example:

  return 0;
}
