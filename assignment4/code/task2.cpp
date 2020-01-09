#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class Invalid{};
static int min_switch(vector<bool> station, vector<bool> &beaming_cities, vector<size_t> &enabled_station, size_t radius, size_t& idx){
    if (radius < station.size()){
        if ((find(station.begin(), station.begin()+radius, true) == station.begin() + radius) || (find(station.end()-radius, station.end() + radius, true) == station.end())){
            return -1; //if first or last beaming station is > radius distance away from the beginning or end, return -1
        }

        if (find(enabled_station.begin(), enabled_station.end(), idx) != enabled_station.end()){// if the beaming station is already enabled (== there is not beaming station in range 2*k-1 from the current station)
            return -1;
        }
        else {// if the beaming station is currently disabled
            if (beaming_cities[beaming_cities.size() - 1]) return 0;    //end recursion when all cities are enabled
            else {//if (all cities are enabled == false)
                if (station[idx]){ //if there is a beaming station in current city
                    replace(beaming_cities.begin() + idx - radius, beaming_cities.begin() + idx + radius, false, true); //enable the beaming station by changing beaming status of all cities within radius to true
                    enabled_station.push_back(idx); //store the enabled beaming station
                    idx = idx + 2*radius - 1; //examine the next beaming station that is 2*k-1 unit away from current station to minimize overlapping
                }
                else { //if there is no beaming station in current city -> check preceding city
                    --idx;
                }
                return min_switch(station, beaming_cities, enabled_station, radius, idx);
            }
        }
    }
    else {
        if (find(station.begin(), station.end(), true) != station.end()) {
            size_t found_idx = distance(station.begin(), find(station.begin(), station.end(), true));
            enabled_station.push_back(found_idx);
            return enabled_station.size();
        }
        else return -1;
    }
}

int main(int argc, const char* argv[]) {
    vector<bool> beaming_stations; bool station;
    string line1; string line2;
    getline(cin, line1); getline(cin, line2);
    istringstream iss1(line1); istringstream iss2(line2);
    if (line1.empty() || line2.empty()){
        cerr << "First of second line is missing.\n";
        exit(1);
    }

    size_t a; vector<size_t> first_line;
    while (iss1 >> a){
        first_line.push_back(a);
    }
    if (first_line.size() != 2){
        cerr << "Please check the first line of your input.\n";
        exit(1);
    }
    size_t n = first_line[0];
    size_t k = first_line[1];
    cout << n << "\t" << k << endl;

    while (iss2 >> station){
        beaming_stations.push_back(station);
        cout << station << "\t";
    }
    cout <<endl;
    if (beaming_stations.size() != n){
        cerr << "Please check the second line of your input: " << beaming_stations.size() << endl;
        exit(1);
    }

    vector<size_t> result;
    vector<bool> beaming_cities(n, false);
    vector<size_t> enabled_station;
    size_t index; //start examining the first station at position k-1
    if (k - 1 < n) index = k - 1; else index = n - 1;
    if (min_switch(beaming_stations, beaming_cities, enabled_station, k, index) == -1) cout << -1;
    else cout << enabled_station.size();

    return 0;
}

