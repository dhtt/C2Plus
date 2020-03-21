## Assignment project 2
### 1. gene_cluster_finder
A program computes gene clusters in which each gene is at most at distance d of at least one other gene of the cluster and all being located on the same chromosome. The distance between two genes is determined by their middle positions.
The genes will be passed as tab-separated text file as first argument. The allowed distance will be passed as second argument and the output file as third argument. The input file consists of three columns: chromosome start stop, start and stop represent a closed interval and begin at one. The clusters should be sorted in ascending coordinate order.

==========================================

_*Sample input_

chr1 100 21000

chr1 250 18000

chr1 21000 24000

chr2 1300 10800

_*Sample output_

chr1 100 21000 cluster=1

chr1 250 18000 cluster=1

chr1 21000 24000 cluster=2

chr2 1300 10800 cluster=3

==========================================

### 2. Nussinov_secondary_structure_finder
A program that takes one RNA sequence as argument and outputs the score of the best secondary structure it could form (i.e. the maximum number of base pairs for this sequence) using Nussinov algorithm (https://math.mit.edu/classes/18.417/Slides/rna-prediction-nussinov.pdf) and dynamic programming. Secondary structures should be output in dot-bracket notation.

==========================================

_*Sample program argument_

GGUCCACU

_*Sample output_

2 ((..).) ((..)).

==========================================

### 3. dynamic_dataframe
A class Dataframe that can manage a dynamic number of columns (of identical length), where each column has its own value type. The dataframe is capable of encapsulating any valid C++ type and contain heterogenous data types. The following properties are implemented:

1. Dataframe(), default initialized.
2. Copy constructor and copy assignment operator (generation by the compiler
is allowed).
3. Move constructor and move assignment operator (generation by the compiler is allowed).
4. Memberfunctionsnrowsandncolsprovidingthenumberofrowsandcolumns.
5. Member function get<T>(i,j) to access and/or modify the element of type T stored at row i and column j. The data access is 0-indexed. This should return a reference to the original element (ensure const-correctness!).
6. Member function get<T>(r,c) to access and/or modify the element stored at row named r and column named c. This should return a reference to the original element (ensure const-correctness!).
7. Member functions set_colnames and set_rownames to set the column names and row names.
8. Member functions clear_colnames and clear_rownames to remove column and row names.
9. Member functions has_colnames and has_rownames to check if column names or row names have been specified.
10. Member function add_column<T>(vector<T>) that adds a new column with entries of type T.
11. Member function remove_column that removes a column either by index or by name.
12. Member function swap_columns that allows to exchange the position of two columns, both either being given by numeric index parameters or by column name.
13. Member function apply that executes on a given column identified by either index or name the passed lambda function on each element of the column (functions that modify the elements are allowed).
14. Member function order_by that allows to sort the elements (in ascending order by using operator <) of a given column identified by either index or name. 
15. Operator << to output data. 
16. Operator == and != that check the elements of the dataframes for (in)equality. 
