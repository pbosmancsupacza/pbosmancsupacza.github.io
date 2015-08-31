background-image: url(./res/templ.jpg)
# Function templates

---
class: middle
.big[A function template is a generic function that can work with many different data types]

---
The only differences between this function...
```c++
void swapValues(int& l, int &r) {
   int tmp = l;
   l = r;
   r = tmp;
}
```

--

and these...

```c++
void swapValues(char& l, char &r) {
   char tmp = l;
   l = r;
   r = tmp;
}

void swap(MyClass& l, MyClass &r) {
   MyClass tmp = l;
   l = r;
   r = tmp;
}
```

--

are the datatypes they use.
---

class: middle
.big[Function templates let us factor out the data types and keep everything else]

---
class: middle
Something like...
```c++
void swapValues(__ l, __ r) {
   __ tmp = l;
   l = r;
   r = tmp;
}
```

---

class:middle
.big[Function templates use a *type parameter* instead of an actual type]

---

class:middle
.big[]Example:
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
.big[.red1[`template`].blue1[`<`].green1[`class`] .blue2[`T`].blue1[`>`]]

.nop[.]

.red1[`template`] : The so-called *template prefix*. `template` is a keyword

.blue1[`<`] .blue1[`>`] : All type parameters go between these angled brackets

.green1[`class`] : The type parameter type. Can also be `typename`

.blue2[`T`] : The name of the type parameter. This can now be used in stead of types anywhere in the function. Can be named anything; traditionally T, U, V etc.

---
class:middle
.big[]
Using it:
```c++
int x=0, y=27;
swapValues(x, y);

char l = 'l', r = 'r';
swapValues(l, r);
```

---
class:middle
.big[A function template is not a function]

---
class:middle
The compiler uses the function template to generate a function instance for every type it is used for.
---
class:middle
This code
```c++
int x=0, y=27;
swapValues(x, y);
```
causes the compiler to generate this function instance
```c++
void swapValues(int& l, int &r) {
   int tmp = l;
   l = r;
   r = tmp;
}
```
---
class:middle
and this code
```c++
char l='l', r='r';
swapValues(l, r);
```
causes the compiler to generate this function instance
```c++
void swapValues(char& l, char &r) {
   char tmp = l;
   l = r;
   r = tmp;
}
```
---
class:middle
.big[`T` can also stand in for user-defined types]
---
class:middle
This code
```c++
class MyClass {
   // ...
};

MyClass object1, object2;
swapValues(object1, object2);
```
causes the compiler to generate this function instance
```c++
void swapValues(MyClass& l, MyClass &r) {
   MyClass tmp = l;
   l = r;
   r = tmp;
}
```
---
class:middle
.big[If a template function is never used, no function instances are generated and no memory is used]
---
class:middle
You can use a parameter type as a return type
```c++
template<typename T>
T square(T x) {
   return x*x;
}
```
```c++
template<class T>
T foo(T x, T y, T z) {
   return x < y ? z : x;
}
```
---
class:middle
.big[Re: operators in template functions]

If a template function uses an operator, you can only call that function for types for which the operator is overloaded.
---
class:middle
This function
```c++
template<class T>
bool less(T l, T r) {
   return l < r;
}
```
can be called for most primitive types (int, double, char, etc)
```
float f1 = 200, f2 = 3.14f;
bool result = less(f1, f2);
```
---
class:middle
but if a function instance is generated for a type for which the operator is not overloaded, a compile error is caused.
```c++
class MyClass {};

template<class T>
bool less(T l, T r) {
   return l < r
};

MyClass x, y;
less(x,y);
```
---
class:middle
The compiler determines whether a function is valid based only on the specific function instances that it generated. You can exploit this to create generic functions that work equally well on completely unrelated classes, as long as each class exposes the interface needed by the function.
---
class:middle
```c++
class Class1 {
public: string val;
};

class Class2 {
public: bool val;
};

class Class3 {
public: char val;
};

template <class T>
void foo(T x) {
   cout << x.val << endl;
}
```
---
class:middle
```c++
class Class1 {
public: void foo() {
      cout << "Class1::foo()" << endl;
   }
};

class Class2 {
public: void foo() {
      char c;
      cin >> c;
   }
};

class Class3 {
public: int foo() {
      return 1;
   }
};

template <class T>
void foo(T x) {
   x.foo();
}
```
---
class:middle
.big[Function templates can take more than one type parameter]
---
class:middle
```c++
template<class T, class U>
void cat(T x, U y) {
   cout << x << y << endl;
}
```
---
class:middle
.big[Function templates can be overloaded]

Differently-overloaded function templates can be distinguished by the number of type parameters, or by the "types" of the type parameters.
---
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
.big[Generic functions can be overridden by specifically-typed functions]
---
class:middle
```c++
template <class T>
void foo(T) {
	cout << "generic foo" << endl;
}

void foo(int) {
	cout << "int foo" << endl;
}

foo('x'); // generic foo
foo(123); // int foo
```
---
