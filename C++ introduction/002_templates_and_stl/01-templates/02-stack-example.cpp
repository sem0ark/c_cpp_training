// Code notes on the C++ Templates and STL course from LinkedIn learning
// Created by Arkadii Semenov, 2023.01.12

#ifndef _STACK
#define _STACK

#include <exception>

// smiple expection class
class StackExpection : public std::exception {
  const char * msg;
  StackExpection(){}; // No default constructor
public:
  explicit StackExpection(const char * s) throw() : msg(s) { }
  const char * what() const throw() { return msg; }
};

// Simple fixed-size LIFO stack template
template<typename T>
class Stack {
private:
  static const int defaultSize = 10;
  static const int maxSize = 1000;
  int _size;
  int _top;
  T * stackPtr;
public:
  explicit Stack(int s = defaultSize);
  ~Stack() { delete[] stackPtr; }
  T & push(const T & );
  T & pop();
  bool isEmpty() const { return _top < 0; }
  bool isFull() const { return _top >= _size-1; }
  bool top() const { return _top; }
  bool size() const { return _size; }
};

#endif // _STACK



