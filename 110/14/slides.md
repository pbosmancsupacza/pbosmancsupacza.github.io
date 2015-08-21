class: middle
background-image: url(./res/glove.jpg)
# Exceptions

---
class: middle

Suppose you are implementing basic division:

```c++
double num, den;
cin >> num >> den;
double quot = num / den;
```

This code is vulnerable to division-by-zero errors

---
class: middle

You can implement basic error-checking using control statements:

```c++
if (den == 0)
  cout << "DIVISION BY ZERO!" << endl;
else
  quot = num / den;
```

But if an error is prevented, the quotient isn't set.

---
class: middle

If the above is part of a function, what should be returned when there is an error?

```c++
double divide(double num, double den) {
  if (den == 0) {
    cout << "DIVISION BY ZERO!" << endl;
    return -1;
  }
  else {
    quot = num / den;
    return quot;
  }
}
```

Any value you return can be interpreted as a valid result.

---
class: middle

Instead of using the result of an operation to signal an error, we can use a different channel.

C++ provides such a channel through the concept of *exception handling*.

---
class: middle

The concept:
1. An *exception* is a value that signifies that an error occurred
2. If an error occurs, an exception is *thrown*
1. Code that might throw an exception is *tried*
2. If the tried code throws an exception, the exception is *caught* by other code that handles the error

---
class: middle

### 1. What is an *exception*?
Any value, of any type, becomes an exception when it is *thrown*.

---
class: middle

### 2. How to *throw* an exception
To throw a value, use the keyword `throw`, followed by the value.

---
class: middle

For example:
```c++
throw "This string is an exception";
```
or:
```c++
throw 1;
```
or:
```c++
float inaccuratePi = 3.14;
throw pi;
```

---
class: middle

In context:
```c++
double divide(double num, double den) {
  if (den == 0)
    throw "division by zero";
  else
    return num / den;
}
```
--
(Note that, when the exception is thrown, nothing is returned)
---
class: middle

### 3. How to *try* code
If a piece of code might throw an exception, put that code in a `try`-block, followed by everything that relies on successful execution of the code.

---
class: middle

.nop[]
Example:
```c++
double num, den;
cin >> num >> den;
try {
  double quot = divide(num, den);
  cout << "result: " << quot << endl;
}
// catch goes here...
```

---
class: middle

### 4. How to *catch* an exception
An exception is caught by a `catch`-block. Error-handling code is written in the catch-block, and gets executed whenever an exception is caught.

---

class: middle
.nop[]
NB: `try`- and `catch`-blocks must go together.

Every `try`-block must be directly followed by at least one `catch`-block.

---
class: middle
.nop[]
Example:
```c++
try
{
  double quot = divide(num, den);
  cout << "result: " << quot << endl;
}
catch(string s) {
  cout << "division by 0 error!";
}
```

---
class: middle

If an exception is thrown in a try-block, control is immediately transferred to the first type-matching catch-block. The rest of the try-block is skipped. After the catch-block is done, control continues after the try-catch structure.

If no exception is thrown, the whole try-block is completed, and no catch-block code is run.

---
class: middle

Longer example:
```c++
#include <stdlib.h>
double parse(string value) {
  double result = atof(value);
  if (value == 0.0)
    throw 0;
  return value;
}

double divide(double num, double den) {
  if (num == 0)
    throw "div by zero";
  return num/den;
}
```

---
class: middle

```c++
try {
  string input;
  getline(cin, input);
  double den = parse(input);
  cout << "got denominator: " << den << endl;
  double result = divide(1, den);
  cout << "result: " << result;
} catch (int) {
  cout << "failed to parse" << endl;
} catch (string s) {
  cout << s << endl;
}
cout << "done." << endl;
```

---
class: middle
.nop[]
Notes:
- different functions throw different types
- different catch-blocks catch different types
- first catch-block has no named parameter
- second catch-block uses named parameter
- "done" is always printed

---
class: middle

Exceptions can be thrown outside of try-catch blocks.

Try-catch blocks don't have to catch all exceptions (might be wrong type).

---
class: middle

If an exception is not caught in the current scope, it is thrown to a higher scope. This is called *unwinding the stack*. If there is no higher scope, the program quits.

---
class: middle

```c++
void foo() {
  throw 1; // thrown to bar
}

void bar() {
  try {
    foo(); // throws 1
  } catch(char) { // doesn't catch 1
  } // 1 is not handled, so it is thrown to baz
}

void baz() {
  bar(); // 1 is not handled; thrown to main
}

int main() {
  try {
    baz();
  } catch (int) { // 1 is caught and handled
    cout << "caught an int";
  }
  return 0;
}
```

---
class: middle

```c++
void foo() {
  throw 1;
}

void bar() {
  try {
    foo();
  } catch(char) {
  }
}

void baz() {
  bar();
}

int main() {
  baz(); // 1 is not caught and handled, so the program quits
  cout << "something"; // not printed!
  return 0;
}
```

---
class: middle

A catch-block can re-throw an exception:

```c++
//...
catch(int) {
  throw;
}
```
---
class: middle

An exception is re-thrown to the outer scope, **not** to other catch blocks in the same structure.

```c++
void foo() {
  try {
    throw 1;
  } catch (int) {
    cout << "foo caught" << endl; // will print
    throw;
  } catch (int) {
    cout << "foo caught again" << endl; // won't print
    throw;
  }
}

void bar() {
  try {
    foo()
  } catch (int) {
    cout << "bar caught" << endl; // will print
  }
}
```

---
class: middle

You can throw class objects

---
class: middle

E.g.
```c++
class MyClass {};

try {
  MyClass x;
  throw x;
} catch (MyClass) {}
```

---
class: middle

.nop[]Careful: Catch-blocks work polymorphically

```c++
class Base {};
class Derived: public Base {};

try {
  throw Derived();
} catch(Base) {
  cout << "Base" << endl;
} catch (Derived) {
  cout << "Derived" << endl;
}
// will print "Base"
```
If a base-class catch block is before a derived-class catch block, then the derived-class catch block will never run!

---
class: middle

Depending on your needs, it might be sensible to create specific exception classes.

---
class: middle
.nop[]Example:

```c++
class DivisionByZeroException {};

double divide(double num, double den) {
  DivisionByZeroException z;
  if (num == 0)
    throw z;
  return num/den;
}

try {
   double result = divide(num, den);
   cout << "result: " << result;
} catch (DivisionByZeroException e) {
   cout << "failed to parse" << endl;
}
```

---
class:middle

You can even equip your custom classes to handle exceptions better

```c++
class ExceptionClass {
   string message;
public:
   ExceptionClass(string s): message(s) {}
   string getMessage() {return message;}
};

try {
   throw ExceptionClass("division by zero");
} catch (ExceptionClass e) {
   cout << e.getMessage() << endl;
}
```

---
