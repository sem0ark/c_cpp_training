// Code notes on the C++ inroduction course from LinkedIn learning
// Created by Arkadii Semenov, 2022.12.09

#include <iostream>
#include <fstream>

/*
Reading files:
ofstream -> output stream / file for writing
  -> .open(string filename) -> opens the file for writing as a character stream
  -> .close() -> closes the file
  -> .fail() -> true if there is an error with file writing

writing to the file work as with std::cout ->

filestream << message
*/

std::ofstream outFile;

float a = 4.333f, b = 5.302f;

int main() {
  outFile.open("data.txt");
  if (outFile.fail()) {
    std::cout << std::endl << "Could not open the file!" << std::endl;
  } else {
    outFile << "a = " << a << std::endl;
    outFile << "b = " << b << std::endl;
    outFile << "a + b = " << a + b<< std::endl;
    outFile << "a * b = " << a * b << std::endl;
    outFile.close();
    std::cout << "File was written successfully!" << std::endl;
  }
  return 0;
}


