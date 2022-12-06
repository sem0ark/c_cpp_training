#include <iostream>
#include <string>

int main() {
  // creation of string type variable
  std::string str;

  std::cout << "Please, enter your name: ";

  // request input from user
  // used for *single words*
  std::cin  >> str;
  // output str variable to the console
  std::cout << "Your name is: " << str << std::endl;

  return 0;
}
