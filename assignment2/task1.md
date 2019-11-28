

1.  What is the difference between a struct and a class? (0.5 P.)
    - All members in Struct are public by default. All members in Class are private by default and members can be protected. 
    - A Struct cannot inherit from another Struct or Class. A Class can inherit from another Class.
    - A Struct is a value type (allocated on stack memory) and a Class is a reference type (allocated on heap memory). 
    
2.  Why should the public interface to a class be as small as possible? (1 P.)
The larger the public interface is, the more information is exposed and accessed/modified. This does not guarantee safety and stable performance for the program as the values/objects/instances are not well protected unless defined to be. Debugging or tracing of errors from this interface is also really problematic.
Using private could help us to track the problem down easier and faster as we know more about the error source and have less to examine. 
Furthermore, public section is accessed by all dependencies. If the project is large, there is no guarantee that all dependencies would not change our class. 

3.  What is the difference between const and static? (0.5 P.)
- Const is a type modifier for an object that ensures its value is not modified later. Static is more often used for function or class, and enables the accessibility to the instances' value for the entire run. Static instances are initialized once, persist even out of function and hold an changeable global-scoped value.

4.  Why should you distinguish between functions that modify objects and those that do not? (1 P.)
In some contexts, changing an object's value is not favorable as it introduces errors, changes the algorithm, or simply messes up with the program if modified by accident. Functions that return a const value are utilized here to prevent such situations and increase safety. 
 
5.  What is the concept and effect of inline functions? When would you prefer inline functions over function calls? (0.5 P.)
 - Unlike normal functions whose memory is allocated and referred to when being executed, inline functions enables the codes within itself to be replaced wherever it is called during compile time. This is time efficient because the program does not have to jump back and forth between addresses, copy or load the function from an other location. 
 - Inline function could be used within a class in header file to avoid linker error from function call overheads, especially when we have a complicated project.
 - If the function is small and frequently called, inline makes the performance faster. Otherwise, it is not advisable for bulky, seldomly called functions as it leads to larger executables. 
  
6.  What is a destructor and when is it called? What is the typical consequence of its usage? (1 P.)
- Destructor is the opposite of constructor - it is member function that destroys or deletes an object and releases the allocated memory. 
- Destructor is automatically called when the object goes out of scope, or more specifically, after the value is returned and before the last } of the scope. It can be called also then the program ends or when delete is called on an object. 
- Destructor frees the memory allocated to an object when called, and thus, ensures safe and effective memory management. 
    
7.  In which context are virtual functions used? (1 P.)
    Virtual functions are used in Base class so that the functions can be overriden by classes derived from Base. As each derived class has its own override version, the version will be called specifically for the object of that derived class. This hierachy prevents ambiguity for functions in derived class, especially when they share more or less similarity to each others.
    
8.  What is the semantic result of combining the keywords friend and virtual for a class function? Explain and state reasons for your observations. (1 P.)
- The friend and virtual idiom is extremely useful in case of implementing a Base class and Derive classes. Friend functions cannot be declared virtual as normal function and thus, cannot be override for the purposes in question 7. To enable dynamic binding, it has to be coupled with an other virtual function which helps to do the actual work and can be overriden in derived classes.
    
9.  When would you make a virtual member function pure? (0.5 P.)
- Making a member function pure-virtual requires it to be overriden by all derived class if they are not abstract class. If overriding functions in derived class are improper, the class stay to be abstract and cannot be instantiated just like the base class. As virtual brings about polymorphism, declaring pure virtual makes the codes less ambiguous and error prone because all functions have to be redefined. 
    
10.  What are pitfalls of multiple inheritance? (0.5 P.)
- If a class inherits from multiple classes, there could be confusion when there are functions of the same names existing in the parent classes. The ambiguity could lead to errors or miscalculation without warnings as arbitrary function is called from either one of the parents. 
11.  What is the difference between a concrete class and an interface? (0.5 P.)
- An interface does not contain the implemented codes but only provides a blueprints to implement a class. Abstract class serves as only interface while Concrete class contaisn defined functions within itself and thus, is able to instantiate an object.
