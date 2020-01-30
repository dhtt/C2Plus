#include <iostream>

#include "munkres_algorithm.hpp"
#include "matrix.hpp"


int main(int /*argc*/, const char* /*argv*/[]) {
    const Matrix<int> m = {{250, 400, 350}, {400, 600, 350}, {200, 400, 250}};
    const Matrix<int> s = {{0, 1, 0}, {0, 0, 1}, {1, 0, 0}};

    const auto res = run_munkres_algorithm(m);

    if(s.nrows() != res.nrows() || s.ncols() != res.ncols()) {
        std::cerr << "Cannot compare matrices" << std::endl;
        return 1;
    }

    for(size_t i = 0; i < s.nrows(); i++) {
        for(size_t j = 0; j < s.ncols(); j++) {
            if(s(i,j) != res(i,j)){
                std::cerr << "Found invalid result" << std::endl;
                return 1;
            }
        }
    }

//SELF-TEST
//    const Matrix<int> m1 = {{80, 40, 50, 46}, {40, 70, 20, 25}, {30, 10, 20, 30}, {35, 20, 25, 30}};
//    const Matrix<int> m2 = {{1, 1, 0, 1}, {0, 1, 1, 0}, {1, 1, 0, 0}, {1, 1, 1, 0}};
//    const Matrix<int> m3 = {{38,53,61,36,66}, {100,60,9,79,34}, {30,37,36,72,34}, {61,95,21,14,64}, {89,90,4,5,79}};
//    const Matrix<int> m4 = {{1, 2, 3,4}, {2,4,6,8}, {3,6,9,12}, {4,8,12,16}};
//    const Matrix<int> m1 = {{1, 2, 3}, {2, 4, 6}, {3, 6, 9}};
//    const auto res1 = run_munkres_algorithm(m1);
//    const auto res2 = run_munkres_algorithm(m2);
//    const auto res3 = run_munkres_algorithm(m3);
//    const auto res4 = run_munkres_algorithm(m4);
    return 0;
}
