class:middle
Templates
---
class:middle
Templates let you create classes and functions where some of the types are generic.
---
class:middle
Templates start with the *template prefix*:
.big[.red1[`template`].blue1[`<`].green1[`class`] .blue2[`T`].blue1[`>`]]

.nop[.]

.red1[`template`] : The so-called *template prefix*. `template` is a keyword

.blue1[`<`] .blue1[`>`] : All type parameters go between these angled brackets

.green1[`class`] : The type parameter type. Can also be `typename`

.blue2[`T`] : The name of the type parameter. This can now be used in stead of types anywhere in the function. Can be named anything; traditionally T, U, V etc.
---
class:middle
To create a function template, write a template prefix, and then write a function where some of the types are the type parameters you defined in the prefix. Example:
```c++
template <class T>
void swapValues(T& l, T& r) {
   T tmp = l;
   l = r;
   r = tmp;
}
```
---
class:middle
To use a function template:
```c++
int x=0, y=27;
swapValues(x, y);

char l = 'l', r = 'r';
swapValues(l, r);
```
---
class:middle
A function template is not a function. The compiler uses the template to generate a version of the function for each type you need.
---
class:middle
You can use function templates with any type, including user-defined types, as long as the function body makes sense for that type.
---
class:middle
If you use operators or functions in the implementation, they must be overloaded/defined for the types you use it with.
---
class:middle
```c++
template<typename T>
T square(T x) {
   return x*x;
}
```
You can only use this function with types for which the `*` operator makes sense
---
class:middle
```c++
template<typename T>
T square(T x) {
   return x.foo();
}
```
You can only use this function for class types that have a `foo` function that returns a value of the class type
---
class:middle
Function templates can take more than one type parameter
```c++
template<class T, class U>
void cat(T x, U y) {
   cout << x << y << endl;
}
```
---
class:middle
Function templates can be overloaded.
---
Example 1:
class:middle
```c++
template <class T>
void foo(T) {
   cout << "foo 1" << endl;
}

template <class T>
void foo(T, T) {
   cout << "foo 2" << endl;
}

foo('x'); // foo 1
foo(-1, 1); // foo 2
```
---
class:middle
Example 2:
```c++
template <class T>
void foo(T, T) {
   cout << "foo 1" << endl;
}

template <class T, class U>
void foo(T, U) {
   cout << "foo 2" << endl;
}

foo(1, 2); // foo 1
foo(1, 2.0); // foo 2
```
---
class:middle
Class templates are classes where some of the types are generic. In a class template, member variables can be of generic types, and member functions can be function templates.
---
class:middle
To write a class template **declaration**, write the template prefix, and then declare the class, using type parameters for generic types where needed.

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
To write **definitions** for class members outside the scope of the class declaration, write a template prefix for each member, and refer to the class's scope using its template type.

```c++
template <class T>
T Vault<T>::getTheGoods(int myPassword) {
  return myPassword == thePassword ? theGoods : T();
}

template <class T>
Vault<T>::Vault(int p, T g):
   thePassword(p), theGoods(g) {
}
```
---
class:middle
To instantiate an object of a template class, you must specify the type parameters to use.
```c++
Vault<float> floatVault(123, 1.1);
```
You must also specify type parameters when you allocate memory with the `new` keyword.
```c++
Vault<bool> *boolVault = new Vault<bool>(456, false);
```
---
class:middle
You can create classes that inherit from class templates. When you refer to a class template, always include the type parameter.
```c++
template <class T>
class Parent {
	Parent() {...}
	void bar() {...}
};

template <class T>
class Child: Parent<T> {
	Child(): Parent<T>() {...}
	void foo() {
		Parent<T>::bar();
	}
};
```
