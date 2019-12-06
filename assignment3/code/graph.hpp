#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>

static void check_dup_ind(size_t v_idx1, size_t v_idx2){
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

 private:
  // stores the neighbors of each vertex
  std::vector<std::list<std::size_t>> adj_list_;
  // stores the vertex properties
  std::vector<VertexProp> vertex_props_;
};

template<typename VertexProp>
Graph<VertexProp>::Graph(std::size_t num_vertices) { //TODO examine
    reserve(num_vertices);
}

template<typename VertexProp>
std::size_t Graph<VertexProp>::add_vertex(VertexProp &&prop) {
    if (find(vertex_props_.begin(), vertex_props_.end(), prop) != vertex_props_.end()) throw std::invalid_argument("This vertex is already added.");
    //TODO check capacity?
    //==============================================
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

    if (!has_edge(v_idx1, v_idx2)){
        adj_list_[v_idx1].push_back(v_idx2);
        adj_list_[v_idx2].push_back(v_idx1);
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

    if (has_edge(v_idx1, v_idx2)) { //remove if there is an edge
        adj_list_[v_idx1].remove(v_idx2);
        adj_list_[v_idx2].remove(v_idx1);
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
void Graph<VertexProp>::reserve(const std::size_t size) { //TODO reserve adj_list[i] size?
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
    return n_edges/2;
}

template<typename VertexProp>
std::size_t Graph<VertexProp>::capacity() const {
    return 0;
}

#endif  // GRAPH_HPP
