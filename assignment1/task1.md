# Task1

 **1. List 6 built-in types provided by C++.**

6 built-in types provided by C++: char, string, int, double, float, bool. 

 **2. What is the difference between an expression and a statement? Provide an example for each.**

An expression is comprised of operants and operators that specify a computation. Meanwhile, a statement, typically an expression followed by a semicolon, can be executed singly or within a block of code embedded in braces.

***Example***

Expression: 2 +2
Statement: int a = 2+2

 **3. What is the difference between implicit and explicit type conversion?**

Implicit type conversion is performed automatically by the compiler, while explicit type conversion is defined by programmers using a type casting operator.

 **4. Why can implicity type conversion be problematic?**

Implicit type conversion might cause problems of information loss, sign loss or overflow.

 **5. What are possible consequences of using uninitialized variables?**

Using an uninitialized variable is problematic as a known value is not assigned to the variable, leading to ambiguity, uncertainty and arbitrary behaviors during the process such as producing erroneous outputs, inconsistent performance, crashing, etc.

 **6. When would a programmer prefer a switch-statement over an if-statement?**

A switch-statement is prefered when there is a need to compare multiple of values of an expression, to control a multibranching scenario with distinct cases, or to compare against constants. When multiple expressions need to be evaluated or when a boolean result is needed, if-statement would  be a better choice. 

 **7. What is a common problem with switch statements? Provide an example.**

While using switch-statement, errors could emerge from forgetting the break statement at the end of the cases since all codes after a matching label are excuted, regardless our intended branching. 

***Example*** 
```
switch( c ) { 
	case  1: ++a; 
	case  2: ++b; 
	case 3 : ++c;
	} 
``` 
Without break statements, the program will execute (++a then ++b then ++c) or (++b then ++c) or (++c), instead of incrementing just one variable a, b or c depending on case 1, 2 or 3. 
 
 **8. Name one operation available for strings but not for integers and one operation available for integers but not for strings.**

Operation for string but not integer: operator [] to get character in string.
Operation for integer but not for string: modulus operator (%).

 **9. Explain what are references and pointers. Provide examples for each.**

Reference can be understood as the alias of an object, while pointer store its memory address. 
 
 ***Example***

Reference: 
```
int a = 1357; 
int& r = a;  //r = 1357.
``` 
Pointer: 
```
int* p = &a //p holds the memory address of a, while &-operator get the address of a so they are the same.
```

 **10. Explain the relationship between pointers and arrays (and C-strings). Provide examples.**

Pointer holds the address of the first element of the array, so by incrementing pointer variable, we move across the array to its end.
 
***Example***
```
char c = 'C++' //memory address of c: |156| 157 |158|
char* p = c; //p = 156
++p //p=157; *p = '+'
```

 **11. Explain the pass by value and pass by reference concepts. Provide examples.**

Pass by value is when an actualy value of an object is passed on, while pass by reference is when the memory address of the variable is passed on. The value stored in the address is changed directly by its reference.

***Example***
Pass by value: 
```
int total_pies = 10; 
ate_one_pie(int pies){return pies-1;}; 
ate_one_pie(total_pies); //total_pies, for example, has value 10 at address 156 before and value 9 at address 208 after ate_one_pie() is called. 
```
Pass by reference: 
```
int total_pies = 10; 
ate_one_pie(int& pies){return pies-1;}; 
ate_one_pie(total_pies);/ /total_pies, for example, has value 10 at address 156 before and value 9 at the same adress after ate_one_pie() is called.
```

 **12. Explain the terms declaration and definition.**

Declaration means to give the information of a variable or a function to the compiler, including its name, type, initial values, return value, etc. Definition is a process in which the memory for a variable or function with its parameters is allocated. 

 **13. What is a namespace and what is its typical use?**

Namespace is defined as a declarative region providing scope for its entities. Namespace is typically used for avoiding name collision. Variable, function or type from different scope might employ the same name and raise error if they are put together in a program. Declaring namespace allows reference to different scopes to which the entities belong and thus, solve the conflict. 

 **14. Why should you avoid using directives in a header?** 

Using directives in headers would lead to loading of all namespace into scope and thus, introduce clashes and collision when multiple headers are included. 

 **15. Four types of errors:**

Compile-time error: 
```
 char a = 10; 
 int b = a; 
 //implicit type casting leads to error that b !=10). 
 ```
Link-time error: 
```
string a = do_a_barrel_roll('foobar') 
//do_a_barrel_roll() is not defined. 
 ```
Run-time error: 
```
double devide_by_zero(double a){return a/0;}
```
Logic error: 
```
double rectangle_area(int height, int width){return height*width*3.14;}
```

 **16. What is the free store and for what reasons might one use it?**

Free store is the memory compartment that is dedicated to dynamic allocation of memory during execution. The 'new' operator to allocate free store to a variable return a pointers, which hold no information about how many elements it points to and thus, allow to versatilely grow or shrink a dynamic data structure of a certain type.

 **17. How do you allocate memory and about what do you need to be careful? Provide an example.** 

To allocate memory, the new operator is used. It should be kept in mind to deallocate the used memory back to the free store with delete operator to avoid memory leaks. 

***Example***
```
string* concat(string a, string b){
    string* c = new string;
    c = a + b;
    return (c);
}
string* concat_string = concat("programming","course")
cout << concat_string;
delete concat_string; \\here the allocated memory is freed
```
 **18. How do you safely allocate/manage memory?**

To safely allocate/manage memory, we should make sure that the correct memory is deallocated and deallocation is executed thoroughly. As suggested in the lecture, exception handling or scoped resource management with std::unique_ptr,  std::make_unique might come as handy to assure this. Another option is to not complicate things by avoiding pointers. 

 **19. What is RAII?**

RAII is a technique that facilitates the handling of a resource through a class constructor and destructor insteading going through operators like new/delete, open/close, lock/unlock.  With RAII, one can rest assure the resource is released without having to deal with errors raised from early return and exception, which can be tedious to fix.

