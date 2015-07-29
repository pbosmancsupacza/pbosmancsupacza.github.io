class: middle
# Copy Constructors & Intro to Operator Overloading

---

## This lecture:
- Copy constructors!
- Overload the assignment operator!
- Overload other operators!

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
If a class has member variables, we have to duplicate the memberwise assignment ourselves (if we want it):
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
Why does one Elvis impersonator have access to another impersonator's private members?

Because C++ allows one object to access another's private members if
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
};
```
And this client code:
```c++
WithPointer original;
original.setPointer(new int(10));

WithPointer clone = original;
*clone.getPointer() = 11;

cout << *original.getPointer() << endl;
```
Even though we changed the value of the integer that `clone` was pointing to, it also changed for `original`. That's because memberwise assignment only does **shallow** copying of pointers.

---

## Copy constructors: A more serious use case
### Shallow copying
When copying pointers, the default behaviour is to make shallow copies. A shallow copy of a pointer is when:
- One pointer variable is copied to another
- But only the address stored in the first variable is copied to the second
- So each variable points to the same object or variable
- So changes made to the object using one of the pointers will change the value of the object as it is seen by the other pointers

```c++
int *pointer1 = new int(-1); // p1 points to an integer
int *pointer2 = pointer1; // p2 points to the same integer as p1
(*pointer2)++; // p2 increments the integer it points to
cout << *pointer1 << endl; // prints `0` because:
  // the integer that p1 points to was "also" incremented
  // ("also" because it's the same integer)
```

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

  int* getPointer() {
    return pointer;
  }

  void setPointer(int *i) {
    pointer = i;
  }
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

As with the copy constructor, C++ provides a default assignment operator that performs memberwise assignment. And, as with the copy constructor, we can provide our own version of the assignment operator. This is referred to operator overloading.

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
