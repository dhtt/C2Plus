**1.  What is the difference between the keywords typedef and using? Also, state one usage example for both. (0.5 P.)**
While both are helpful for alias-declaration, "using" enables the user to form template alias, while "typedef" does not. For example:
```
template <typename T> 
class A {};
template <typename T> 
class B {
  typedef A<T> TYPE;
};

B<int>::TYPE variable;
template <typename U> class C { typename B<U>::TYPE example_var; }
```
```
template <typename T> using TYPE = A<T>;

TYPE<int> variable;
template <typename U> class C { TYPE<U> example_var; }
```
"using" allows the declaration TYPE< U > while for "typedef", it is neccesary to point out the type is "typename B< U >::TYPE"
    
**2.  What are iterators? Name at least 3 different types of iterators and explain their functionalities. (1 P.)**
    Iterators are objects functioning as pointers to the memory address of an element in a container. Though iterators, the program can get access to the container members and traverse between those, allowing algorithms to be applied in a convenient and dynamic manner. 
    Three types of iterators:
    Input iterators: Iterators which allows single pass through the elements. Each container member is read once and then the iterator increments and points to the next member in the sequence.
    Output iterators: Iterators which do not allow access to values, but rather can be assigned with values. Like input iterator, it provide single pass through the member of the sequence. 
    Forward iterators: Iterators with combined functions from input and output iterators. They allow access and modification to/of values in the sequence in operation. Unlike input and output iterators, they own multi-pass functionality. 

**3.  What is a crucial difference between an input and a forward iterator? (0.5 P.)**
    Forward iterators allow multipass, and input iterators are more limited by allowing single pass only. While both are undirectional, using forward iterator one can pass through an element more than once by the same iterator values. Furthermore, a forward iterator, if not defined const, allow not only access to values in the sequence but also assignment of values when this is impossible for input iterator. 
    
**4.  Why are iterators to a std::vector invalided by insert, push_back or erase? (0.5 P.)**
    When we use push_back, erase or insert on an vector, its size changes and as vector can be described as linear, the elements inside are moved as the result of squeezing in a new element (like frameshift point mutation on a gene). Meanwhile, the iterator keeps pointing to the same address and thus would return another values or arbitrary values if the data are erased. 
    
**5.  Which container would you choose and why if**
*a) you need to do sorted traversal and no duplicates are allowed (0.5 P.)*

Set: Sets allow no duplicated keys and are ordered as they are sorted by keys. 

*b) the order is not important and no duplicates are allowed (0.5 P.)*

Unordered_set: Unordered_sets allow only unique keys and are hashed by keys so they are not ordered.
        
*c) you only need to add elements at the end and want fast traversal (0.5 P.)*

Vector: Vector is a sequence container that can grow, which is perfect for adding more elements. For fast traversal one can choose between iterator, [] or at(), which are convenient and fast.
        
*d) you need to provide a dictionary that can associate multiple values with the same key (0.5 P.)*

Map: Maps store the key and values associated to it like a dictionary. To store multiple values, the value type could be pair, vector, etc depending on personal usage. 

**6. How does an STL algorithm usually indicate "not found" or "failure"? (0.5 P.)**
    The returned iterator would be ".end()", which points to the address right past the last element, as this indicates no values meet the return requirement/condition of the algorithm  during the traversal of all the container' members.

**7.  What does std::sort(b,e) use as its sorting criterion? (0.5 P.)**
    The algorithm include a comparison between the first argument and the second argument, which returns true if the first less than the second. In that case, the first is ordered before the second. The arguments are retrieved through the iterator.
    
**8.  Why is the STL container set missing a [] (subscript) operator? (0.5 P.)**
Set does not have the linear property like vector as it is implemented as self-balancing binary search tree. This allows set insertion, removal and search operations to have logarithmic complexity. Overloading [] for set does not make much sense then as set's elements are sorted using its compare function always. 

**9. Why does std::map require its key_type to be copy-constructible and its mapped_type to be default constructible? (1 P.)**
The key type must be copy-constructible so that when user looks up a key, it is copied and searched in the map for stored values. 

**10. Why is std::forward_list missing a size member function and why is the empty member-function still implemented if it is typically equal to container.size() == 0? (1 P.)**
	
std::forward_list lacks a size member function because that cannot support the current number of elements to be stores or computes in constant time. Such function would have to keep track of the list head and the count, meaning whether one uses the function or not, every operation that changes the number of nodes would slow down the entire process. It thus make more sense to keep track of the container size outside the list if size is needed. 
Empty function check if forward_list is empty by comparing .begin() and .end() so it does not rely on the actual size of the list. 