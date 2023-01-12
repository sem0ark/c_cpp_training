// Code notes on the C++ inroduction course from LinkedIn learning
// Created by Arkadii Semenov, 2022.12.07

#include <iostream>
#include <string>
#include <vector>

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



// Vectors
// 1. Dynamic-size containers
// 2. The memory is managed for you
// 3. Generic container class -> can be used for any type of elements
// 4. There's a lot of useful functions, Part od STD

std::vector<int> primes;

int main() {
  primes.push_back(2); // append in python
  primes.push_back(3);
  primes.push_back(5);
  primes.push_back(7);
  primes.push_back(11);

  std::cout << "Length: " << primes.size() << std::endl;
  std::cout << "Primes[2]: " << primes[2] << std::endl;
  std::cout << "Primes[4]: " << primes[4] << std::endl;

  primes[2] = 13;
  std::cout << "Primes[2] changed: " << primes[2] << std::endl;

  std::vector<cow> cattle;

  cattle.push_back(cow("Betty", 6, meat));
  cattle.push_back(cow("Bettr", 5, meat));
  cattle.push_back(cow("Betto", 4, meat));
  cattle.push_back(cow("Libre", 3, meat));

  std::cout << "The first cow is " << cattle.begin()->get_name() << std::endl;
  std::cout << "The cow[1] is " << cattle[1].get_name() << std::endl;
  std::cout << "The next to last cow is " << std::prev(cattle.end(), 2)->get_name() << std::endl;
  std::cout << "The last cow is " << (cattle.end() - 1)->get_name() << std::endl;

  return 0;
}
