layout: true
class: middle
---
# Inheritance

---

Real-world classes are often generalized or specialized versions of other classes

---
background-image: url(./res/transport.jpg)
---

Specialized classes have an "*is a*"-relationship with generalized classes

---

A Shiba Inu is a dog

A train is a vehicle

A square is a shape

A triangle is an instrument

---

The "is a"-relationship is one-sided

---

A dog is not a Shiba Inu

A vehicle is not a train

A shape is not a square

An instrument is not a triangle

---

Specialized classes have all the same attributes as their generalized versions, and also add their own attributes

---

All dogs have ears (so Shiba Inu also have ears)

All vehicles can transport people

All shapes have areas

All instruments have pitch ranges

---

Shiba Inu also have memes

Trains also have conductors

Circles also have radii

Triangles also have mallets

---

In C++, "is a"-relationships are implemented with **inheritance**

---

The specialized class *inherits* from the generalized class.

The inheritee is called the **base class** or **parent class**

The inheritor is called the **derived class** or **child class**

---

The derived class *is a* base class

---

A derived class inherits all the member functions and member variables of its base class

A derived class can also have its own members added

---

This base class has some members:
```c++
// Base class:
class Vehicle {
   int speed;
public:
   int getSpeed();
};
```

...and the derived class adds more members:
```c++
// Derived class:
class Skateboard: public Vehicle {
public:
   void stunt();
};
```

---

The derived class has access to its own members as well as those of its base class:

```c++
int main() {
   Skateboard board;
   board.stunt(); // own member
   int s = board.getSpeed(); // inherited member
}
```

---

# Syntax

---

A base class doesn't have any special syntax

.smaller[(Any class can be a base class - even a derived class)]

---

```c++
class BaseClass {
  // ...
};
```

---

A derived class must tell the compiler
- which base class it is derived from, and
- how to adapt the visibility of the inherited members

---

```c++
class DerivedClass: public BaseClass {
  // ...
};
```

---

.mono[class .blue1[DerivedClass] .red1[:] .green1[public] .blue2[BaseClass] {]

```

```
.smaller[
.mono[.blue1[DerivedClass]]: this class's name

.mono[.red1[:]]: a colon indicates that we are going to tell the compiler which base class(es) to inherit from

.mono[.green1[public]]: *base class access specification* (more on that later)

.mono[.blue2[BaseClass]]: The name of the base class to inherit from
]

---

Remember, "is a" is a one-sided relationship.

Derived classes can access their base classes' members, but base classes cannot access their derived classes' members.

---

# Access to inherited members

---

In this:

```c++
class BaseClass {
private:
   void privateFoo();
public:
   void publicFoo();
};

class DerivedClass: public BaseClass {
public:
   void foo() {
      publicFoo();  // OK
      privateFoo(); // Bad!
   }
};
```

---

...`DerivedClass` has access to `BaseClass`'s public members, but **not** to its private members

---

Private members are inaccessible to client code **and** to derived classes

---

There is a third member access specifier: **protected**

---

Protected members are not accessible to client code, but they are accessible to derived classes

In UML, protected access is demarcated with a `#`

---

```c++
class BaseClass {
protected:
   void protectedFoo();
};

BaseClass baseObject;
baseObject.protectedFoo(); // BAD!

class DerivedClass: public BaseClass {
public:
   void foo() {
      protectedFoo(); // OK
   }
};
```

---

What about the visibility of inherited members to clients of derived classes?

---

```c++
class BaseClass {
private: void privateFoo();
protected: void protectedFoo();
public: void publicFoo();
};

class DerivedClass: public BaseClass {
   // ...
};

DerivedClass derivedObject;
derivedObject.privateFoo(); // valid?
derivedObject.protectedFoo(); // valid?
derivedObject.publicFoo(); // valid?
```

---

Inherited members that were **private** in the base class are **inaccessible** to clients of the derived class

```c++
derivedObject.privateFoo(); // NOT valid
```

---

**Protected** members of the base class are **inaccessible** to clients of the derived class
```c++
derivedObject.protectedFoo(); // NOT valid
```

---

**Public** members of the base class **can be** accessible to clients of the derived class, depending on the *base class access specification*

---

When a class is derived from a base class, the visibility of the members changes.

A class can be inherited publicly, protectedly, or privately.

---

If a base class is inherited **publicly**:
```c++
class DerivedClass: public BaseClass {};
```
- **public** members of the base class are **public** members the derived class
- **protected** members of the base class are **protected** members of the derived class
- **private** members of the base class are inaccessible to the derived class

---

```c++
class BaseClass {
private: void privateFoo();
protected: void protectedFoo();
public: void publicFoo();
};

class DerivedClass: public BaseClass {
};

DerivedClass derivedObject;
derivedObject.privateFoo(); // BAD
derivedObject.protectedFoo(); // BAD
derivedObject.publicFoo(); // OK
```

---

A derived member's access is also important when you derive a class from a derived class

---

```c++
class BaseClass {
private: void privateFoo();
protected: void protectedFoo();
public: void publicFoo();
};

class DerivedClass: public BaseClass {
};

class DerivedDerivedClass: public DerivedClass {
   void foo() {
      privateFoo(); // BAD
      protectedFoo(); // OK
      publicFoo(); // OK
   }
};
```

---

If a base class is inherited **protectedly**:

```c++
class DerivedClass: protected BaseClass {};
```

- **public** members of the base class are **protected** members of the derived class
- **protected** members of the base class are **protected** members of the derived class
- **private** members of the base class are inaccessible to the derived class

---

```c++
class BaseClass {
private: void privateFoo();
protected: void protectedFoo();
public: void publicFoo();
};

class DerivedClass: protected BaseClass {
};

DerivedClass derivedObject;
derivedObject.privateFoo(); // BAD
derivedObject.protectedFoo(); // BAD
derivedObject.publicFoo(); // BAD

class DerivedDerivedClass: public DerivedClass {
   void foo() {
      privateFoo(); // BAD
      protectedFoo(); // OK
      publicFoo(); // OK
   }
};

```

---

If a base class is inherited **privately**:

```c++
class DerivedClass: private BaseClass {};
```

- **public** members of the base class are **private** members of the derived class
- **protected** members of the base class are **private** members of the derived class
- **private** members of the base class are inaccessible to the derived class

---

```c++
class BaseClass {
private: void privateFoo();
protected: void protectedFoo();
public: void publicFoo();
};

class DerivedClass: private BaseClass {
};

DerivedClass derivedObject;
derivedObject.privateFoo(); // BAD
derivedObject.protectedFoo(); // BAD
derivedObject.publicFoo(); // BAD

class DerivedDerivedClass: public DerivedClass {
   void foo() {
      privateFoo(); // BAD
      protectedFoo(); // BAD
      publicFoo(); // BAD
   }
};

```

---
class:center
```
                    member:
                  +     #     -
                  -------------------
               + |   +     #     n/a
inheritance:   # |   #     #     n/a
               - |   -     -     n/a
```

---

# Constructors

---

When a derived-class object is created, its base class constructor is also invoked

---

The base class constructor is invoked **before** the derived class constructor

---

```c++
class BaseClass {
public:
   BaseClass() {
      cout << "Base constructor" << endl;
   }
};

class DerivedClass {
public:
   DerivedClass() {
      cout << "Derived constructor" << endl;
   }
};

DerivedClass object;
```
Output:
```
Base constructor
Derived constructor
```
---

If a class is derived from a derived class, the top-level base class is constructed first

---

```c++
class BaseClass {
public:
   BaseClass() { cout << "Base" << endl; }
};

class DerivedClass {
public:
   DerivedClass() { cout << "Derived" << endl; }
   }
};

class DerivedDerivedClass {
public:
   DerivedDerivedClass() {
      cout << "Derived Derived" << endl; }
   }
};

DerivedDerivedClass object;
```

---
Output:

```
Base
Derived
Derived Derived
```

---

If we don't specify anything, the default constructor is invoked.

---

This might not be our desired behaviour if
- base class doesn't have default constructor
- base class has a parameterized constructor that we want to invoke

---

To specify which constructor to invoke, use an *initializer list*

```c++
class DerivedClass {
public:
   DerivedClass() : BaseClass(10) {
      // ...
   }
};

```

---

.mono[.blue1[DerivedClass()] .red1[:] .green1[BaseClass(10)] {

}]

```

```

.mono[.blue1[DerivedClass()]]: The name of the derived class's constructor

.mono[.red1[:]]: A colon to indicate the start of the initializer list

.mono[.green1[BaseClass(10)]]: An explicit call to the base class's constructor

Followed by the body of the constructor
---

The base class's default constructor can be invoked explicitly:

.mono[.blue1[DerivedClass()] .red1[:] .green1[BaseClass()] {

}]

---

Parameterized constructors can be invoked with literals, variables that are in scope (parameters or global variables), and expressions:

.mono[.blue1[DerivedClass()] .red1[:] .green1[BaseClass('x')] {}]

.mono[.blue1[DerivedClass(int i)] .red1[:] .green1[BaseClass(i + 1)] {}]

.mono[.blue1[DerivedClass(char c)] .red1[:] .green1[BaseClass(c=='a'?0:1)] {}]

---

This notation is only used in the **definition** of the constructor, not the declaration:

```c++
class DerivedClass {
public:
   DerivedClass(); // declaration
};

// definition:
DerivedClass::DerivedClass() : BaseClass() {
   // ...
}
```

---

# Destructors

---

Each classes only has a default destructor, so it's not necessary to invoke them specifically

---

When a derived class is destructed, its own destructor is invoked first, and then that of its base class.

---

```c++
class BaseClass {
public:
   ~BaseClass() { cout << "Base" << endl;}
};

class DerivedClass {
public:
   ~DerivedClass() { cout << "Derived" << endl;}
};

{
   DerivedClass object;
}
```
Output:
```
Derived
Base
```

---

# More on initializer lists

---

Initializer lists can be used to
- explicitly invoke the base class constructor
- explicitly initialize member variables

---

Recall that *aggregation* means a class has member variables of other class types:
```c++
class Part {};
class Whole {
   Part member;
};
```

---

...and that, if we do not specify otherwise, the member objects' default constructors are invoked before the aggregate class's constructor's body:
```c++
class Part {
public:
   Part() { cout << "Part" << endl; }
};

class Whole {
   Part member;
public:
   Whole() { cout << "Whole" << endl; }
};

Whole object;
```
Output:
```
Part
Whole
```

---

It might be necessary to invoke the constructors of the member objects explicitly
- Member objects might not have default constructors
- We might need to invoke a parameterized constructor

---

Class members can be initialized using initializer lists:
```c++
class Whole {
   Part member;
public:
   Whole() : member(1) {}
};
```

---

Primitive-type members can also be initialized in this way:
```c++
class Aggregate {
   int i;
   char c;
   string s;
public:
   Aggregate():
      s('hello world') {
      i(-1),
      c('!'),
         // ...
      }
};
```

---

Members to initialize are separated by commas.

The order in which members are initialized is determined by the order they are **declared as class members**, not the order they are listed in the initializer list.

---

An initializer list can contain invocations for base class constructors and member initializations:

```c++
class DerivedAggregate : public Base {
   Part member1, member2;
public:
   DerivedAggregate(int i, int j, int k):
      member1(i),
      Base(k),
      member2(j) {
         // ...
      }
};
```
The order doesn't matter

The base class is constructed first, then the members are initialized in declared order
---

Base class members **can't** be initialized in this way:

```c++
class BaseClass {
protected: int baseVar;
};

class DerivedClass {
   DerivedClass():
      baseVar(0), // invalid
      BaseClass::baseVar(0) // also invalid
   {

   }
};
```
because they are not *technically* members of the derived class
---

# End
