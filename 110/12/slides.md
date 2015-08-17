layout: true
class: middle
---

# Redefining base class functions

---

Inheritance allows us to extend classes by adding members in derived classes.

It might also be useful to change existing member functions in derived classes.

---

```c++
class Square {
protected:
    double w;
public:
    double getArea() {
      return w*w;
    }
};

class Rectangle: public Square {
protected:
  double b;
public:
  // redefined getArea()
};
```

---

To redefine an inherited member function, simply use the same signature in the derived class

---

```c++
class Square {
protected:
    double w;
public:
    double getArea() {
      return w*w;
    }
};

class Rectangle: public Square {
protected:
  double b;
public:
  // redefined function:
  double getArea() {
    return w*b;
  }
};
```

---

A call to `getArea()` on a `Rectangle` object will invoke the redefined function.

(A call to `getArea()` on a `Sqare` object will call the original base class version.)

---

```c++
class Square {
protected:
    double w;
public:
    getArea() {
      cout << "Sqare's area: " << w*w << endl;
      return w*w;
    }
};

class Rectangle: public Square {
protected:
  double b;
public:
  // redefined function:
  double getArea() {
    cout << "Rectangle's area: " << w*b << endl;
    return w*b;
  }
};
```

---

```c++
Square s;
s.getArea();

Rectangle r;
r.getArea();
```
Output:
```
Square's area: // something
Rectangle's area: // something
```

---

Redefining is not the same as overloading

---

Overloaded function: same name, different parameter list

Redefined function: same name and parameter list, different (inheriting) class

---

```c++
class Base {
  public: void foo() {
    cout << "Base foo" << endl;
  }
};

class Derived: public Base {
public:
  void foo() {
    cout << "Derived foo" << endl;
  }
  void foo(int i) {
    cout << "Derived foo 2" << endl;
  }
};

Base b;
Derived d;
b.foo(); // "Base foo"
d.foo(); // "Derived foo"
d.foo(1);// "Derived foo 2"
```

---

# Class hierarchies

---

Classes can be derived from derived classes to create hierarchies of Inheritance

---
```c++
class A {};
class B: public A {};
class C: public B {};
class B2: public A {};
```
---

Hierarchies can be depicted using diagrams

---

background-image: url(./res/ios.gif)

---
