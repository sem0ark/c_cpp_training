// Code notes on the C++ inroduction course from LinkedIn learning
// Created by Arkadii Semenov, 2022.12.07

#include <iostream>

enum cow_purpose {dairy, meat, hide, pet};

class cow{
public:
  cow(std::string name_i, int age_i, unsigned char purpose_i){
    name = name_i;
    age = age_i;
    purpose = purpose_i;
  }
  std::string get_name(){
    return name;
  }
  int get_age(){
    return age;
  }
  unsigned char get_purpose(){
    return purpose;
  }
  void set_age(int new_age){
    age = new_age;
  }
  void set_name(std::string new_name){
    name = new_name;
  }
  void set_age(unsigned char new_purpose){
    purpose = new_purpose;
  }
private:
  std::string name;
  int age;
  unsigned char purpose;
};

// Pointers -> addresses for specified data
// 1. Can be void or NULL
// 2. Can point to different objects

// if 
// int a = 37; value 37 on address ex: 104
// int *prt = &a; -> pointer to the address of "a" variable
//      value 104 at ex: 120

int a = 37;
int *ptr;

cow *my_cow;

// References -> aliases to existing variables
// 1. References are not objects
// 2. References are not pointers
// 3. Referenced don't have an address
//      1. there're no arrays of references
//      2. there're np pointers to references
//      3. there're no references to references
// 4. Must be initialized on the declaration
// 5. Point to only one specific objects
// 6. It is not needed to dereference the reference

// HOW TO USE
// 1. Pass params by reference, so you can change parametres and copy big objects
// 2. Avoiding copying large objects in for loops

int my_int = 10;
int& my_ref = my_int;

int main() {
  ptr = &a;
  
  std::cout << " value -> a = " << a << std::endl;
  std::cout << " value -> ptr = " << ptr << std::endl;
  std::cout << "address -> &a = " << &a << std::endl;
  std::cout << " value -> *ptr = " << *ptr << std::endl;
  std::cout << "address -> &ptr = " << &ptr << std::endl;

  
  my_cow = new cow("Gertie", 3, hide);

  // -> - member of a pointer
  // it is a short-hand for

  std::cout << "Cow name:    " << my_cow->get_name() << std::endl;
  std::cout << "Cow age:     " << my_cow->get_age() << std::endl;
  std::cout << "Cow purpose: " << (int) my_cow->get_purpose() << std::endl;

  delete my_cow;

  return 0;
}
