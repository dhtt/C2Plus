#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <numeric>

using namespace std;
static void print_cliques(vector<size_t> V){
    sort(V.begin(), V.end());
    string sep = "";
    cout << "{";
    for (auto i:V) {
        cout << sep << i;
        sep = ", ";
    }
    cout << "}" << endl;
}

static vector<size_t> get_intersection(vector<size_t> V1, vector<size_t> V2){
    sort(V1.begin(), V1.end());
    sort(V2.begin(), V2.end());
    vector<size_t> intersection;
    set_intersection(V1.begin(), V1.end(), V2.begin(), V2.end(), back_inserter(intersection));
    return intersection;
}
static vector<size_t> get_union(vector<size_t> V1, vector<size_t> V2){
    sort(V1.begin(), V1.end());
    sort(V2.begin(), V2.end());
    vector<size_t> union_set;
    std::set_union (V1.begin(), V1.end(), V2.begin(), V2.end(), back_inserter(union_set));
    return union_set;
}
static vector<size_t> get_exclusion(const vector<size_t>& V1, vector<size_t> V2){
    vector<size_t> exclusion_set;
    for (auto i:V1){
        if (find(V2.begin(), V2.end(), i) == V2.end()){
            exclusion_set.push_back(i);
        }
    }
    return exclusion_set;
}
static vector<vector<size_t>> get_adjacency_list(vector<vector<bool>> adj_matrix){
    vector<vector<size_t>> all_neighbors;
    for (size_t i = 0; i < adj_matrix.size(); ++i){
        vector<size_t> neighbors;
        for (size_t j = 0; j < adj_matrix.size(); ++j){
            if (adj_matrix[i][j]){
                neighbors.push_back(j);
            }
        }
        all_neighbors.push_back(neighbors);
    }
    return all_neighbors;
}
static vector<size_t> get_neighbors(vector<vector<size_t>> adjacency_list, size_t idx){
    return adjacency_list[idx];
}

static void find_maximal_clique3(const vector<size_t>& R, vector<size_t> P, vector<size_t> X, const vector<vector<size_t>>& adjacency_list){
    if (P.empty() && X.empty()) print_cliques(R);
    else {
        //Choose a u and get its non-neigbors
        vector<size_t> PX_union = get_union(P,X);
        size_t u = PX_union[0];
        vector<size_t> Nu = get_neighbors(adjacency_list, u);
        vector<size_t> P_Nu = get_exclusion(P, Nu);

        //Loop through non-neighbor of u
        for (auto v:P_Nu){
            vector<size_t> R_v(R); R_v.push_back(v);
            vector<size_t> Nv = get_neighbors(adjacency_list, v);
            vector<size_t> PNv = get_intersection(P, Nv);
            vector<size_t> XNv = get_intersection(X, Nv);

            find_maximal_clique3(R_v, PNv, XNv, adjacency_list);

            P.erase(remove(P.begin(), P.end(), v), P.end());
            X.push_back(v);
        }
    }
}


int main(int argc, const char* argv[]) {
    string line; vector<vector<bool>> adj_matrix;
    //std::ifstream infile("sample.txt");
    while (getline(cin, line)){
        istringstream iss(line); bool has_edge; vector<bool> edge;
        while (iss >> has_edge){
            edge.push_back(has_edge);
        }
        adj_matrix.push_back(edge);
    }
    vector<vector<size_t>> adjacency_list = get_adjacency_list(adj_matrix);
    vector<size_t> R; vector<size_t> X; vector<size_t> P(adj_matrix.size());
    iota(P.begin(), P.end(), 0);
    find_maximal_clique3(R, P, X, adjacency_list);
    return 0;
}
