#include <algorithm>
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
using namespace std;
static bool is_complementary(char a, char b){
    return (a == 'A' && b == 'U') || (a == 'U' && b == 'A') || (a == 'C' && b == 'G') || (a == 'G' && b == 'C') || (a == 'G' && b == 'U') || (a == 'U' && b == 'G');
}

class DP_array{
private:
    string RNA;
public:
    size_t nrows{};
    size_t ncols{};
    int * array{};

    DP_array();
    explicit DP_array(string seq);

    int& at(size_t i, size_t j){//get element at i,j
        return array[i*nrows + j];
    }
};

DP_array::DP_array() = default;

DP_array::DP_array(string seq) {
    RNA = std::move(seq);
    nrows = RNA.size() + 1;
    ncols = RNA.size() + 1;
    array = new int[nrows * ncols];

    for (size_t i = 0; i < nrows; ++i){
        for (size_t j = 0; j < ncols; ++j){
            array[i*nrows + j] = 0;
        }
    }
} //Dynamic array initialized by 0

struct Pair{
    Pair(size_t i, size_t j): base1(i), base2(j) {}
    size_t base1;
    size_t base2;
}; //Pair of position for backtracking

static int score(int i, int j, string s, const DP_array& dp, int l){ //score function
    int score1 = 0; int score2 = 0; //score1 = Sj is unpaired; score2 = Sj is paired with Sk
    if (j - i < l) return 0; //end if loop length < minimal_loop length
    else {
        score1 = score(i, j-1, s, dp, l);
        for (int k = i; k < j-l; ++k){
            if (is_complementary(s[static_cast<unsigned long>(k - 1)], s[static_cast<unsigned long>(j - 1)])){ //s[k-1] and s[j-1] instead of s[k] and s[j] because the index in string and in array are different
                int score_temp = score(i, k-1, s, dp, l) + score(k+1, j-1, s, dp, l) + 1;
                if (score_temp > score2) score2 = score_temp;//get max score2
            }
        }
        return max(score1, score2); //get final score
    }
}

static DP_array DPscoring(const string& s, int l)
{
    DP_array dp(s);
    // Scoring
    for (size_t i = 1; i < dp.nrows; ++i){
        for (size_t j = 1; j < dp.ncols; ++j){
            dp.at(i,j) = score(i, j , s, dp, l);
        }
    }
    return dp;
}

static void traceback(size_t i, size_t j, vector<Pair>& structure, const string &seq, DP_array& dp){
    //Traceback following the method described in RNASecondaryStructure,byDanielHuson,ClemensGro ̈pl,January11,2012,10:08
    int d = 0;
    if (i<j){
        if (is_complementary(seq[i-1], seq[j-1])) d = 1;
        if (dp.at(i,j) == dp.at(i+1,j)) {
            traceback(i+1, j, structure, seq, dp);
            }
        else if (dp.at(i,j) == dp.at(i,j-1)) {
            traceback(i, j-1, structure, seq, dp);
        }
        else if (dp.at(i,j) == dp.at(i+1,j-1) + d) {
            Pair pair(i, j); structure.push_back(pair);
            traceback(i, j-1, structure, seq, dp);
        }
        else for (size_t k = i+1; k < j-1; ++k){
            if (dp.at(i,j) == dp.at(i,k) + dp.at(k+1, j)) {
                traceback(i, k, structure, seq, dp);
                traceback(k+1, j, structure, seq, dp);
            }
        }
    }
}

static string write_structure(const vector<Pair>& structure, const string& seq){
    string result(seq.size(), '.');
    for (auto item:structure){
        result[item.base1-1] = '(';
        result[item.base2-1] = ')';
    }
    return result;
}

int main(int argc, const char* argv[])
{
    if (argc!=2){
        printf("Please give 1 argument.\n");
        return EXIT_FAILURE;
    }

    string seq = argv[1];
    int min_loop_length = 2;
    DP_array score_array = DPscoring(seq, min_loop_length);
    cout << score_array.at(1, seq.size()) << endl;
    vector<Pair> trace_temp;
    traceback(1, seq.size(), trace_temp, seq, score_array);
    cout << write_structure(trace_temp, seq) << endl;
    return 0;
}
