#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
using namespace std;

void sort(std::vector<string>& v);
void sort(std::vector<string>& v){
    std::sort(v.begin(), v.end());
}
int log_time_search(vector<string> vs, int start, int end, const string& word);
int log_time_search(vector<string> vs, int start, int end, const string& word){
    if (start > end) return -1;

    int mid = start + ((end-start)/2);
    if (vs[mid] == word) {return mid;}
    else if (vs[mid] > word) {return(log_time_search(vs, start, mid-1 , word));}
    else {return(log_time_search(vs, mid + 1, end , word));}
}

int main(int argc, char* argv[]) {
    freopen("temp4.txt","r",stdin);
    string a; vector<string> vs;
    while(getline(cin,a)){
        vs.push_back(a);
    }
    sort(vs);
    for (int i=1; i<argc; ++i) {
        string b = argv[i];
        int pos = log_time_search(vs, 0, vs.size()-1, b);
        if (pos == -1) cout << "not found" << endl;
        else cout << pos+1 << endl;
    }
    return 0;
}
