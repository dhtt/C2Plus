## Assignment project 3
### 1. [t_statistics_calculator](t_statistics_calculator.cpp)
Calculate the t stastistic for independent two-sample t-test with equal sample sizes 

### 2. [lightweight_grep](assignment3/code/lightweight_grep.cpp)
A lightweight version of grep that allows to find arbitrary user-defined text-patterns in a given set of files with several options to specify the strictness of matching and the output formatting. 

==========================================

_*basic usage_: ./lightweight_grep pattern list of filenames...

_*case-sensitivity:_ ./lightweight_grep -i pattern list of filenames...

_*use fixed-string instead of a regular expression:_ ./lightweight_grep -F pattern list of filenames...

_*whole word matching_: ./lightweight_grep -w pattern list of filenames...

_*read from FILENAME_: ./lightweight_grep -f FILENAME list of filenames...

_*output non-matching lines_: ./lightweight_grep -v pattern list of filenames...

_*print line number where a match is found_: ./lightweight_grep -n pattern list of filenames...

==========================================

### 3. [graph_maker](assignment3/code/graph.hpp)
An unweighted directed Graph class stores its vertices in an adjacency list. The following properties are implemented:

1. dfs_iterator dfs_begin(std::size_t vertex_idx)
2. dfs_iterator dfs_end(std::size_t vertex_idx)
3. bfs_iterator bfs_begin(std::size_t vertex_idx)
4. bfs_iterator bfs_end(std::size_t vertex_idx)
5. const_dfs_iterator dfs_begin(std::size_t vertex_idx) const
6. const_dfs_iterator dfs_end(std::size_t vertex_idx) const
7. const_bfs_iterator bfs_begin(std::size_t vertex_idx) const 
8. const_bfs_iterator bfs_end(std::size_t vertex_idx) const
9. operator *it returning the underlying object
10. operator ++it letting the iterator point to the next element
11. operator == and != 
