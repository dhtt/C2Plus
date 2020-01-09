#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include "munkres_algorithm.hpp"

static void substract_minrow(Matrix<int>& mat){
    for (size_t r = 0; r < mat.nrows(); ++r){
        std::vector<int> row;
        for (size_t c = 0; c < mat.ncols(); ++c){
            row.push_back(mat(r, c));
        }

        int min_row = *std::min_element(row.begin(), row.end());
        for (size_t c = 0; c < mat.ncols(); ++c){
            mat(r,c) = mat(r,c) - min_row;
        }
    }
}
static void substract_mincol(Matrix<int>& mat){
    for (size_t c = 0; c < mat.ncols(); ++c){
        std::vector<int> col;
        for (size_t r = 0; r < mat.nrows(); ++r){
            col.push_back(mat(r, c));
        }

        int min_col = *std::min_element(col.begin(), col.end());
        for (size_t r = 0; r < mat.nrows(); ++r){
            mat(r,c) = mat(r,c) - min_col;
        }
    }
}

static void step_0(int& step, Matrix<int>& mat, Matrix<int>& mask, std::vector<bool>& row_cover, std::vector<bool>& col_cover){
    substract_minrow(mat); //1: For each row r in C, subtract its smallest element from every element in r
    substract_mincol(mat); //2: For each column c in C, subtract its smallest element from every element in c

    for (size_t r = 0; r < mat.nrows(); ++r){//3: For all zeros zi in C, mark zi with a star if there is no starred zero in its row or column
        for (size_t c = 0; c < mat.ncols(); ++c){
            if ((mat(r,c) == 0) && (row_cover[r] == 0) && (col_cover[c] == 0)){
                mask(r,c) = 1;
                row_cover[r] = true;
                col_cover[c] = true;
            }
        }
    }
    for (size_t r = 0; r < mat.nrows(); ++r) row_cover[r] = false; //uncover row
    for (size_t c = 0; c < mat.ncols(); ++c) col_cover[c] = false; //uncover col
    step = 1;
}
static void step_1(int& step, Matrix<int>& mask, std::vector<bool>& col_cover){ //4: STEP 1
    for (size_t r = 0; r < mask.nrows(); ++r){ //5: for Each column containing a starred zero do
        for (size_t c = 0; c < mask.ncols(); ++c){
            if (mask(r,c) == 1){
                col_cover[c] = true; //6: cover this column
            }
        }
    } //7: end for
    if (find(col_cover.begin(), col_cover.end(), false) == col_cover.end()) { //8: if n columns are covered then GOTO DONE else GOTO STEP 2
        step = 5; //GOTO DONE
    }
    else {
        step = 2; //GOTO STEP 2
    }
}

static int check_uncovered_zero(Matrix<int>& mat, Matrix<int>& mask, std::vector<bool>& row_cover, std::vector<bool>& col_cover){
    int prime_row = -1;
    for (size_t r = 0; r < mat.nrows(); ++r){
        for (size_t c = 0; c < mat.ncols(); ++c){
            if ((mat(r,c) == 0) && (row_cover[r] == 0) && (col_cover[c] == 0)){
                prime_row = r;
                mask(r,c) = 2;
                return prime_row;
            }
        }
    }
    return prime_row;
}
static int check_starred_zero_in_row(Matrix<int>& mat, Matrix<int>& mask, int prime_row){
    int starred_col = -1;
    for (size_t c = 0; c < mat.ncols(); ++c){
        if (mask(prime_row, c) == 1){
            starred_col = c;
        }
    }
    return starred_col;
}
static int step_2(int& step, Matrix<int>& mat, Matrix<int>& mask, std::vector<bool>& row_cover, std::vector<bool>& col_cover, int& e_min){ //9: STEP 2
    int prime_row = check_uncovered_zero(mat, mask, row_cover, col_cover);
    if (prime_row != -1){ //10: if C contains an uncovered zero then 11: Find an arbitrary uncovered zero Z0 and prime it
        int starred_col = check_starred_zero_in_row(mat, mask, prime_row);
        if (starred_col == -1) {// 12: if There is no starred zero in the row of Z0 then
            step = 3;
        }
        else { //14: else
            // 15: Cover this row, and uncover the column containing the starred zero GOTO STEP 2
            row_cover[prime_row] = true;
            col_cover[starred_col] = false;
            step = 2; //GOTO STEP 2
        }
    } //end if
    else { //17: else
        std::vector<int> e_vector;
        for (size_t r = 0; r < mat.nrows(); ++r){
            for (size_t c = 0; c < mat.ncols(); ++c){
                if (row_cover[r] == 0 && col_cover[c] == 0 ) {
                    int e = mat(r,c); //18: Save the smallest uncovered element emin GOTO STEP 4
                    e_vector.push_back(e);
                }
            }
        }
        e_min = *std::min_element(e_vector.begin(), e_vector.end());
        step = 4; //GOTO STEP 4
    }//19: end if
    return prime_row;
}

static int get_prime_col(Matrix<int> mask, int prime_row){
    int prime_col = -1;
    for (size_t c = 0; c < mask.ncols(); ++c){
        if (mask(prime_row, c) == 2) prime_col = c;
    }
    return prime_col;
}
static int get_prime_row(Matrix<int> mask, int prime_col){
    int prime_row = -1;
    for (size_t r = 0; r < mask.nrows(); ++r){
        if (mask(r, prime_col) == 2) {
            prime_row = r;
            break;
        }
    }
    return prime_row;
}
static int get_starred_row(Matrix<int> mask, int prime_col){
    int starred_row = -1;
    for (size_t r = 0; r < mask.ncols(); ++r){
        if (mask(r, prime_col) == 1) starred_row = r;
    }
    return starred_row;
}
static int get_starred_col(Matrix<int> mask, int star_row){
    int starred_col = -1;
    for (size_t c = 0; c < mask.ncols(); ++c){
        if (mask(star_row, c) == 1) starred_col = c;
    }
    return starred_col;
}
static bool check_starred_zero_in_col(Matrix<int>& mask, int prime_col){
    bool result = false;
    for (size_t r = 0; r < mask.nrows(); ++r){
        if (mask(r, prime_col) == 1){
            result = true;
            break;
        }
    }
    return result;
}
static void step_3(int& step, Matrix<int>& mat, Matrix<int>& mask, std::vector<bool>& row_cover, std::vector<bool>& col_cover, int& prime_row){ //20: STEP 3
    std::vector<int> S;
    S.push_back(prime_row); //21: Insert Z0 into S

    while (check_starred_zero_in_col(mask, get_prime_col(mask, prime_row))){ //22: while In the column of Z0 exists a starred zero Z1 do
        int star_row = get_starred_row(mask, get_prime_col(mask, prime_row));
        S.push_back(star_row); //23: Insert Z1 into S

        int prime_col = get_prime_col(mask, star_row);
        prime_row = get_prime_row(mask, prime_col); //24: Replace Z0 with the primed zero in the row of Z1. Insert Z0 into S
        S.push_back(prime_row);
    } //25: end while

    for (size_t i = 1; i < S.size(); i+=2){ //26: Unstar each starred zero in S
        mask(S[i], get_starred_col(mask, S[i])) = 0;
    }
    for (size_t i = 0; i < S.size(); i+=2){
        mask(S[i], get_prime_col(mask, S[i])) = 1; //26: Replace all primes with stars.
    }
    for (size_t r = 0; r < mask.nrows(); ++r){ //26: Erase all other primes
        for (size_t c = 0; c < mask.ncols(); ++c){
            if (mask(r,c) == 2) mask(r,c) = 0;
        }
    }
    for (size_t r = 0; r < mat.nrows(); ++r) row_cover[r] = false; //26: uncover every line in C
    for (size_t c = 0; c < mat.ncols(); ++c) col_cover[c] = false; //26: uncover every line in C
    step = 1; //26: GOTO STEP 1
}

static void step_4(int& step, Matrix<int>& mat, std::vector<bool>& row_cover, std::vector<bool>& col_cover, int e_min){
    for (size_t i = 0; i < row_cover.size(); ++i){//27: Add emin to every element in covered rows
        if (row_cover[i]){
            for (size_t j = 0; j < mat.ncols(); ++j){
                mat(i,j) += e_min;
            }
        }
    }
    for (size_t j = 0; j < col_cover.size(); ++j){ //27: subtract emin from every element in uncovered columns
        if (!col_cover[j]){
            for (size_t i = 0; i < mat.nrows(); ++i){
                mat(i,j) -= e_min;
            }
        }
    }
    step = 2; //GO TO STEP 2
}

Matrix<int> run_munkres_algorithm(Matrix<int> m) {
    if (m.nrows() != m.ncols()){
        std::cerr << "Matrix has to be square." << std::endl;
        exit(1);
    }
    
    Matrix<int> mat(m);
    Matrix<int> mask(mat.nrows(), mat.ncols(), 0); //mask stores star and prime zero
    std::vector<bool> row_cover(mat.nrows(), false); //row_cover stores which row is covered
    std::vector<bool> col_cover(mat.ncols(), false); //col_cover stores which col is covered

    int step = 0; //start from step 0:
    int prime_row = 0;
    int e_min = 0;
    bool done = false;
    while (!done){
        switch(step)
        {
            case 0:
                step_0(step, mat, mask, row_cover, col_cover);
                break;
            case 1:
                step_1(step, mask, col_cover);
                break;
            case 2:
                prime_row = step_2(step, mat, mask, row_cover, col_cover, e_min);
                break;
            case 3:
                step_3(step, mat, mask, row_cover, col_cover, prime_row);
                break;
            case 4:
                step_4(step, mat, row_cover, col_cover, e_min);
                break;
            case 5:
                done = true;
                break;
        }
    }
    return mask;
}
