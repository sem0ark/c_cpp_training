// Code notes on the C++ inroduction course from LinkedIn learning
// Created by Arkadii Semenov, 2022.12.07

#include <iostream>
#include <cstdint>

float flt = -7.44f;

int32_t sgn;
uint32_t unsgn;


// in inline type casting with numerical values we would get
// casting: int -> float -> double

int main() {
  // these are examples of internal type casting
  sgn = flt; // the value is preserved -> -7.44 goes to -7
  unsgn = sgn; // the value isn't preserved

  std::cout << "   float: " << flt << std::endl;
  std::cout << "  signed: " << sgn << std::endl;
  std::cout << "unsigned: " << unsgn << std::endl;
  std::cout << std::endl;

  int fahr = 100;
  // int cels = (5 / 9) * (fahr - 32); // here (5 / 9) -> constant and it would result as 0
  int cels = (5 / 9.0) * (fahr - 32);

  std::cout << "fahr: " << fahr << std::endl;
  std::cout << "cels: " << cels << std::endl;
  std::cout << std::endl;

  float weight = 10.99;
  std::cout << "Float: " << weight << std::endl;
  std::cout << "Int part: " << (int) weight << std::endl;
  std::cout << "Frac part: "<< weight - (int)weight << std::endl;

  return 0;
}
