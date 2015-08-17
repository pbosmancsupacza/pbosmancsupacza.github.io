layout:true
class:middle

---


# Debugging seg faults

---

Step 1: find the fault

---

Method 1: use `cout`

---

A seg fault causes your program to crash, so `cout` statements after the line that causes the fault will not be printed

---

```c++
MyClass *obj;
cout << before << endl;
obj->member();
cout << after << endl;
```

Note: the newlines are important.

---

Method 2: use exit

---

`cout` statements can occasionally be rearranged due to compiler optimization. `exit` commands might be safer

---

```c++
#include <stdlib.h>
MyClass *obj;
obj->member();
exit(0);
```

---

Move the exit line down your code (followinf functions) until the seg fault occurs. The seg fault is caused by the line before the exit line.

---

Method 3: use gdb

---

Gnu Debugger (gdb) can help us find bugs in code.

---

To use gdb, first compile with *debug symbols*:

```
g++ myclass.cpp main.cpp -g
```

---

To start debugging, run gdb with your program name:

```
gdb ./a.out
```

---

To simply run the program:

```
run
```

Gdb will tell you on which line a seg fault occurred.

---

You can also step through your program to find bugs:

```
start
step
s
p var
Etc
```

---

Step 2: ID the cause

---

Once you have found the line that's causing the seg fault, find out *why* it's causing a seg fault.

---

A seg fault is usually caused by attempting to access invalid memory. This can happen when

- you dereference an unassigned or unallocated pointer
```c++
MyClass * obj;
obj->member();
```

- an array index is out of bounds
```c++
int* arr[] = new int[10];
for (int i=0; i<=10; i++)
   arr[i] = 0;
```

---

# Inheritance

---

Inheritance models "is a"-relationships in OO. A derived class inherits a base class's traits (members), and can also add its own.

---

Inheritance only goes one way

---

Syntax:

```c++
class DerivedClass: public BaseClass {
   ...
}
```

---

Inheritance changes the visibility of members.
- private members of the base class are inaccessible to the derived class
- other members are accessible to the derived class, but might have their visibility changed:

```
                        member:
                     +     #     -
                  -------------------
               + |   +     #     n/a
inheritance:   # |   #     #     n/a
               - |   -     -     n/a
```
---

Derived classes invoked their base classes' constructors before their bodies even start executing.

To invoke a parameterized constructor, use an intialization list:
```c++
class Derived: public Base {
   Derived(): Base(1) {}
};
```

---

An initialization list can provide constructors with any expression with any valid variables or literals. For example:
```c++
   Derived(int i): Base(i) {}
   Derived(char c): Base('x') {}
   Derived(double d): Base(d <= 23 ? d : -1) {}
```

---

Init lists go along with definitions, not declarations

```c++
class D: B {
   D() : B(i); // error!
   D() : B(i) { // correct
      //...
   }
};

```
---

Inherited functions can be *redefined*

Redefinition means that the derived class has a function with the same *signature* as one it inherited from the base class, but with a different implementation.

---

Redefinition is not the same as overloading

---

A class can inherit from any class, including classes that are already derived from other classes. This allows us to create hierarchical inheritance.

---
