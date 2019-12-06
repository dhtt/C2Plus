#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "graph.hpp"
Graph<int> G1();
Graph<char> G2(6);

TEST_CASE("add_edge valid"){
    G2.add_vertex('A');
    G2.add_vertex('B');
    G2.add_vertex('C');
    G2.add_vertex('D');
    G2.add_vertex('E');
    G2.add_vertex('F');
    REQUIRE(G2.add_edge(0, 1));
    REQUIRE(G2.add_edge(1, 2));
    REQUIRE(G2.add_edge(2, 3));
    REQUIRE(G2.add_edge(3, 0));
    REQUIRE(G2.add_edge(3, 4));
    REQUIRE(G2.add_edge(4, 5));
}
TEST_CASE("add_edge invalid"){
    REQUIRE(!G2.add_edge(1, 0)); //An edge already exists.
    REQUIRE(!G2.add_edge(1, 1)); //Vertex cannot have edge to itself.
    REQUIRE(!G2.add_edge(8, 0)); //Vertex index out of range.
    REQUIRE(!G2.add_edge(8, 10)); //Vertex index out of range.
}

TEST_CASE("remove_edge valid"){
    REQUIRE(G2.remove_edge(1, 2));
    REQUIRE(G2.remove_edge(0, 3));
}
TEST_CASE("remove_edge invalid"){
    REQUIRE(!G2.remove_edge(5, 0)); //Edge does not exist.
    REQUIRE(!G2.remove_edge(1, 1)); //Vertex cannot have edge to itself.
    REQUIRE(!G2.remove_edge(8, 0)); //Vertex index out of range.
    REQUIRE(!G2.remove_edge(8, 10)); //Vertex index out of range.
}

TEST_CASE("add_vertex valid"){
    REQUIRE(G2.add_vertex('G') == 6);
    REQUIRE(G2.add_vertex(1) == 7);
}
TEST_CASE("add_vertex invalid"){
    REQUIRE_THROWS_AS(G2.add_vertex('E'), std::invalid_argument); //This vertex is already added
}

TEST_CASE("get_neighbors valid") {
    REQUIRE(G2.get_neighbors(6).empty());
    REQUIRE(G2.get_neighbors(3).size() == 2);
    REQUIRE(G2.get_neighbors(4).size() == 2);

    G2.add_edge(4,2);
    G2.add_edge(4,0);
    G2.add_edge(4,7);
    REQUIRE(G2.get_neighbors(4).size() == 5);
    G2.remove_edge(7,4);
    REQUIRE(G2.get_neighbors(4).size() == 4);
}
TEST_CASE("get_neighbors invalid") {
    REQUIRE_THROWS_AS(G2.get_neighbors(10), std::out_of_range); //Vertex index out of range.
    REQUIRE_THROWS_AS(G2.get_neighbors('b'), std::out_of_range); //Vertex index out of range.
}

TEST_CASE("get_vertex valid"){
    REQUIRE(G2.get_vertex(6) == 'G');

    REQUIRE(G2.get_vertex(7) == 1);
    G2.get_vertex(7) = 'H';
    REQUIRE(G2.get_vertex(7) == 'H');
}
TEST_CASE("get_vertex invalid"){
    REQUIRE_THROWS_AS(G2.get_neighbors(20), std::out_of_range); //Vertex index out of range.
    REQUIRE_THROWS_AS(G2.get_neighbors('b'), std::out_of_range); //Vertex index out of range.
}

TEST_CASE("has_edge valid"){
    REQUIRE(G2.has_edge(0, 4));
}
TEST_CASE("has_edge invalid"){
    REQUIRE(!G2.has_edge(7, 0));
    REQUIRE(!G2.has_edge(0, 0)); //Vertex cannot have edge to itself.
    REQUIRE(!G2.has_edge(1, 20)); //Vertex index out of range.
}

TEST_CASE("num_edges valid"){
    REQUIRE(G2.num_edges() == 6);
    G2.add_edge(1,3);
    G2.add_edge(7,2);
    REQUIRE(G2.num_edges() == 8);
    G2.remove_edge(7,2);
    REQUIRE(G2.num_edges() == 7);
}
TEST_CASE("num_edges invalid"){
}

TEST_CASE("num_vertices valid"){
    REQUIRE(G2.num_vertices() == 8);
    G2.add_vertex('I');
    G2.add_vertex('J');
    REQUIRE(G2.num_vertices() == 10);
}
TEST_CASE("num_vertices invalid"){
}
