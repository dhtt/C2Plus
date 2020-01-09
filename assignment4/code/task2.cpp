#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class Invalid{};
static int min_switch(vector<bool> station, vector<bool> &beaming_cities, vector<size_t> &enabled_station, size_t radius, size_t& idx){
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

int main(int argc, const char* argv[]) {
    size_t n; size_t k;
    vector<bool> beaming_stations; bool station;
    string line1; string line2;
    getline(cin, line1); getline(cin, line2);
    istringstream iss1(line1); istringstream iss2(line2);
    iss1 >> n >> k;
    while (iss2 >> station){
        beaming_stations.push_back(station);
    }
    if (beaming_stations.size() != n){
        cerr << "Please give n cities.\n";
        throw Invalid{};
    }
//    cin >> n >> k;
//    for (size_t i = 0; i < n; ++i){
//        cin >> station;
//        beaming_stations.push_back(station);
//    }
    vector<size_t> result;
    vector<bool> beaming_cities(n, false);
    vector<size_t> enabled_station;
    size_t index = k - 1; //start examining the first station at position k-1
    if (min_switch(beaming_stations, beaming_cities, enabled_station, k, index) == -1) cout << -1;
    else cout << enabled_station.size();

    return 0;
}
