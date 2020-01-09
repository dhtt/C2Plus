**1.  Why is it dangerous to return a reference when you must return an object? (1 P.)**
    
Returning a reference potentially leads to memory leak and undesired or unpredicted behaviors if the reference points to a destroyed object. When an object is created and allocated on heap by the new operator but its pointer/reference is not explicitly deallocated after the object is returned, memory leak can happen. Furthermore, an object would be destroyed when it goes out of the local scope so its reference would now refer to an arbitrary value.
   
**2. What is an implicit interface in the context of compile-time polymorphism**
    
While both class and template support interfaces and polymorphism. For templates polymorphism, implicit interface is important as the methods have to deal with various types, as long as these types fits into the prototype of these methods, while a type must be explicitly specified for a class and its inheritance. Through template instantiation and function overloading resolution, template polymorphism occurs in compile time .
    
**3.  Why should you prefer range member functions to their single-element counterparts? (1 P.)**

* Range member functions are simpler to craft and less confusing than a loop.
* They are more efficient as (i) fewer operations are performed as auxilary functions are not required, (ii) less memory is allocated as single elements are not called, and (iii) the performance could be significantly improved since the functions do not take account for all elements in the container. The example in the lecture demonstrates this well: the range member insert function benefits from having v.size() move assignment, when its single-element counterpart require n*v.size() assignments.
* The use of range member functions are more preferred for keeping the codes clean, clear and up to standard as many are included in the standard library.

**4.  Why should you avoid in-place modification of keys in a set? (1 P.)**
    
Sets allow no duplicated keys and are ordered by keys through red-black tree implementation. Thus, it is dangerous to perform in-place modification as reordering of keys of their hash is a tedious, error-prone process. The return values could be wrong due to false branching when the initial order is messed up. 

**5.  Why should predicate functions be pure? (1 P.)**
    
If a predicate function is not pure, its return value does not rely solely on its own parameters, but also on other class/functions that could also modify the same parameters. Unexpected results are thus to be expected if we do not make the predicate functions pure and keep it safe from changes by using opertor() const.

**6.  Why should you avoid the default capture modes of lamdbas? (1 P.)**
    
It is safe to forego the two default capture modes of lambdas for explicit capture. Capture by-reference could lead to dangling reference (as the object is destroyed but the reference to it lives on) and capture by-values could lead to dangling pointer (as the pointer still points to the memory location of the deallocated memory when an object is deleted).

**7.  What do std::move and std::forward do? (2 P.)**
    
std::move is a function for casting to a rvalue reference in compile time and through that, allows user to make it a temporary object whose content can be used without being copied. 
    
std::forward is used to preserve the exact type of an argument in templates when passing it to another function. For example, an rvalue argument would be passed on as rvalue and lvalue would be as lvalue.

**8.  How are the strings of a std::set<std::string*> sorted? How you would make them sorted lexicographically? Provide the necessary code. (2 P.)**

As the type here is std::string*, the addresses of the strings are stored and ordered in the set. Thus, the strings are not actually sorted lexicographically. For lexicographic sorting, the strings have the be retrieved through dereference and compared against each other. 
Examplary code:
```
class compare_dereferenced{
public:
    template <typename PtrType>
    bool operator() (PtrType lhs, PtrType rhs) const{
        return *lhs < *rhs;
    }
};
std::set<std::string*, compare_dereferenced> s;
```
