


1.  Why is it dangerous to return a reference when you must return an object? (1 P.)
   Returning a reference potentially leads to memory leak and undesired or unpredicted behaviors if the reference points to a destroyed object. Memory leak can happen when an object is allocated on heap by the new operator but its pointer/reference is not explicitly deallocated after the object is returned. Furthermore, an object would be destroyed when it goes out of the local scope so the reference now points to an arbitrary value.
   
2.  Why should you prefer range member functions to their single-element counterparts? (1 P.)
    - Range member functions are simpler to craft and potentially less confusing than a loop.
    - They are more efficient as (i) fewer operations are performed as auxilary functions are not required, (ii) less memory is allocated as single elements are not called, and (iii) the performance could be significantly improved since the functions do not take account for all elements in the container. The example in the lecture demonstrates this well: the range member insert function benefits from having v.size() move assignment, when its single-element counterpart require n*v.size() assignments.
    - The use of range member functions are more preferred for keeping the codes clean and clear.

3.  Why should you avoid in-place modification of keys in a set? (1 P.)
   Sets allow no duplicated keys and are ordered as they are sorted by keys. Thus, it is dangerous to perform in-place modification as reordering of keys of its hash can lead to invalid container. 
4.  Why should predicate functions be pure? (1 P.)
    If a predicate function is not pure, its return value does not rely solely on its own parameters, but also on other class/functions that could also modify the same parameters. Unexpected results are thus to be expected if we do not make the predicate functions pure and keep it safe from changes by using opertor() const.
5.  Why should you avoid the default capture modes of lamdbas? (1 P.)
    It is safe to forego the two default capture modes of lambdas for explicit capture. Capture by-reference could lead to dangling reference (as the object is destroyed but the reference to it lives on) and capture by-values could lead to dangling pointer (as the pointer still points to the memory location of the deallocated memory when an object is deleted).
6.  What do std::move and std::forward do? (2 P.)
    std::move is a function for casting to a rvalue reference in compile time and through that, allows user to make it a temporary object whose content can be used without being copied. 
    std::forward is used to preserve the exact type of an argument in templates when passing it to another function. For example, an rvalue argument would be passed on as rvalue and lvalue would be as lvalue.
7.  How are the strings of a std::set<std::string*> sorted? How you would make them sorted lexicographically? Provide the necessary code. (2 P.)
As the type here is std::string*, the addresses of the strings are stored and ordered in the set. Thus, the strings are not actually sorted lexicographically.
Examplary code:
```
std::set<std::string*> s;
struct compare_dereference{  
template <typename PtrType>
bool operator()(PtrType lhs, PtrType rhs) const{
	return *lhs < *rhs;
	}
};
std::set<std::string*, compare_dereference> s;
```
