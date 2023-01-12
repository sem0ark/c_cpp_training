// Code notes on the C++ inroduction course from LinkedIn learning
// Created by Arkadii Semenov, 2022.12.08

#include <iostream>

// If statement

// if (condition) { CODE }
// else if (condition_2) { CODE }
// ...
// else { CODE }

void calculate() {
  int op_1, op_2, res;
  char op;

  std::cout << "Enter operand 1: " << std::endl;
  std::cin >> op_1;
  std::cout << "Enter operand 2: " << std::endl;
  std::cin >> op_2;
  std::cout << "Choose operation (+ - * /): " << std::endl;
  std::cin >> op;

  switch (op) {
    case '+':
      res = op_1 + op_2;
      break;
    case '-':
      res = op_1 - op_2;
      break;
    case '*':
      res = op_1 * op_2;
      break;
    case '/':
      res = op_1 / op_2;
      break;
    default:
      std::cout << "Bad operation." << std::endl;
      break;
  }
  
  std::cout << "Result: " << res << std::endl;
}


int a = 1023;
char l = 'd';

int main() {
  if (a > 1000) {
    std::cout << "a is over 1000" << std::endl;
  } else {
    std::cout << "a is not over 1000" << std::endl;
  }

  if (a % 2 == 0) std::cout << "a % 2 == 0" << std::endl;

  std::cout << "The letter " << l << " is ";
  if (l!='a' && l!='e' && l!='i' && l!='o' && l!='u' && 
      l!='A' && l!='E' && l!='I' && l!='O' && l!='U') {
    std::cout << "not ";
  }
  std::cout << "a vowel" << std::endl;

  // Calculator function

  calculate();

  return 0;
}
