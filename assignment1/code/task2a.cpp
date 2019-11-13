#include <iostream>
#include <vector>

int main() {
  std::vector<int> v;
  v.reserve(50);

  for (auto i = 104; i < 154; ++i) {
    v.push_back(i);
  }

  for (auto i = v.size(); i > 0; --i) {
    std::cout << i-1 << ": " << v[i-1] << std::endl; //We want to print 50 values in the vector and their index (0-based)
  }
  return 0;
}
