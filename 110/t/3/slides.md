class: middle
# Tutorial 3
## Revision

---
layout: true
class: middle
---

These slides are available at:
.bigtext[
```
pbosmancsupacza.github.io
```
]
- my email address (pbosman@cs.up.ac.za) without any punctuation
- hosted on github pages, so .github.io

---

# Overloading operators

---

Operators can be overloaded as either
- member functions
- standalone functions

---

The following binary operator...

```c++
MyClass lhs, rhs;
lhs + rhs;
```

---

... can be overloaded as a **member** of `MyClass`:

```c++
class MyClass {
public:
   MyClass operator+ (MyClass);
};
```

---

... in which case, when it is invoked...

```c++
lhs + rhs;
```
- the LHS operand is the **calling object** (i.e. `this`)
- the RHS operand is the **argument** (i.e. the parameter)

---

If the result of the operation is assigned to something...

```c++
result = lhs + rhs;
```
... that result is what the operator **returns**.

---

Example implementation:
```c++
// constructor:
MyClass::MyClass(int x) {
   memberVariable = x;
}

// operator:
MyClass MyClass::operator+(MyClass rhs) {
   int sum = this->memberVariable + rhs.memberVariable
   MyClass result(sum);
   return result
}
```
--

- `this->memberVariable` is a member variable of the **calling object**, which is the LHS operand of the operator
--

- `rhs.memberVariable` is a member variable of the **argument**, which is the RHS operand
--

- the two operands' member variables are added together and assigned to `sum`
--

- a **new** object of type `MyClass` is created
  - the parameterized constructor is invoked with `sum`
--

- the result is returned

---

The operator can also be overloaded as a *standalone* operator:

```c++
class MyClass {

};

MyClass operator+ (MyClass, MyClass);
```

---

... in which case, when it is invoked...

```c++
lhs + rhs;
```
- the LHS operand is the **first parameter**
- the RHS operand is the **second parameter**

And since the operator is not a member of `MyClass`, there is no calling object (`this`).


---

If the result of the operation is assigned to something...

```c++
result = lhs + rhs;
```
... that result is, once again, the value that operator **returns**.

---

Standalone operators are usually *friends* of the classes they are overloaded for. (Why?)

---

```c++
class MyClass {
   friend MyClass operator+ (MyClass, MyClass);
};
```

---

Example implementation:
```c++
MyClass operator+ (MyClass lhs, MyClass rhs) {
   int sum = lhs.memberVariable + rhs.memberVariable;
   MyClass result(sum);
   return result;
}
```
--

- `lhs.memberVariable` is a member of the left operand of the operation
  - `lhs` is passed as the first parameter
--

- `rhs.member` is a member of the right operand of the operation
--

- there is no `this`
--

- the sum of the operands' member variables are used to create a result object
--

- the result is returned

---

Do not write **both** member and standalone versions of an operator

---

```c++
class MyClass {
public:
   MyClass operator+ (MyClass);

   friend MyClass operator+ (MyClass, MyClass);
};

MyClass operator+ (MyClass, MyClass);
```

---

The compiler won't know which version to invoke.

---

# Overloading the stream operators

---

The stream extraction operator (<<) inserts values into stream.

---

For example, in
```c++
cout << 1;
```
the value `1` is inserted into the `cout` object.
--


(`cout` is an object of the `ostream` class. When values are inserted into the `cout` stream, they appear on the terminal's standard output stream.)

---

The stream extraction operator (>>) gets values from a stream.

---

For example, in
```c++
int i;
cin >> i;
```
a value is read from the `cin` object into the variable `i`.
--


(`cin` in an object of the `istream` class. When values are extracted from `cin`, they are read from the terminal.)

---

The stream operators can be overloaded for user defined types.

---

For example:

```c++
MyClass object;
cin >> object;
cout << object;
```
--

What is the left-hand-side operand of each operation?
--


Can the stream operators be implemented as members of `MyClass`?

---

Recall that operators can either be members of classes, or standalone.

Stream operators are always invoked with stream objects as left-hand-side operands.

So the operators can either be
- members of the stream classes
- or standalone functions

... but we don't have access to the stream classes' definition, so only the second option is available to us.

---

```c++
class MyClass
   //...
   friend ostream& operator<<(ostream&, MyClass);
};
```

---

```c++
ostream& operator<<(ostream& out, MyClass myObject) {
   out << myObject.memberVariable;
}
```

---


- `operator<<` is a *friend* of `MyClass`, not a member
---


- return type is `ostream&`
  - allows chaining; e.g. `cout << obj1 << obj2;`
---


- return type *must* be by reference
  - otherwise `ostream`'s copy constructor would be invoked
  - but `ostream`'s copy constructor is private
---


- the operator's name is `operator<<`
---

- there are two parameters
  - because `<<` is a binary operator
---


- first parameter is the left-hand operand, which is of type `ostream`
  - also passed by reference; CC is private
---


- second parameter is the right-hand operand, which is the type we are overloading the operator for
---

- in the implementation, we can use existing overloaded versions of the `<<` operator to help implement ours

---

Similary, for the extraction operator:

---

```c++
class MyClass {
   // ...
   friend istream& operator>> (istream&, MyClass);
};
```

---

```c++
istream& operator>> (istream& in, MyClass myObject) {
   in >> myObject.memberVariable;
}
```

---

# Overloading the array subscript operator

---

The array subscript operator (`[]`) is used to access elements of an aray:
```c++
int arr[] = {1,2,3};
int x = arr[1];
```

---

The operator can be overloaded for out own classes.

---

For example:
```c++
MyClass object;
int x = object[0];
```

---

The array subscript operator is a binary operator

```c++
object[0]
```

---

Can be a member of our class:

```c++
class MyClass {
   //...
public:
   int operator[] (int index) {
      return something;
   }
};
```

---

Or a standalone operator:

```c++
class MyClass {
   // ...
   friend int operator[] (MyClass, int);
};

int operator[] (MyClass object, int index) {
   return object.something;
}
```

---


We usually create two versions:
- One that returns a value **by reference**
- One that returns a **`const`** value, also by reference, and is `const` itself

---

```c++
class MyClass {
   //...
public:
         int& operator[] (int i);
   const int& operator[] (int i) const;
};
```

(Both can have the same implementation)

---

We return by reference so that the result is an *lvalue* - i.e. so that we can assign to it:
```c++
MyClass object;
object[0] = 1;
```

---

We include a `const` version so that, if the object is `const`, we can still read its elements:
```c++
int foo(const MyClass object) {
   return object[0];
}
```

---

# Object conversion

---

C++ does automatic type conversion for primitive types. E.g.
```c++
double d = 3.14;
int i = d;
d = i;
```

---

We can implement type conversion for our own classes. This is called object conversion.

---

```c++
DistanceClass d(10,2,90);
double distance = d; // convert to double

TimeClass t(15, 15, 0);
long seconds = t; // convert to long
```

---

Note that, in the following statements:
```c++
DinstanceClass d = 10.29;

TimeClass t;
t = 360000;
```
A **constructor** and **assignment operator** are invoked, respectively; this is not conversion.

---

To enable object conversion, we overload *conversion operators*.

---

```c++
class Time {
   int h, m, s;
public:
   operator int();
};

Time::operator int() {
   return s + 60*m + 3600*h;
}
```

---

The conversion operator's name is the type that it will convert to

---

There is no return type

---

There are no parameters

---

Only ZUUL

---

Objects of the type can now be automatically converted to `int` values
```c++
Time t;
int seconds = t;
cout << t << endl;
```

---

Several conversion operators can be created for different types.

---

Conversion operators can also be created for user-defined types (a.k.a. classes)

---

If a class has more than one conversion operator, the following statement won't work:
```c++
cout << object;
```
The compiler won't know which operator to invoke.

---

If a statement can invoke both a conversion operator and a constructor or assignment operator, it won't compile.
```c++
class A {
   A(B);
};

class B{
  operatorA();
};

B b;
A a = b; // constructor or converter?
```

---

# Aggregation

---

Class member variables can be of user-defined types:

```c++
class TypeA {};

class TypeB {
   TypeA memberVariable; // valid
};
```

---

This is called aggregation.

---

**Note:** Unless you use an *initializer list*, constructing an aggregate object will invoke the default constructors of its parts.

```c++
class Part {
public:
   Part() {
      cout << "part created" << endl;
   }
};

class Whole {
   Part part1, part2;
public:
   Whole() {
      cout << "whole created" << endl;
   }
};

Whole whole();
```
Output:
```
part created
part created
whole created
```

---

# Dynamic memory
## some notes

---

When declaring pointers, put the asterisk against the variable name.

This is easier to read if you declare multiple pointers.

```c++
int *p, q, *x;
```

---

Initialize pointers to `0`. This means it points to nothing.

```c++
int *p = 0;
```

`NULL` is a defined constant that means the same thing, but it isn't always available.

---

Dynamic variables are allocated on the heap at runtime, and can be any size.

The `new` keyword allocated dynamic memory and returns a pointer to that memory.

---

To allocate a single variable:
```c++
new DataType;
```

---

To allocate an array of variables:
```c++
new DataType[size];
// where size is an integer
```

---

To use memory allocated by `new`, we must assign the result to a pointer:
```c++
int *p = new int;
int *q = new int[10];
```

---

Dynamic memory must be deallocated manually.

To deallocate memory, use the keyword `delete` with a pointer to that memory:

```c++
delete p; // single variable
delete [] q; // array of variables
```

---

After the memory has been deallocated, the pointer is *dangling*. Set the pointer to null.

```c++
delete p;
p = 0;
```

---

If memory is not deallocated before you lose reference to it, *memory leak* occurs.

Too much memory leak will fill up the heap.

---

```c++
void foo() {
   int *p = new int;
}

while (true)
   foo();
```
Each time the function exits, memory leak occurs

---

```c++
int *p;
p = new int;
p = new int;
```
Memory leak occurs when `p` gets a new value

---

You can assign to pointers:
```c++
int *p = new int;
int *q = p;
```

---

You can compare pointers:
```c++
int *p, *q;
// ...
if (p < q) {
   // ...
}
```

---

You can add integers to pointers
```c++
int *p;
int *q = p+1;
```

---

Adding or substracting integers to/from pointers is called *pointer arithmetic*.

C++ performs scaling so that steps through memory are of the size of the type of the pointer.

---

To allocate a dynamic array:
```c++
int *array = new int[size]; // size can be set at runtime
```

---

To iterate through a dynamic array:
```c++
for (int i = 0; i < size; i++)
   *(array + i) = 0;
```

---
- or:

```c++
for (int *i = array; i < array + size; i++)
   *i = 0;
```

---

- or:

```c++
for (int i = 0; i < size; i++)
   array[i] = 0;
```

---

To allocate a dynamic 2D array:

```c++
int **array = new int*[numRows];
for (int row = 0; row < numRows; row++)
   array[row] = new int[numCols];
```
---

To deallocate a dynamic 2D array:
```c++
for (int row = 0; row < numRows; row++)
   delete [] array[row];

delete [] array;
```

---

If a function returns a pointer, that pointer **may not** be the address of a local static variable:
```c++
int* foo() {
   int x;
   return &x; // invalid
}
```

---

A function may return the address of a dynamic variable:
```c++
int *foo() {
   int *x = new int;
   return x;
}
```

---

If a parameter is passed to a function *by value*, a copy is made and the original cannot be changed by the function.
```c++
int increment(int i) {
   i++;
}

int var = -1;
increment(var);
// var is still -1
```

---

If a parameter is passed to a function *by reference*, the function can operate on the original directly.
```c++
int increment(int &i) {
   i++;
}

int var = -1;
increment(var);
// var is 0
```

---

In a function's signature, the ampersand (`&`) **does not** mean "address of".

---

Pointers can be also passed to functions by value or by reference.
```c++
void incByValue(int* v) {
   (*v)++;
   v++; // no effect
}

void incByReference(int *&v) {
   (*v)++;
   v++;
}
```
Both functions can modify the value their parameters are *pointing to*, but only the reference version can modify the pointer.

---

This is a shallow copy:
```c++
int *original = new int[5];
// populate original...
int *copy = original;
```
`copy` points to the same array as `original`.

---

This is a deep copy:
```c++
int *original = new int[5];
// populate original...
int *copy = new int[5];
for (int i = 0; i < 5; i++)
   copy[i] = original[i];
```
`copy` points to a newly-allocated array that has the same element values as `original`.

---

# End
