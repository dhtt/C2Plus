## Assignment project 4
### 1. Munkres_assignment_solver
A program that takes a matrix input and apply [Munkres algorithm](https://www.sciencedirect.com/science/article/abs/pii/S026288560800084X) to solve the [assignment problem](https://en.wikipedia.org/wiki/Assignment_problem). 

==========================================

*_Sample input_

250 400 350

400 600 350

200 400 250

*_Sample output_

0    1    0

0    0    1

1    0    0

==========================================

### 2. Bron-Kerbosch_maximal_cliques_generator
A program that takes an adjacency matrix on the standard input and outputs all maximal cliques on the standard output using the [Bron-Kerbosch algorithm](https://en.wikipedia.org/wiki/Bron–Kerbosch_algorithm) to detect the maximal cliques. 

==========================================
_*Sample input_

0 1 0 0 1 0 

1 0 1 0 1 0

0 1 0 1 0 0

0 0 1 0 1 1

1 1 0 1 0 0

0 0 0 1 0 0

_*Sample output_

{0, 1, 4}

{1, 2}

{2, 3}

{3, 4}

{3, 5}

==========================================
