// Code notes on the C++ inroduction course from LinkedIn learning
// Created by Arkadii Semenov, 2022.12.07

#include <iostream>

#include <string>
// import string object methods

#include <cstring>
// import character arrays method (from C library)

const int LENGTH1 = 25;

char arr_str1[LENGTH1] = "Hey guys! ";
char arr_str2[] = "What's up?";
// Using arr strings isn't recommended in C++
// Use only for compatibility with C code

std::string std_str1 = "Hi everybody! ";
std::string std_str2 = "How's the going?";

int main() {
  strcat_s(arr_str1, LENGTH1, arr_str2);
  std::cout << arr_str1 << std::endl;
  std::cout << std_str1 + std_str2 << std::endl;
  return 0;
}
