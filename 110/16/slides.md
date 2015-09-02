class:middle
# Notes about questions from last lecture
---
class:middle
.big[1: Can a function with two different type parameters be called with the same type twice?]
```c++
template <class T, class U>
void foo(T t, U u) {}
```
**A:** Yes. This is valid:
```c++
foo(0,0);
```
---
class:middle
What if there is also a version that takes the same type twice?
```c++
template<class T, class U>
void foo(T, U) {
	cout << "foo 1" << endl;
}

template<class T>
void foo(T, T) {
	cout << "foo 2" << endl;
}

foo(0,0);
```
It depends on the template prefix. The above code will print `foo 2`, but...
---
class:middle
...if the code was
```c++
template<class T, class U>
void foo(T, U) {
	cout << "foo 1" << endl;
}

template<class T, class U>
void foo(T, T) {
	cout << "foo 2" << endl;
}

foo(0,0);
```
The output would be `foo 1`
---
class:middle
.big[2: If there is a generic and a specialized function, and the function is called with a type that can be converted to the specialized type, which version executes?]
```c++
template<class T>
void foo(T) {
	cout << "foo 1" << endl;
}

void foo(double) {
	cout << "foo 2" << endl;
}

foo(0);
```
**A:** The generic function is called. The output is `foo 1`.
---
background-image: url(./i/pen.jpg)
# Class templates
---
class: middle
.big[Class templates let you define a generic version of a class that will work with many datatypes]

Just like you can define *function templates*, you can also create *class templates*
---
class:middle
Recall that templates let us generalize the types that our code can work with. What types do we want to generalize in classes?
--

- Member variable types
- Function templates for member functions
---
class:middle
```c++
class IntVault {
   int thePassword;
   int theGoods;
public:
   IntVault(int p, int g): thePassword(p), theGoods(g) {}
   int getTheGoods(int myPassword) {
      return myPassword == thePassword ? theGoods : -1;
   }
};

class CharVault {
   int thePassword;
   char theGoods;
public:
   IntVault(int p, char g): thePassword(p), theGoods(g) {}
   char getTheGoods(int myPassword) {
      return myPassword == thePassword ? theGoods : -1;
   }
};
```
---
class:middle
To **declare** a class template:
1. Create a template prefix to define the type variables
2. Use the type variables in your class declaration
3. There is no step 3! No need to put a class template before every function or variable!
---
class:middle
```c++
template <class T>
class Vault {
   int thePassword;
   T theGoods;
public:
   Vault(int p, T g): thePassword(p), theGoods(g) {}
   T getTheGoods(int myPassword) {
      return myPassword == thePassword ? theGoods : T();
   }
};
```
---
class:middle
To **define** functions outside a class declaration:
1. Create a template prefix for every function
2. `<T>` follows the class name when you resolve the scope, but not when you name constructors
3. Write the function like a normal template function
---
class:middle
```c++
template <class T>
class Vault {
   int thePassword;
   T theGoods;
public:
   Vault(int, T);
   T getTheGoods(int);
};

template <class T>
Vault<T>::Vault(int p, T g):
   thePassword(p), theGoods(g) {
}

template <class T>
T Vault<T>::getTheGoods(int myPassword) {
  return myPassword == thePassword ? theGoods : T();
}
```
---
class:middle
We kept the password an `int` variable because we only wanted to change the type of info that the class stores. If we want to make the password any type, we can use a second type parameter.
---
class:middle
```c++
template <class T, P>
class Vault {
   P thePassword;
   T theGoods;
public:
   Vault(P p, T g): thePassword(p), theGoods(g) {}
   T getTheGoods(P myPassword) {
      return myPassword == thePassword ? theGoods : T();
   }
};
```
---
class:middle
To instantiate an object of a template class, you must specify the type parameters to use.
```c++
Vault<float> floatVault(123, 1.1);
```
---
class:middle
You must also specify type parameters when you allocate memory with the `new` keyword.
```c++
Vault<bool> *boolVault = new Vault<bool>(456, false);
```
---
class:middle
If a template class has more than one type parameter, just list the types you'd like to use.
```c++
Vault<char, string> charVaultWithStringPassword("pwd", '%');
```
---
class:middle
You can specify default "values" for template type parameters.
```c++
template <class T=int>
class Vault {
   // ...
};

Vault<> defaultVault(123, 456);
```
(You still need the angled brackets, just like you still need the round brackets when calling a function with default parameters)
---
class:middle
Part 2:

.big[Class templates and inheritance]
---
class:middle
If one class template is derived from another, the base class must be referenced with its type parameter.
---
class:middle
```c++
template <class T>
class Parent {};

template <class T>
class Child: Parent<T> {
};
```
---
class:middle
The type parameter in the inheritance specification
```c++
: Parent<T>
```
means that the same type is used to generate the parent class.
---
class:middle
So this is correct:
```c++
template <class T>
class Parent {};

template <class T2>
class Child: Parent<T2> {
};
```
---
class:middle
You can use this to derive from a specific instance of a class template
```c++
class IntVault: public Vault<int> {
public:
   IntVault(int p, int g): Vault(p, g) {}
};
```
---
class:middle
Or to remap type parameters to a base class
```c++
template<class T, class U>
class X {
   T a;
   U b;
};

template<class T, class U>
class Y: public X<U, T> {};
```
---
class:middle
Ordinary classes may be derived from class templates, and vice versa
```c++
template<class T>
class TemplateBase {};

class Ordinary: public TemplateBase<int> {};
// base class is a template, so
// there must be a template parameter

template<class T>
class TemplateDerived: public Ordinary {};
// base class is not a template, so
// do not specify type when inheriting.
// type can only be used for new or overloaded members.
```
---
class:middle
Part 3:

.big[Specialized class templates]
---
class:middle
Recall that specialized versions of function templates can be written:
```c++
template<class T>
void foo(T i) {}
void foo(int i) {}
void foo(char i) {}
```
---
class:middle
You can also create specialized versions of class templates. This is also called explicit or *full template specialization*.
```c++
template<class T>
class Bar {};

template<>
class Bar<int> {};

template<>
class Bar<char> {};
```
---
class:middle
We're not going to look into *partial template specialization*.
---
