layout: true
class: middle

---

background-image: url(./res/travelplug.jpg)
# Polymorphism

---

Suppose we have a class hierarchy:

```c++
class Animal {
protected:
  string sound;
public:
  bool has4paws() {return true;}
  string getSound() {return "i'm such an animal";}
};

class Dog: public Animal {
public:
  // bool has4paws() is unchanged
  string getSound() {return "such bark wow";}
  void bark() {cout << getSound() << endl;}
};
```

---

The derived class
- inherits one member as-is
- redefines one member
- adds one member

---

Suppose we have a function that takes a base class object by reference:

```c++
int countPaws(Animal &a) {
  if (a.has4paws())
    return 4;
  else
    return -1; // not very useful, I know
}
```

---

The parameter of the function is of type `Animal`, so we can call the function with `Animal` objects.

```c++
Animal someAnimal;
countPaws(someAnimal);
```

---

Since a `Dog` *is an* `Animal`, we can also call the function with Dog objects.

```c++
Dog doge;
countPaws(doge);
```

---

A `Dog` object is also an `Animal` object in this context. This ability of an object to take multiple forms is called polymorphism.

---

Now suppose we have another function:

```c++
void talk(Animal &a) {
  cout << "The animal says" << a.getSound() << endl;
}
```

Remember that `getSound` was *redefined* by the `Dog` class.

---

We can call the function with a `Dog` object:
```c++
Dog doge;
talk(doge);
```
... but it won't work as you would expect. Instead of invoking the `Dog` class's `getSound()` function, the `Animal` class's function is invoked.
```
Output:
The animal says i'm such an animal
```

---

## Dynamic binding

---

The way C++ matches function calls to functions is called *binding*. In the previous example, the compiler performs *static binding*, which occurs at compile time. Even though we passed a `Dog` object to `talk()`, the parameter type is `Animal`, so the compiler decided to use `Animal`'s version of `getSound()`.

---

To get the compiler to bind the `getSound()` call in `talk()` to the `Dog` class, we have to tell C++ to bind the function *dynamically*. In dynamic binding, C++ decides which functions to bind to function calls at runtime, and so it will take the type of the object making the call into account.

---

To tell C++ to bind a function dynamically, we make the function *virtual*. For example;
```c++
class Animal {
protected:
  string sound;
public:
  bool has4paws() {return true;}
  virtual string getSound() {return "i'm such an animal";}
};
```

---

- put the keyword `virtual` before the return type
- make the function virtual in the base class; anywhere the function is called on the base class, binding is deferred to runtime
- not necessary (but maybe informative) to make redefined functions virtual; every redefinition is virtual

---

## Overriding functions

---

When a class redefines a virtual function, we say it *overrides* the function.

---

Redefinition is static. Overriding is dynamic.

---

## Polymorphism requires references or pointers.

---

If the `talk()` function took its parameter by value:
```c++
void talk(Animal a) {
  cout << "The animal says" << a.getSound() << endl;
}
```
... a polymorphic call would still be valid syntax;
```c++
Dog doge;
talk(doge); // OK
```
... but it wouldn't "work" - the call to `getSound()` would bind to the base class.

---

Polymorphism works with reference variables:
```c++
Dog doge;
Animal &animal = doge;
cout << animal.getSound(); // such bark wow
```

---

... and with pointers:
```c++
Dog *doge = new Dog;
Animal *animalPtr = doge;
cout << animalPtr->getSound();
```

---

You can assign subclasses directly to class pointers:
```c++
Animal *animalPtr = new Dog;
```

---

## Restrictions

---

### 1. Base class pointers and references only know about base class members

Even if you passed a `Dog` object to `talk()`, you couldn't call `Dog::bark()`. The parameter type is `Animal`, and Animal doesn't know about `Dog`'s member functions.

---

### 2. The "is a" relationship doesn't work in reverse

The following code is valid:
```c++
Animal *x = new Dog;
```
but the following is not:
```c++
Dog *x = new Animal;
```

---

## Virtual destructors

---

If a class can be subclassed, always make its destructor virtual. (Why?)

---

If a class with a statically-bound destructor is used polymorphically, only the base class destructor might execute.

---

```c++
class Base {
};

class Derived: public Base {
  int *dynamic;
public:
  Derived() {
    cout << "Derived()" << endl;
    dynamic = new int;
  }
  ~Derived() {
    cout << "~Derived()" << endl;
    delete dynamic;
  }
};

Base *x = new Derived;
//Outptut:
//Derived()
```

---

## `override` and `final` in C++11

---

In C++11, if you intend to override a virtual function, you can add the keyword `override` to its declaration, as follows:
```c++
class Dog {
  string getMessage() override;
};
```
If we made a mistake and `getMessage` doesn't **override** a base class function, the compiler will throw an error.

---

In C++11, if you want to prevent a function from being overriden in derived classes, you can add the keyword `final` to its declaration, as follows:
```c++
class Dog {
  string getMessage() final;
};
```
If we derive a class from `Dog` and override `getMessage()`, the compiler will thow an error.

---
