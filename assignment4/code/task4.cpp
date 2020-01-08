#include "bloom_filter.hpp"

int main(int argc, const char* argv[]) {
  // you might test your bloom filter here
    int i = 50;
    uint32_t seed = 42;
    murmur3_32(reinterpret_cast<uint8_t*>(&i), sizeof(i), seed);
    return 0;
}
