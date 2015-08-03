class: middle
# Operator overloading
## Stream and array subscript operators

---

class: middle
# Overloading the stream operators

---

## Stream operators
The stream insertion (`<<`) and extraction (`>>`) operators can be overloaded to make our classes more usable. For example, given a `Time` class, we might want the following sort of behaviour:
```c++
Time timeObject(2, 45, 00);
cout << timeObject << endl;
// should print out:
// 2:45:00
cin >> timeObject;
// could read in seconds and convert to HH:MM:SS
```

---

## Overloading stream operators
A problem arises: In the following statement,
```c++
cout << timeObject;
```
... the left-hand side operand is not an object of our class. Therefore, we cannot overload the `<<` operator as a member of our class. In fact, the `<<` operator belongs to the `ostream` class, which we cannot edit. Similarly, `>>` is part of the `istream` class.

(Note that `cout` and `cin` are instances of the `ostream` and `istream` classes, respectively.)

---

## Overloading stream operators
To overcome this problem, we use an alternative representation of binary operators. The statement:
```c++
cout << timeObject;
```
will invoke **one of** the following formal representations, depending on which one is defined:
```c++
cout.operator<<(timeObject); // either this
operator<<(cout, timeObject); // or this
```
The first representation is not (and cannot) be defined, so we should create a **standalone** operator in the form of the second representation.

---

## Overloading stream operators
We define our overloaded `<<` operator **outside** our class:
```c++
class Time {
   int h, m, s;
   // ...
};

ostream &operator << (ostream &out, Time &time) {
  out << time.h << ':' << time.m << ':' << time.s;
  return out;
}
```
In a statement like `cout << timeObject;`, `cout` will play the role of the first argument, and `timeObject` will be the second argument.

Note that the operator returns the `ostream` object (by reference); this allows us to chain calls like this:
```c++
cout << timeObject1 << " and " << timeObject2 << endl;
```

---

## Overloading stream operators
Why should the return type be by reference?

Because `ostream`'s copy constructor is `private`.

For the same reason, the `ostream`-type parameter should also be passed by reference.

---

## Overloading stream operators
Overloading the `>>` operator is similar:
```c++
class Time {
  int h, m, s;
  // ...
};

istream &operator >> (istream &in, Time &time) {
  int seconds;
  in >> seconds;
  time.s = seconds % 60;
  time.m = (seconds / 60) % 60;
  time.h = ( (seconds / 60) ) / 60;
  return in;
}
```

---

## Overloading stream operators
We need to fix one more thing before this will work. The stream operators currently try to access the `h`, `m` and `s` members of the `Time` instances they receive as parameters, but those members are **private**. How do we solve this?

---

## Overloading stream operators
The operators must be made "friends" of the `Time` class.
```c++
class Time {
  int h, m, s;
  friend ostream &operator << (ostream &out, Time &time);
  friend istream &operator >> (istream &in,  Time &time);
};
```

---

class: middle
# Overloading the array subscript operator

---

## Array subscript operator
We can overload the array subscript operator (`[]`) to give our classes array-like usage.

The `string` class has an overloaded subscript operator. For example,
```c++
string s = "Rosebud";
cout << s[5];
```
... will output `u`, and is equivalent to
```c++
string s = "Rosebud";
cout << s.operator[](5);
```

We are going to create a class that will behave like an `int` array, but with bounds-checking capabilities.

---

## IntArray class
Header file:
```c++
class IntArray {
private:
  int *array;
  int arraysize;
  void error() const;
public:
  IntArray(int);
  IntArray(const IntArray&);
  ~IntArray();
  IntArray &operator= (IntArray&);
  int size();
  int &operator[](const int&);
  int  operator[](const int&) const;
};
```

---

## IntArray class
Implementation:
```c++
#include <cstdlib>
void IntArray::error() const {
  cout << "invalid subscript" << endl;
  exit(0);
}



IntArray::IntArray(int size) {
  arraysize = size;
  array = new int[size];
  for (int i = 0; i < size; i++)
    *(array + i) = 0;
    // which means:
    // array[i] = 0;
}
```

---

## IntArray class
Implementation (continued):
```c++
IntArray(const IntArray& other) {
  arraysize = other.arraysize;
  array = new int[arraysize];
  for (int i = 0; i < size; i++)
    *(array + i) = *(other.array + i);
}



IntArray::~IntArray() {
  if (size > 0)
    delete [] array;
}
```

---

## IntArray class
Implementation (continued):
```c++
IntArray &IntArray::operator= (IntArray &other) {
    if (this != &other) {
      if (arraysize > 0) {
        delete [] array;
      }
      arraysize = other.arraysize;
      array = new int[arraysize];
      for (int i = 0; i < arraysize; i++) {
        array[i] = other.array[i];
      }
    }
}
```

---

## IntArray class
Implementation (continued):
```c++
int &IntArray::operator[](const int& i) {
  if (i < 0 || arraysize <= i)
    error();
  return array[i];
}



int IntArray::operator[](const int& i) const {
  if (i < 0 || arraysize <= i)
    error();
  return array[i];
}
```

---
