#include "cxxopts.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    cxxopts::Options options("MyProgram", "One line description of MyProgram");
    options.add_options()
            ("i", "Case insensitive")
            ("F", "Fixed string pattern", cxxopts::value<std::string>())
            ("w", "Whole word matching")
            ("f", "Read pattern from file name", cxxopts::value<std::string>())
            ("v", "Non matching line")
            ("n", "Output line number", cxxopts::value<std::string>());
    auto result = options.parse(argc, argv);
    result.count("i");
    return 0;
}
