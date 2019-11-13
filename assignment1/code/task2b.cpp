#include <iostream>
#include <vector>
unsigned int& get_max(unsigned int a, unsigned int b);
unsigned int& get_max(unsigned int a, unsigned int b) { //variables pass by reference
  unsigned int *c = a > b ? &a : &b; //dereference by *
  return *c; //return dereferenced value
}

int main() {
  std::vector<unsigned int> v(10000, 0);
  v[9999] = 1000u;

  auto max = 0u;
  for(auto e : v){
    max = get_max(max, e);
  }
  std::cout << "Maximum: " << max << std::endl;
  return 0;
}
