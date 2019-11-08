#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
using namespace std;

void sort(std::vector<double>& v);
double get_max(vector<double>& v);
double get_min(vector<double>& v);
double get_mean(vector<double>& v);
double get_median(vector<double>& v);
double get_first_quartile(vector<double>& v);
double get_third_quartile(vector<double>& v);
void get_result(vector<double> v, long type);

void sort(std::vector<double>& v) {
  std::sort(v.begin(), v.end());
}

double get_min(vector<double>& v) {
    return(v[0]);
}
double get_max(vector<double>& v) {
    return(v[v.size()-1]);
}
double get_mean(vector<double>& v) {
    return std::accumulate(v.begin(), v.end(), 0.0)/v.size();
}

double get_median(vector<double>& v){
    if (v.size()%2 == 1) return v[v.size()/2];
    else return (v[v.size()/2-1] + v[v.size()/2])/2;
}
double get_first_quartile(vector<double>& v) {
    vector<double> first_half(v.begin(), v.begin() + v.size() / 2);
    return get_median(first_half);
}

double get_third_quartile(vector<double>& v){
        if (v.size()%2 == 1) {
            vector<double> second_half(v.begin() + v.size()/2 + 1, v.end());
            return get_median(second_half);
        }
        else {
            vector<double> second_half(v.begin() + v.size()/2, v.end());
            return get_median(second_half);
        }
}

void get_result(vector<double> v, long type){
    sort(v);

    double quartile;
    if (type==1) quartile = get_first_quartile(v);
    else if (type==2) quartile = get_median(v);
    else quartile = get_third_quartile(v);

    cout << get_min(v) << " " << get_max(v) << " " << get_mean(v) << " " << quartile << endl;
}

int main(int argc, char* argv[]) {
    if (argc!=2){
        printf("Please give 1 argument.\n");
        return EXIT_FAILURE;
    }

    string line;
    vector<vector<double>> vvd; double d; double quartile;

    while (getline(cin,line)) {
        std::istringstream iss(line);
        vector<double> vd;
        while(iss >> d){
            vd.push_back(d);
        }
        vvd.push_back(vd);
    }
    long type = strtol(argv[2], nullptr, 10);


    for (auto & vd : vvd) {
        const vector<double>& row(vd);
        get_result(row, type);
    }

    return 0;
}
