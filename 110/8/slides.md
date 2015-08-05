class: middle
### Today:
- Object conversion
- Aggregation

---
class: middle
background-image: url(./res/monk.png)
# Object conversion
---
layout: true
## Automatic type conversion
---

Say we have two variables of different primitive types:
```c++
double d;
int i = -1;
```
--

Then a statement like this
```c++
d = i;
```
causes the value of `i`, which is an integer, to be converted to a double.

--
Similarly,
```c++
d = 3.14;
i = d;
```
causes `d`, a double-type value, to be converted to an integer, with all the associated truncation.

--
C++ does this automatically and "behind-the-scenes" for primitive types.

---

This behaviour could be useful for our own class types. For example:
```c++
Time now(13, 34, 01);
int seconds = now;
```
or
```c++
Distance d(2, 130);
double kilos = d;
```

---
layout: true
## Object conversion
---

C++ has special operator functions that we can overload to implement type conersion. For example:
```c++
class Time {
  int h, m, s;
public:
* operator int();
};

Time::operator int(); {
  return s + 60*m + 3600*h;
}
```

--
Note:
- No return type
  - even though we do return something
  - because the return type is determined by the operator and cannot be changed
--

- Name is `operator` and the type
--

- No parameters

---

Note that, for statements like these:
```c++
int seconds = 3650;
Time then = seconds;
```
or these:
```c++
double kilos = 24.1;
Distance to;
to = kilos;
```
C++ will use an appropriately-overloaded constructor or assignment operator, which is not the same as type conversion.

---

### Another example:
```c++
class Fraction {
  int numerator, denominator;
public:
  // ... constructors, getters, setters, etc ...
  operator int();
  operator double();
  operator string();
};
```
---
layout: true

##Object conversion
### Another example:
---

```c++
Fraction::operator int() {
  if (denominator == 0) {
    cout << "Division by zero!" << endl;
    exit(0);
  }
  return numerator / denominator;
}
```
--

Why does the return statement work?

The division operator is overloaded to return a (truncated) `int` value.

---

This implementation will not work as expected:
```c++
Fraction::operator double() {
  // error checking etc...
  return numerator / denominator;
}
```
--

The division in the return statement will result in a truncated `int` value, just like in the `int` conversion operator.

This `int` value will then be converted to a still-truncated `double` when it is returned.

---

Instead, we can do this:
```c++
Fraction::operator double() {
  // error checking etc...
  double d = numerator;
  return d / denominator;
}
```
--

A differently-overloaded division operator is used that results in a `double` value.

---

We can also convert to `string`-type objects:
```c++
#include <sstream>
using namespace std;

Fraction::operator string() {
  stringstream ss;
  ss << numerator << '/' << denominator;
  return ss.str();
}
```
--

... so it stands to reason that we can convert to any class types.
---

Back to the header file:
```c++
class Fraction {
  int numerator, denominator;
public:
  // ... constructors, getters, setters, etc ...
  operator int();
  operator double();
  operator string();
  operator OurOwnClassType(); // suppose this type exists
};
```
--

And a hypothetical implementation:
```c++
Fraction::operator OurOwnClassType() {
  return OurOwnClassType(numerator, denominator);
}
```

---
layout: true
## Object conversion
### Side note
---

Suppose there are two classes, called `One` and `Two`, where
- `One` has a conversion operator that converts objects to type `Two`
- `Two` has a constructor that takes a `One`-type object as a parameter

---


```c++
class One {
  // ...
  operator Two();
};

class Two {
  // ...
  Two(One);
};
```
--

Which would get called by the following code?
```c++
One one;
*Two two = one;
```
--

**Answer:** The code won't compile because it is an **ambiguous conversion**.

---
layout: true
## Object conversion
---

Using conversion, our `Fraction` class can be printed to `ostream` objects without the need of overloaded stream operators.
--


**But**:

If C++ doesn't know which conversion operator to use, we have to specify. For example:
--

```c++
Fraction notQuitePi(22, 7);
cout << (string)notQuitePi << endl;
// or
cout << string(notQuitePi) << endl;
// or
cout << (int)notQuitePi << endl;
// etc
```
--

The *logic* behind this is that different conversions can cause different things to be printed, as in our case. But even if every conversion operator will print the same thing, C++ will complain about ambiguous overloads unless we're specific.

---

layout: true
class: middle
background-image: url(./res/engine.png)
# Aggregation
---
---
layout: true
## Aggregation
---

**Aggregate**: a whole formed by combining several separate elements
--


So far, our member functions have been (mostly) of primitive types:
```c++
class MyClass {
  int member1;
  char member2;
  string member3;
};
```
--

(One of these is not like the others...)

---

Member variables can be of any type, including class types that we define.
```c++
class TypeA {};
class TypeB {
  TypeA memberVariable;
};
```

--

Aggregation is when a class is comprised of instances of another class.

--

Sometimes, it makes sense to build classes out of other classes. For example, a house contains doors, windows, a roof, etc.

---

Some notes:
- For now, make sure all your classes have default constructors
--

  - If that's not possible, look up "initializer lists"
--


... and that's it.

---
layout: true
class: middle
# The end
---
