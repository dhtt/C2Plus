#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>
#include <stack>
#include <queue>

static void check_dup_ind(size_t v_idx1, size_t v_idx2){ //throw error when 2 given indexes are the same
    if (v_idx1 == v_idx2) throw std::invalid_argument("Please choose two different indexes");
}

// an unweighted directed Graph whose vertex properties (e.g. int, Color,
// std::pair<int, Color>, etc.) can be passed as template parameter
// for simplicity vertices can only be added, but not removed
template <typename VertexProp>
class Graph {
public:
    // builds an empty graph
    Graph() = default;

    // builds a graph with num_vertices unconnected vertices
    explicit Graph(std::size_t num_vertices);

    // adds a vertex and returns its index
    std::size_t add_vertex(VertexProp&& prop);

    // creates and edge between two vertices and returns if the creation was
    // successful (e.g. the edge could already exist)
    bool add_edge(const std::size_t v_idx1, const std::size_t v_idx2);

    // removes an edge between two vertices and returns if the removal was
    // successful
    bool remove_edge(const std::size_t v_idx1, const std::size_t v_idx2);

    // returns the neighbors of a vertex
    const std::list<std::size_t>& get_neighbors(const std::size_t v_idx) const;

    // reserves space for size number of vertices
    void reserve(const std::size_t size);

    // returns if there is an edge between v_idx1 and v_idx2
    bool has_edge(const std::size_t v_idx1, const std::size_t v_idx2) const;

    // returns the properties for a given vertex index
    VertexProp& get_vertex(const std::size_t v_idx);
    const VertexProp& get_vertex(const std::size_t v_idx) const;

    // returns the number of vertices
    std::size_t num_vertices() const;

    // returns the number of edges
    std::size_t num_edges() const;

    // returns the capacity
    std::size_t capacity() const;

    // ===================================================Iterator======================================================
    // ===================DFS iterator====================
    class dfs_iterator{
    public:
        VertexProp* it_;
        dfs_iterator(): it_(nullptr) {}
        explicit dfs_iterator(VertexProp* it): it_(it) {}
        explicit dfs_iterator(typename std::vector<VertexProp>::iterator it): it_(&*it) {}
        VertexProp& operator*(){
            return *it_;
        }
        dfs_iterator& operator++() {
            dfs_iterator i = *this;
            ++it_;
            return *this;
        }
        bool operator==(dfs_iterator& other){
            return (it_ == other.it_);
        }
        bool operator!=(dfs_iterator& other){
            return (it_ != other.it_);
        }
    };

    // Find DFS path and store the path in dsf_path
    void dfs(std::vector<bool>& visited, size_t v_idx, std::vector<VertexProp>& path);
    std::vector<VertexProp> find_dfs_path(size_t v_idx);

    // Iterator begin and end
    dfs_iterator dfs_begin(size_t i);
    dfs_iterator dfs_end(size_t i);

    // ===================BFS iterator====================
    // BFS iterator
    class bfs_iterator{
    public:
        VertexProp* it_;
        bfs_iterator(): it_(nullptr) {}
        explicit bfs_iterator(VertexProp* it): it_(it) {}
        explicit bfs_iterator(typename std::vector<VertexProp>::iterator it): it_(&*it) {}
        VertexProp& operator*(){
            return *it_;
        }
        bfs_iterator& operator++() {
            bfs_iterator i = *this;
            ++it_;
            return *this;
        }
        bool operator==(bfs_iterator& other){
            return (it_ == other.it_);
        }
        bool operator!=(bfs_iterator& other){
            return (it_ != other.it_);
        }
    };

    // Find BFS path and store the path in bsf_path
    void bfs(std::vector<bool>& visited, size_t v_idx, std::vector<VertexProp>& path);
    std::vector<VertexProp> find_bfs_path(size_t v_idx);

    // Iterator begin and end
    bfs_iterator bfs_begin(size_t i);
    bfs_iterator bfs_end(size_t i);

private:
    // stores the neighbors of each vertex
    std::vector<std::list<std::size_t>> adj_list_;
    // stores the vertex properties
    std::vector<VertexProp> vertex_props_;
};

template<typename VertexProp>
Graph<VertexProp>::Graph(std::size_t num_vertices) {
    reserve(num_vertices);
}

template<typename VertexProp>
std::size_t Graph<VertexProp>::add_vertex(VertexProp &&prop) {
    if (find(vertex_props_.begin(), vertex_props_.end(), prop) != vertex_props_.end()) throw std::invalid_argument("This vertex is already added.");

    vertex_props_.push_back(prop);
    adj_list_.resize(vertex_props_.size());
    return vertex_props_.size()-1;
}

template<typename VertexProp>
bool Graph<VertexProp>::add_edge(const std::size_t v_idx1, const std::size_t v_idx2) {
    try {
        adj_list_.at(v_idx1);
        adj_list_.at(v_idx2);
    }
    catch (const std::out_of_range &e){
        std::cerr << "Vertex index is out of range: " << e.what() <<std::endl;
        return false;
    }
    try {check_dup_ind(v_idx1, v_idx2);}
    catch (std::invalid_argument &e) {
        std::cerr << "Vertex cannot have edge to itself: " << e.what() <<std::endl;
        return false;
    }

    if (!has_edge(v_idx1, v_idx2)){ //add edge if there is no edge
        adj_list_[v_idx1].push_back(v_idx2); //directed graph: unidirectional edge only
        return true;
    }
    else {
        std::cout << "An edge already exists.";
        return false;
    }
}

template<typename VertexProp>
bool Graph<VertexProp>::remove_edge(std::size_t v_idx1, std::size_t v_idx2) {
    try {
        adj_list_.at(v_idx1);
        adj_list_.at(v_idx2);
    }
    catch (const std::out_of_range &e){
        std::cerr << "Vertex index is out of range: " << e.what() <<std::endl;
        return false;
    }
    try {check_dup_ind(v_idx1, v_idx2);}
    catch (std::invalid_argument &e) {
        std::cerr << "Vertex cannot have edge to itself: " << e.what() <<std::endl;
        return false;
    }

    if (has_edge(v_idx1, v_idx2)) { //remove edge if there is an edge
        adj_list_[v_idx1].remove(v_idx2); //directed graph: unidirectional edge
        return true;
    }
    else {
        std::cout << "This edge does not exist.";
        return false;
    }
}

template<typename VertexProp>
const std::list<std::size_t> &Graph<VertexProp>::get_neighbors(const std::size_t v_idx) const {
    if (v_idx >= adj_list_.size()) throw std::out_of_range("Vertex index is out of range");
    return adj_list_[v_idx];
}

template<typename VertexProp>
void Graph<VertexProp>::reserve(const std::size_t size) {
    adj_list_.reserve(size);
    vertex_props_.reserve(size);
}

template<typename VertexProp>
bool Graph<VertexProp>::has_edge(const std::size_t v_idx1, const std::size_t v_idx2) const {
    try {
        adj_list_.at(v_idx1);
        adj_list_.at(v_idx2);
    }
    catch (const std::out_of_range &e){
        std::cerr << "Vertex index is out of range: " << e.what() <<std::endl;
        return false;
    }
    try {check_dup_ind(v_idx1, v_idx2);}
    catch (std::invalid_argument &e) {
        std::cerr << "Vertex cannot have edge to itself: " << e.what() <<std::endl;
        return false;
    }

    return find(adj_list_[v_idx1].begin(), adj_list_[v_idx1].end(), v_idx2) != adj_list_[v_idx1].end();
}

template<typename VertexProp>
VertexProp &Graph<VertexProp>::get_vertex(const std::size_t v_idx) {
    if (v_idx >= vertex_props_.size()) throw std::out_of_range("Vertex index is out of range");
    return vertex_props_[v_idx];
}

template<typename VertexProp>
const VertexProp &Graph<VertexProp>::get_vertex(const std::size_t v_idx) const {
    if (v_idx >= vertex_props_.size()) throw std::out_of_range("Vertex index is out of range");
    return vertex_props_[v_idx];
}

template<typename VertexProp>
std::size_t Graph<VertexProp>::num_vertices() const {
    return adj_list_.size();
}

template<typename VertexProp>
std::size_t Graph<VertexProp>::num_edges() const {
    size_t n_edges = 0;
    for (auto vertex:adj_list_){
        n_edges += vertex.size();
    }
    return n_edges;
}

template<typename VertexProp>
std::size_t Graph<VertexProp>::capacity() const {
    return 0;
}

template<typename VertexProp>
void Graph<VertexProp>::dfs(std::vector<bool> &visited, size_t v_idx, std::vector<VertexProp> &path) {
    std::stack<size_t> v_stack;
    v_stack.push(v_idx); //push current vertex into stack
    while (!v_stack.empty()) { //while there are still vertex to be examined
        v_idx = v_stack.top(); //get the last added vertex out of stack
        v_stack.pop();
        if (!visited[v_idx]) { //if this vertex is not visited then mark visit and include it in DFS_path
            visited[v_idx] = true;
            if (find(path.begin(), path.end(), vertex_props_[v_idx]) == path.end()) path.push_back(vertex_props_[v_idx]);
        }
        for (auto i = adj_list_[v_idx].begin(); i != adj_list_[v_idx].end(); ++i){ //push all neighbor of this vertex into stack
            if (!visited[*i]) v_stack.push(*i);
        }
    }
}

template<typename VertexProp>
std::vector<VertexProp> Graph<VertexProp>::find_dfs_path(size_t v_idx) {
    std::vector<bool> visited(num_vertices(), false); // at first all vertexes are not visited
    std::vector<VertexProp> dfs_path;
    for (size_t i = v_idx; i < num_vertices(); i++){ // traverse through all nodes
        if (!visited[i]) dfs(visited, i, dfs_path);
    }
    return dfs_path;
}

template<typename VertexProp>
typename Graph<VertexProp>::dfs_iterator Graph<VertexProp>::dfs_begin(size_t i) {
    std::vector<VertexProp> dfs_path = find_dfs_path(i);
    return dfs_iterator(dfs_path.begin());
}

template<typename VertexProp>
typename Graph<VertexProp>::dfs_iterator Graph<VertexProp>::dfs_end(size_t i) {
    std::vector<VertexProp> dfs_path = find_dfs_path(i);
    return dfs_iterator(dfs_path.end());
}


template<typename VertexProp>
void Graph<VertexProp>::bfs(std::vector<bool> &visited, size_t v_idx, std::vector<VertexProp> &path) {
    std::queue<size_t> v_queue;
    v_queue.push(v_idx); //push current vertex into queue
    while (!v_queue.empty()) { //while there are still vertex to be examined
        v_idx = v_queue.front(); //get the first added vertex out of queue
        v_queue.pop();
        if (!visited[v_idx]) { //if this vertex is not visited then mark visit and include it in BFS_path
            visited[v_idx] = true;
            if (find(path.begin(), path.end(), vertex_props_[v_idx]) == path.end()) path.push_back(vertex_props_[v_idx]);
        }
        for (auto i = adj_list_[v_idx].begin(); i != adj_list_[v_idx].end(); ++i){ //push all neighbor of this vertex into queue
            if (!visited[*i]) v_queue.push(*i);
        }
    }
}

template<typename VertexProp>
std::vector<VertexProp> Graph<VertexProp>::find_bfs_path(size_t v_idx) {
    std::vector<bool> visited(num_vertices(), false); // at first all vertexes are not visited
    std::vector<VertexProp> bfs_path;
    for (size_t i = v_idx; i < num_vertices(); i++){ // traverse through all nodes
        if (!visited[i]) bfs(visited, i, bfs_path);
    }
    return bfs_path;
}

template<typename VertexProp>
typename Graph<VertexProp>::bfs_iterator Graph<VertexProp>::bfs_begin(size_t i) {
    std::vector<VertexProp> bfs_path = find_bfs_path(i);
    return bfs_iterator(bfs_path.begin());
}

template<typename VertexProp>
typename Graph<VertexProp>::bfs_iterator Graph<VertexProp>::bfs_end(size_t i) {
    std::vector<VertexProp> bfs_path = find_bfs_path(i);
    return bfs_iterator(bfs_path.end());
}

#endif  // GRAPH_HPP
