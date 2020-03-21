## Assignment project 1
### 1. [string_search](string_search.cpp) and [binary_string_search](binary_string_search.cpp)
A program that takes a set of words sorted in descending lexicographic order, without duplicates, each on its own line on the standard input. The program should be able to take multiple arguments and to print on the standard output for each argument the line number in which it occurred on the standard input. If the argument was not found, "not found" should be printed instead. The first version of the program finds the words in linear time, whereas the second one finds them in logarithmic time.

==========================================

_Sample input_
  
  CGA

  AGGCA

  AGACG 

_Program arguments_ 
  AGGCA GCA 

_Sample output_

  2  
  not found
  
==========================================

### 2. [FASTA_palindrome_finder](FASTA_palindrome_finder.cpp)
A program that takes a FASTA file as first argument and outputs the number of lines, the number of sequences, the AU ratio, and the percentage of A, C, G and U of the sequences in it. The program should take as second argument an output file and write all sequences that are palindromes in it, one sequence per line. If DNA sequences are found, they are converted to RNA. If a sequence is not RNA nor DNA output its corresponding FASTA header on the standard error stream and don’t count any characters of it for the AU ratio and A, C, G, U percentages and do not check if the sequence is a palindrome. DNA sequences that are palindromes should be outputted as RNA sequences in the palindrome output file and all sequences in the palindrome file should be in upper case letters.
