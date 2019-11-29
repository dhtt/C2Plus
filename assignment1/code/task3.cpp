#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
using namespace std;

//functions prototypes
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

double get_min(vector<double>& v) {//vector must be sorted first
    return(v[0]);
}
double get_max(vector<double>& v) {//vector must be sorted first
    return(v[v.size()-1]);
}
double get_mean(vector<double>& v) {
    return std::accumulate(v.begin(), v.end(), 0.0)/v.size();
}

double get_median(vector<double>& v){//vector must be sorted first
    if (v.size()%2 == 1) return v[v.size()/2]; //odd number of elements in vector: take middle value
    else return (v[v.size()/2-1] + v[v.size()/2])/2; //even number of elements in vector: take average of 2 middle values
}
double get_first_quartile(vector<double>& v) {//vector must be sorted first
    vector<double> first_half(v.begin(), v.begin() + v.size() / 2); //take first half of vector
    return get_median(first_half); 
}

double get_third_quartile(vector<double>& v){//vector must be sorted first
        if (v.size()%2 == 1) { //odd number of elements in vector:
            vector<double> second_half(v.begin() + v.size()/2 + 1, v.end()); //take second half of vector with middle value
            return get_median(second_half);
        }
        else { //even number of elements in vector:
            vector<double> second_half(v.begin() + v.size()/2, v.end()); //take second half of vector without middle value
            return get_median(second_half);
        }
}

void get_result(vector<double> v, long type){ //convenient results report
    sort(v);

    double quartile;
    if (type==1) quartile = get_first_quartile(v);
    else if (type==2) quartile = get_median(v);
    else quartile = get_third_quartile(v);

    cout << get_min(v) << " " << get_max(v) << " " << get_mean(v) << " " << quartile << endl;
}

int main(int argc, char* argv[]) {
    if (argc!=2){ //give error when no quartile argument
        printf("Please give 1 argument.\n");
        return EXIT_FAILURE;
    }

    string line;
    vector<vector<double>> vvd; double d; double quartile;

    while (getline(cin,line)) { //for each line, store doubles in vector vd, then store vd in vector vvd
        std::istringstream iss(line);
        vector<double> vd;
        while(iss >> d){
            vd.push_back(d);
        }
        vvd.push_back(vd);
    }
    
    long type = strtol(argv[1], nullptr, 10); //read argument 1 for quartile

    for (auto & vd : vvd) { //report result for each vector in vvd
        const vector<double>& row(vd);
        get_result(row, type);
    }

    return 0;
}
