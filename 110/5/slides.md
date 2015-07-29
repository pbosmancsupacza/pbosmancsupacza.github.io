class: middle
# Copy Constructors & Intro to Operator Overloading

---

## This lecture:
- Copy constructors
- Overloading the assignment operator
- Overloading operators in general

---

class: middle
# Copy Constructors

---

## Copy constructors
Consider this class:
```c++
class Elvis {
public:
  Elvis() {
    cout << "Elvis has entered the building" << endl;
  }
  ~Elvis() {
    cout << "Elvis has left the building" << endl;
  }
};
```
It will print a message whenever the default constructor is invoked.

---

## Copy constructors
Now check out this client code:
```c++
cout << "Elvis the first:" << endl;
Elvis elvis1;
cout << "Elvis the second:" << endl;
Elvis elvis2 = elvis1;
cout << endl;
```
It will output the following:
```
Elvis the first:
Elvis has entered the building
Elvis the second:

Elvis has left the building
Elvis has left the building
```

What happened to the constructor message for `elvis2`?

---

## Copy constructors
In C++, a statement like `Elvis elvis2 = elvis1` doesn't cause the default constructor to get invoked. Instead, a different constructor, called the **copy constructor**, is invoked.

Similarly to the default constructor, if you do not define your own version of the copy constructor, C++ provides a default.

The default copy constructor performs memberwise assignment.

---

## Copy constructors
So if we want our `Elvis` class to print a message every time an object is instantiated, we provide our own copy constructor:
```c++
class Elvis {
public:
  Elvis() {
    cout << "Elvis has entered the building" << endl;
  }
  ~Elvis() {
    cout << "Elvis has left the building" << endl;
  }
  /// COPY CONSTRUCTOR:
  Elvis(const Elvis &) {
    cout << "Elvis has entered the building" << endl;
  }
};
```

---

## Copy constructors
If a class has member variables, we have to do the memberwise assignment ourselves (if we want it):
```c++
class ElvisImpersonator {
  string realName;
  int age;
public:
  Elvis(string n, int a) {
    realName = n;
    age = n;
    cout << "Thank you. Thank you very much."
  }
  Elvis(const Elvis &otherImpersonator) {
    realName = otherImpersonator.realName;
    age = otherImpersonator.age;
    cout << "Thank you. Thank you very much."
  }
  // etc
};
```

---

## Some notes
### Access to private members
Notice that one Elvis impersonator has access to another impersonator's private members. C++ allows one object to access another's private members if
1. the other object is passed as a parameter to a function, and
2. the other object is the same type as the one that's doing the accessing.

For example:
```c++
class Paranoid {
private:
  int var;
  void print() {
    cout << x << endl;
  }
public:
  void access(Paranoid other, int v) {
    other.var = v; // valid, even though var is private
    other.print(); // also valid
  }
};
```

---

## Some notes
### const
In the Elvis examples, the copy constructor's parameter is `const`. This is not a requirement, but generally regarded as a good idea. Can you tell why? (The previous slide should make it pretty clear.)

---

## Some notes
### reference
The copy constructors from the examples also had their parameters passed by reference. This **is** a requirement.

If an object is not passed by reference, a copy is created. Guess which constructor is invoked.

A reference parameter is needed so that the copy constructor is not called recursively indefinitely.

---

## Some notes
### parameter name
The name of the parameter can be whatever you want it to be. The right-hand-side of an assignment upon initialization will always be assigned to the parameter.

---

## Copy constructors: A more serious use case
Consider the following class:
```c++
class WithPointer {
private:
  int *pointer;
public:
  int* getPointer() {
    return pointer;
  }
  void setPointer(int *p) {
    pointer = p;
  }
};
```

---

## Copy constructors: A more serious use case
... And this client code:
```c++
WithPointer original;
original.setPointer(new int(10));

WithPointer clone = original;
*clone.getPointer() = 11;

cout << *original.getPointer() << endl;
// prints 11
```
Even though we changed the value of the integer that `clone` was pointing to, it also changed for `original`. That's because memberwise assignment only does **shallow** copying of pointers.

---

## Copy constructors: A more serious use case
### Shallow copying
When copying pointers, the default behaviour is to make shallow copies. A shallow copy means:
- One pointer variable is copied to another
- But only the address stored in the first variable is copied to the second
- So each variable points to the same object or variable
- So changes made to the object using one of the pointers will change the value of the object as it is seen by the other pointers

---

## Copy constructors: A more serious use case
### Shallow copying
```c++
int *pointer1 = new int(-1); // p1 points to an integer
int *pointer2 = pointer1; // p2 points to the same integer as p1
(*pointer2)++; // p2 increments the integer it points to
cout << *pointer1 << endl; // prints `0` because:
  // the integer that p1 points to was "also" incremented
  // ("also" because it's the same integer)
```

---
background-image: url(./res/copy.png)
## Copy constructors: A more serious use case
### Shallow copying
---

## Copy constructors: A more serious use case
We can implement our own copy constructors to perform deep copies of pointers.
```c++
class WithPointer {
private:
  int *pointer;
public:
  // default constr (otherwise there would be none)
  WithPointer() {}

  // our own copy constr
  WithPointer(WithPointer &other) {
    pointer = new int(*other.pointer);
  }

  ~WithPointer() {
    if (pointer) delete pointer;
  }

  // etc
};
```

---

class: middle
# Assignment operator

---

## Assignment operator
The following statements
```c++
WithPointer lhs, rhs;
lhs = rhs;
```
do **not** cause the copy constructor to be invoked. Rather, in the second line, the **assignment operator** is invoked.

As with the copy constructor, C++ provides a default assignment operator that performs memberwise assignment. And, as with the copy constructor, we can provide our own version of the assignment operator. This is operator overloading.

---

## Assignment operator
Did you know that this statement
```c++
lhs = rhs;
```
is equivalent to this one?
```c++
lhs.operator=(rhs);
```
In the second statement, you can see that the `=` operator is takes the form of a function where
- the name of function is `operator=`
- the function is called on the left-side object in the statement
- the right-side object in the statement is passed as a parameter to the function

---

## Assignment operator
### Overloading the assignment operator:
In the header file:
```c++
class WithPointer {
  // ...
public:
  void operator=(const WithPointer&);
};
```

---

## Assignment operator
### Overloading the assignment operator:
Notes:
- The return type can be anything (doesn't have to be `void`)
- There can be white space between `operator` and `=`

  (e.g. void operator = (...))
- There **must** be exactly one parameter
- The parameter must be of type `WithPointer` if you want to invoke the operator for objects of that type
- The parameter, if you decide to name it here, can be called anything you like
- The parameter doesn't have to be a reference; this is just more efficient
- the parameter doesn't have to be `const`; this is just safer (especially considering that it is a reference)

---

## Assignment operator
### Overloading the assignment operator:
In the implementation file:
```c++
void WithPointer::operator=(const WithPointer &other) {
  // example implementation 1
  pointer = new int(*other.pointer);
}
```
The signature is the same as in the header, except you'll need a parameter name (which can be anything you like)

---

## Assignment operator
### Overloading the assignment operator:
Example implementation 1 might cause memory leak.
```c++
void WithPointer::operator=(const WithPointer &other) {
  // example implementation 2
  if (pointer)
    delete pointer;
  pointer = new int(*other.pointer);
}
```
So we check if the pointer is currently assigned; if so, we first deallocate (`delete`) it.

(Careful, though: if you did something like this:
```c++
int i = 10;
withPointerObject o;
*o.getPointer() = &i;
```
then deleting the pointer would be invalid!)

---

## Assignment operator
### Overloading the assignment operator:
If we assign an object to itself (`WithPointer o1; o1 = o1;`), then example implementation 2 will fail: the pointer will be deallocated and then assigned to itself.
```c++
void WithPointer::operator=(const WithPointer &other) {
  // example implementation 3
  if (&other!=this) {
    if (pointer)
      delete pointer;
    pointer = new int(*other.pointer);
  }
}
```
So we first check that the object is not being assigned to itself:

`if (&other != this)`

---

## this
`this` is a special pointer that
- is available to be used when implementing member functions
- points to the instance/object that a function is called on

```c++
class MyClass {
  int member;
public:
  void setMember(int i) {
    this->member = i; // why ->?
  }
};
```
`this` can be useful when
- you want to check whether another object is the same as the one a function is called on (previous example)
- you want to access a member that is "hidden" by parameters with the same name

---

## a = b = c
There are many cases where we might want the assignment operator to return a value. The most obvious case is when we want to chain assignments:
```c++
WithPointer a, b, c(1);
a = b = c;
// ^ which means
// a = (b = c);
// i.e. a = the RESULT of (b = c)
```
For that to work, the assignment operator should return an object of the class type.

---

## a = b = c
```c++
class WithPointer {
  // ...
public:
  const WithPointer operator=(const WithPointer&);
};
```
```c++
const WithPointer WithPointer::operator=(const WithPointer &other) {
  // example implementation 4
  if (&other!=this) {
    if (pointer)
      delete pointer;
    pointer = new int(*other.pointer);
  }
  return *this;
}
```

---

class: middle
# Operator overloading

---

## Some notes about operator overloading
### 1
C++ and the compiler has no notion of correct or expected behaviour with regards to operators. In theory, you can overload the `=` operator to print out the value of the left operand, decrement the value of the right, print an insult to the user, and return a surprisingly close approximation of pi.

---

## Some notes about operator overloading
### 2
The number of **operands** of an operator cannot change. Assignment will always take one left and one right operand, and ++ will always be unary.

---

## Some notes about operator overloading
### 3
You can overload most -- but not all -- operators. Specifically, the following operators cannot be overloaded:

```
?:
.
.*
::
sizeof
```

---

## Operator overloading

The general form to overload an operator is the same as for overloading a function:
```c++
ReturnType operatorName (parameterlist);
```
The trick to overloading a given operator is:
- to know the `operatorName`, e.g. `operator=` (most operators will be `operator` and the symbol we know)
- to know which operands (l.h.s and r.h.s) are parameters and which are the calling object (for binary operators, l.h.s is usually the calling object and r.h.s the parameter)

Knowing these tricks, the binary mathematical operators `+` and `-` are straightforward to overload.
---

## Operator overloading
### Example 1: for one class
```c++
class MS {
private:
  int seconds; // seconds wrap at 60
  int minutes;
public:
  MS(int m, int s) {minutes = m; seconds = s;}
  void print() {cout << minutes << ':' << seconds << endl;}
  MS operator + (MS &);
};

MS MS::operator + (MS &rhs) {
  int s = (seconds + rhs.seconds) % 60;
  int m = minutes + rhs.minutes + (seconds + rhs.seconds) / 60;
  return MS(m, s);
}
```
```
MS ms1(1, 33);
MS ms2(2, 48);
(ms1 + ms2).print(); //4:21
```

---

## Operator overloading
### Example 2: for two classes

Suppose we add a second class, `S`, to the mix. `S` only keeps track of seconds. We want to be able to add an `S` instance to an `MS` instance.

---

## Operator overloading
### Example 2: for two classes

`S`'s class declaration looks like this:
```c++
class S {
private:
  int seconds;
public:
  S(int s) {seconds = s;}
  void print() {cout << seconds << endl;}
  S operator + (S&o);
  friend MS MS::operator +(S&);
};
```
Implementation:
```c++
S S::operator + (S &o)  {
  return S(seconds + o.seconds);
}
```

---

## Operator overloading
### Example 2: for two classes

`MS`'s class declaration gets another overloaded operator:
```c++
class MS {
private:
  int minutes;
  int seconds; // seconds are capped at 60
public:
  MS(int m, int s) {minutes = m; seconds = s;}
  void print() {cout << minutes << ':' << seconds << endl;}
  MS operator + (MS &);
  MS operator + (S&); // we added this line
};
```

The implementation for the new operator:
```c++
MS MS::operator + (S &rhs) {
  MS rhs2(0, rhs.seconds);
  return *this + rhs2;
}
```

---

## Operator overloading
### Example 2: for two classes

Note: we could have made a `getSeconds()` function to allow `MS`'s addition operator to access `S`'s private member.

---

class: middle
# End for today

---
