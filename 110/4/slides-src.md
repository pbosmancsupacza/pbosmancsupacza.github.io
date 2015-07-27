class: middle
background-image: url(./res/selfdestruct2.jpg)
.whiteTitle[Explicitly call a destructor]

---

## Explicitly call a destructor
(Based on a question from last class)

### Is it possible?
Yes.

### Should we do it?
No - unless you use something called "placement new" (you probably won't).

---

## Explicitly call a destructor
### Example
Class definition: prints something when a class is constructed or destructed; uses constructor and destructor to manage a dynamic variable
```c++
class C {
  int *x;
public:
  C(int a) {
    cout << "C::C(); // x = " << a << endl;
    x = new int;
    *x = a;
  }

  ~C() {
    cout << "C::~C(); // x = " << *x << endl;
    delete x;
  }
};
```

---

## Explicitly call a destructor
### Example (cont'd)
Client code explicitly destructs object
```c++
int main() {
  D c1(1); // constructor invoked
  c1.~D(); // destructor explicitly invoked
  return 0; // c1 goes out of scope; destructor invoked again
}
```
Output:
```
C::C(); // x = 1
C::~C(); // x = 1
C::~C(); // x = 0
*** Error in `./a.out': double free or corruption (fasttop): 0x0000000000af8010 ***
Aborted (core dumped)
```

---

class: middle
background-image: url(./res/suburbs.jpg)
# More About Classes

---

## This lecture
- Instance and static members
- Friends
- Member-wise copying

---

class: middle
background-image: url(./res/sharing.jpg)
.whiteTitle[Instance and Static Members]

---

## Instance variables

So far, we've given objects *instance variables*.

The class provides a "blueprint" of what each object will have:
```c++
class MyClass {
public:
  int instanceVariable
};
```
and each object has its own copy of those variables:
```c++
int main() {
  MyClass object1, object2;
  object1.instanceVariable = 1;
  object2.instanceVariable = 2;
  cout << object1.instanceVariable << " "
  << object2.instanceVariable << endl;
}
```
```
1
2
```

---

background-image: url(./res/dogs.jpg)

---

## Instance variables

Each object's instance variables are independent of one another.

Instance variables only belong to one *instance* of a class.

Each object has memory allocated for all its instance variables.

---

## Static variables

Different type of member variable: **Static** variable.

Only one copy exists; all objects share the same copy.

---

## Static variables

Declaration & definition:
```c++
class MyClass2 {
public:
  static int staticVariable;
};
int MyClass2::staticVariable = 0;
```
Note:
- Syntax: `static type name;`
- Definition after (outside) class definition - this is needed to create variable in memory
- Could have left out initialization; C++ defaults to 0

---

## Static variables

Client code example:
```c++
int main() {
  MyClass2 object1, object2;
  object1.staticVariable = 1;
  object2.staticVariable = 2;
  cout << object1.staticVariable << " "
  << object2.staticVariable << endl;
  // ...
}
```
Output:
```
2
2
```


In the client code, the static member's value is first set to `1`, then to `2`. All instances of `MyClass` (both `object1` and `object2`) share `staticVariable`, so:
- When `staticVariable` is changed via `object1`, it is also changed for `object1`;
- Vice versa;
- When it is printed for each object, the value is the same (`2`) for both.

---

## Static variables

Static variables exist *outside* of any instances of a class. They can be accessed before any instances have been instantiated.
```c++
int main() {
  cout << MyClass2::staticVariable << endl;
  { // block to isolate object's scope; does not affect static variabe
    MyClass2 object1;
    object1.staticVariabe = 99;
  }
  cout << MyClass2::staticVariable << endl;
  // ...
}
```

---

## Static functions

Member **functions** can also be static.

Static functions can be called outside of any class instance:
```c++
int main() {
  MyClass3::staticFunction();
  MyClass3 object1;
  //...
}
```

Static functions can also use and modify static variables outside of any instance. But they cannot access any non-static members!

---

## Static functions

The syntax to declare a static functions (in header file) is:
```c++
class MyClass {
public:
  static ReturnType FunctionName (ParameterTypeList);
};
```
And to implement (in implementation file):
```c++
ReturnType ClassName::FunctionName(Parameter1Type parameter1name, ...) {
  // implementation
}
```
(Note: no `static` in implementation header)

---
class: middle
background-image: url(./res/friends.gif)
.whiteTitle[Friends of Classes]

---

## Friends of Classes

If a member is private, it cannot be accessed by code outside the class. The concept of 'friends' allow us to make exceptions.

A friend function of a class is a function that is not a member of that class, but still has access to all the private members of that class.

---

## Friends of Classes

**Classes choose their friends.** I.e., for a function to be a friend of a class, that class must declare it as a friend.

```c++
friend ReturnType functionName (ParameterTypeList);
```

---

## Friends of Classes

Friends can be
- standalone functions
- member functions of other classes
- whole other classes

---

## Friends of Classes
### Example

```c++
class MyClass {
private:
  int privateMember;
};
```

```c++
class OtherClass {
public:
  int getPrivateMember();
};
```

Suppose `OtherClass::getPrivateMember()` has to return the value of `MyClass::privateMember`.

---

## Friends of Classes

We declare `getPrivateMember` to be a friend of `MyClass`:
```c++
#include otherclass.h

class MyClass {
private:
  int privateMember;
public:
  friend int OtherClass::getPrivateMember();
}
```
Note
- the name of the friend function includes `OtherClass::`
- we had to include the header file for `OtherClass`

---

## Friends of Classes

We don't declare `getPrivateMember()` as a friend of `MyClass` in its declaration in `OtherClass` though.
```c++
class OtherClass {
public:
  int getPrivateMember(); // unchanged
};
```

---

## Friends of Classes

Now to implement `getPrivateMember()` (`otherclass.cpp`):
```c++
int OtherClass::getPrivateMember() {
  return // ...what?
}
```

---

## Friends of Classes

```c++
int OtherClass::getPrivateMember() {
  return privateMember; // wrong!
}
```
`privateMember` is not a member of `OtherClass` so we can't do this.

---

## Friends of Classes

```c++
int OtherClass::getPrivateMember() {
  return MyClass::privateMember; // also wrong!
}
```
`privateMember` is an instance variable; it must be accessed from a class instance.

---

## Friends of Classes

The right way to do this is to pass the object that the friend function wants to access as a parameter.

Change the function declaration in `MyClass` and `OtherClass`:
```c++
class MyClass {
  //...
  friend int getPrivateMember(MyClass &);
}
```
```c++
#include myclass.h
class OtherClass {
  //...
  int getPrivateMember(MyClass &);
}
```
The `&` ensures that the object is passed by reference so that the friend function operates on the original object, not a copy.

---

## Friends of Classes

And finally, the implementation (`otherclass.cpp`):
```c++
int getPrivateMember(MyClass &object) {
  return object.privateMember;
}
```

---

## Friends of Classes

### One problem
`MyClass` must "include" `OtherClass` to declare its function a friend. `OtherClass` also "includes" `MyClass` to declare `getPrivateMember`'s parameter of type `MyClass`. Apparently, there is a circular dependency.

---

## Friends of Classes

### Easily solved
Instead of "including" `MyClass` from `OtherClass`, we can forward-declare it.

In `otherclass.h`:
```c++
// #include "myclass.h" // no longer needed
class MyClass; // forward declaration

class OtherClass {
public:
  int getPrivateMember(MyClass &);
};
```

---

## Friends of Classes

Entire other classes can be declared friends of classes:
```c++
friend class OtherClass;
```
But that means **every** function of the friend class can access every member of this class - new ones can be written in. Best practice is to give access on a per-function basis as needed, not to entire classes.

---

class: middle
background-image: url(./res/clones.jpg)
# Memberwise assignment

---

## Memberwise assignment

What happens if we initialize or assign one object to another?
```c++
int main() {
  // assume a Person class exists
  Person phlippie("Phlippie", 'a', 1);
  Person clone = phlippie;
  Person clone2;
  clone2 = clone;
  cout << clone.getName() << endl;
  cout << clone2.getName() << endl;
}
```

---

## Memberwise assignment

By default, when an object is initialized with another object, or when an object is assigned to another, C++ performs *memberwise* assignment:

Each member of the RHS object is assigned to each member of the LHS object. So the line
```c++
Person clone = phlippie;
```
causes the following to happen:
```c++
clone.name = phlippie.name;
clone.grade = phlippie.grade;
clone.position = phlippie.position;
// and so on (assuming those are the class members)
```

The same happens between `clone` and `clone2` after the statements
```c++
Person clone2;
clone2 = clone;
```

---

## Memberwise assignment

**However:** Memberwise assignment performs shallow copying! More on that in the next lecture.

---
class: middle
# End
