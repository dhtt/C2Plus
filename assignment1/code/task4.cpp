#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    string a; vector<string> va;
    while(getline(cin,a)){
        va.push_back(a);
    }
    for (int i=1; i<argc; ++i) {
        string b = argv[i];
        auto check_string = find(va.begin(), va.end(), b);
        if (check_string == va.end()) cout << "not found" << endl;
        else cout << check_string - va.begin() + 1 << endl;
    }
    return 0;
}
