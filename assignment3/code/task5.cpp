#include <iostream>
#include "graph.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    Graph<int> G(5);
    G.add_vertex(0);
    G.add_vertex(2);
    G.add_vertex(4);
    G.add_vertex(6);
    G.add_vertex(8);
    G.add_edge(0,1);
    G.add_edge(0,2);
    G.add_edge(0,3);
    G.add_edge(1,2);
    G.add_edge(2,4);

    auto p = G.dfs_begin(3);
    cout << "BEGIN: " << &p << "\t" << *p << endl;
    auto q = G.dfs_end(3);
    cout << "END: " << &q << "\t" << *q << endl;
    for (Graph<int>::dfs_iterator it = p; it !=  q; ++it){
        std::cout << *it <<"\t";
    }


    auto m = G.bfs_begin(3);
    cout << "BEGIN: " << &m << "\t" << *m << endl;
    auto n = G.bfs_end(3);
    cout << "END: " << &n << "\t" << *n << endl;
    for (Graph<int>::bfs_iterator it = m; it != n; ++it){
        std::cout << *it <<"\t";
    }
    return 0;
}
