// Code notes on the C++ inroduction course from LinkedIn learning
// Created by Arkadii Semenov, 2022.12.09

#include <iostream>
#include <string>
#include <fstream>

std::ifstream inFile;
std::string str;
int number;
char letter;

/*
Reading files:
ifstream -> input stream / file for reading
  -> .open(string filename) -> opens the file for reading as a character stream
  -> .close() -> closes the file
  -> .eof() -> shows information if the file is over or not
  -> .fail() -> true if there is an error with file reading

getline(infile stream, &string) -> reads a line from the file,
    gets without \n in the end to the string.
*/

int main() {
  inFile.open("data.txt");
  if (inFile.fail()) {
    std::cout << std::endl << "File not found!" << std::endl;
  } else {
    while (!inFile.eof()) {
      getline(inFile, str);
      std::cout << str << std::endl;
    }
    inFile.close();
  }
  return 0;
}
