# Constructors and Destructors
## and arrays of objects and UML
### and so on

# First: Some Naming Conventions

#### Classes:
	UpperCamelCase (a.k.a. PascalCase)
#### Variables, object, functions:
	camelCase
#### Header file names:
	className.h
#### Implementation file names:
	className.cpp

# Constructors

## I can haz initialization?
In the `MessagePrinter` class, the `message` variable isn't initialized.
```c++
class MessagePrinter() {
private:
	string message; // don't allow clients to see/change the internal data
public:
	void printMessage(); // only allow clients to print the data
};
```
How can we solve this?

## Constructors
To let us initialize objects for real, C++ has something built in called *constructors*.

Constructors are special types of member functions.

They are called automatically (and always) when an object is instantiated.

We use them as initialization routines.

Constructor Example:
```c++
class Noisy {
public:
	Noisy(); // the constructor
};
```
```c++
Noisy::Noisy() {
	cout << "Click!" << endl;
}
```
Every time a `Noisy` object is created, the constructor (called `Noisy`) is called, and the message `Click` is printed.

`main.cpp`
```c++
int main() {
	cout << "about to instantiate..." << endl;
	Noisy n1;
	Noisy n2;
	Noisy n3;
	cout << "finished instantiating objects." << endl;
	return 0;
}
```
This will output:
```bash
about to instantiate...
Click!
Click!
Click!
finished instantiating objects.
```
Each object called the constructor when it was instantiated.

- Constructors have no return type. (Why?)
- The name of a constructor is always the same as the name of the class.

The general form is:
```c++
class ClassName {
	ClassName( /*parameterList1*/ ); // constructor 1
	ClassName( /*parameterList2*/ ); // constructor 2
	// ...
};
```
```c++
// constructor 1:
ClassName::className( /*parameterList1*/ ) {
	// implementation...
}
// constructor 2:
ClassName::ClassName( /*parameterList1*/ ) {
	// implementation...
}
```

- a class can have multiple constructors
- constructors can
  - have parameters
  - have multiple parameters
  - have default parameters
  - be declared inline
  - and be overloaded.


## The Default Constructor
The **default constructor** is the constructor with no parameters.
```c++
class ClassWithDefaultConstructor {
	ClassWithDefaultConstructor() {
		cout << "default constructor called!" << endl;
	}
};
```
The default constructor is called when an object is instantiated with no parameters.
```c++
int main() {
	ClassWithDefaultConstructor object;
	// prints:
	// default constructor called!
	return 0;
}
```

If you do not write **any** constructors for a class, C++ "writes" a default constructor with no implementation. So:
```c++
class C {
};
```
is equivalent to
```c++
class C {
public:
	C() {}
};
```
Note that this will not happen if you create your own constructors, even if you don't create a default constructor.

Suppose a class called `C` exists. Will the following code invoke the default constructor?
```c++
C *c;
```

## Parameterized Constructors
Constructors can accept parameters. The syntax is like normal functions (just no return value).
```c++
class C {
private:
	int val;
public:
	C();
	C(int v) {val = v}
};
```
Parameterized constructors are *explicitly* invoked. For example:
```c++
int main() {
	C c(-1); // a new C object is created and
			// its member variable val is initialized to -1
}
```

Another example:
```c++
class Greeter {
private:
	string message, firstname, lastname;
public:
	Greeter(string m, string f, string l) {
		message = m;
		firstname = f;
		lastname = l;
	}
	Greeter(string f, string l) {
		message = "Howdy";
		firstname = f;
		lastname = l;
	}
	void greet() {
		cout << message << ", " << firstname << " " << lastname;
	}
};
```

## Overload!
Writing new versions of functions (using different parameter lists) is called *overloading*. As you can see in the previous examples, constructors can be overloaded just like functions.

It's also valid to overload a class' member functions.


## Default values for parameters
```c++
class Greeter {
private:
	string message, firstname, lastname;
public:
	Greeter(string f, string l, string m = "Howdy") {
		message = m;
		firstname = f;
		lastname = l;
	}
	void greet() {
		cout << message << ", " << firstname << " " << lastname;
	}
};
```

## Classes with no default constructor
In the previous example, we defined some constructors but no **default** (no parameters) constructor. If we try and invoke the default:
```c++
Greeter g;
```
a compile error will result.

## ... But in C++11:
In C++11, a default constructor can be **explicitly** created or omitted:
```c++
class Greeter {
	// ...
public:
	Greeter() = default; // force generation
	// OR
	Greeter() = delete; // prevent generation
};
```

## Invoking default vs parameterized constructors
Note that invoking the default constructor looks different than invoking other constructors:
```c++
Greeter g1; // default; no brackets!
Greeter g2("Yo", "Swag", "Money");
```
If we tried to invoke the default in the same way we invoke other constructors:
```c++
Greeter g1();
```
it will fail or behave bizarrely. Why?

## All default values = default constructor
If a constructor has parameters, but each has a default value, it is still the default constructor.
```c++
class C {
public:
	C(int v1 = 1, int v2 = 2) {}
};

C c; // valid!
```

## But thERE CAN BE ONLY ONE
A class can only have **one** default constructor. Invoking the default constructor shouldn't leave the compiler wondering whether to invoke the constructor with no parameters, or one with all default parameters (even worse if there are several of those!).

# Destructors

C++ provides another special type of function, called destructors. A destructor is automatically (always) called when an object is destroyed. (When's that?)

The name of a destructor is a tilde (`~`) plus the name of the class. E.g.:
```c++
class ItsGonnaBlow {
public:
	~ItsGonnaBlow();
};
```

Some things about destructors:
- No return type (just like constructors)
- No parameters (unlike constructors)
- So, also no overloading - only one destructor per class


## When are they called?
An object is destroyed when it goes out of scope. Suppose a destructor prints a message when its object is destroyed:
```c++
class ItsGonnaBlow {
	string name;
public:
	ItsGonnaBlow(string n) {name = n;}
	~ItsGonnaBlow() {	cout << name << ": Boom!" << endl;}
}
```

The following code:
```c++
int main() {
	ItsGonnaBlow o1("1");
	if (true) {
		ItsGonnaBlow o2("2");
	}

	{
		ItsGonnaBlow o3("3");
	}
	return 0;
}
```
will print the following:
```bash
2: Boom!
3: Boom!
1: Boom!
```


## But why
Destructors come in handy when objects maintain memory. Suppose a constructor allocates memory as follows:
```c++
SomeClass::SomeClass() {
	int *someVariable = new int;
}
```
then each object of that type allocates memory when it is instantiated. If that memory is not deallocated by the time the object goes out of scope, we have a *memory leak*.

Luckily, the destructor is called *the moment* an object goes out of scope, so we'll let the destructor deallocate the memory:
```c++
SomeClass::~SomeClass() {
	delete someVariable;
}
```
It's good practice to let destructors undo what constructors did.

## When does it get called for dynamically allocated objects?
If we dynamically allocate an object, we must remember to `delete` it.
```c++
ItsGonnaBlow *dynamicObject = new ItsGonnaBlow();
// ...do some stuff...
delete dynamicObject;
```
The destructor is invoked when the object is deleted.

# Other stuff about classes & objects

## Private member functions
Member functions can be private.

Private member functions do not form part of a class' public interface; clients cannot use them.

Where would we need them?


## Arrays of Objects
You can make arrays of class objects. The objects will all be instantiated using their constructors. How you declare an array will determine how the objects are created.

### Invoke default constructor
To create an array of objects and create each object using its default constructor:
```c++
int arraySize = 99;
ClassWithDefaultConstructor arrayOfObjects[arraySize];
```
If a class doesn't have a default constructor, this won't work; you'll have to pass arguments to one the class's parameterized constructors.

### Invoke constructor with ONE parameter
To create an array of objects and create each object using a parameterized constructor, you must provide the parameter to each constructor:
```c++
ClassWithParameterizedConstructor arrayOfObjects[] = {
	"x",
	"y",
	"z"
};
```
This will:
- create an array of 3 class objects
- pass "x" as a parameter to the constructor of the first object
- pass "y" as a parameter to the constructor of the second object
- etc.

### Invoke constructor with multiple parameters
If you want to invoke constructors that takes >1 parameters when you initialize an array, the initialization takes the form of a function call:
```c++
ComplexClass arrayOfObjects[] = {
	ComplexClass("param1", 1),
	ComplexClass("param2", 2),
	ComplexClass("param3", 3),
}
```
This will:
- create an array of 3 class objects
- pass `"param1"` and `1` as parameters to the constructor of the first object
- etc.


### Mixing it up
```c++
MyClass arrayOfObjects[4] = {
	MyClass(),
	"param1",
	MyClass("param2", 2)
	// note: no 4th object
}
```
This will create an array of 3 `MyClass` objects and
- Invoke the default constructor for the first object
- Invoke the constructor that takes a `string` parameter for the second object
- Invoke the constructor that takes a `string` and an `int` parameter for the third object
- Invoke the default constructor for the fourth object

### Accessing objects in an array
An array of objects works like an ordinary array. Its elements are accessed using the subscript operator:
```c++
arrayOfObjects[1].memberVariable = 1;
int q = arrayOfObjects[1].memberFunction();
```

# UML
## (Unified Modeling Language)
UML is a standard for drawing diagrams of object oriented systems.

Suppose we want to draw a UML diagram for the following class:
```c++
class Printer {
private:
	string message;
public:
	Printer();
	Printer(string initMsg);
	~Printer();
	string getMessage();
	void setMessage(string msg);
	void print();
};
```

In UML, a class is represented by a box. The box is divided into three sections for:
- The name of the class
- The class's member variables
- The class's member functions

![](./res/UML-zones.svg)
![](./res/UML-vars-funs.svg)

### Access modifiers
Access modifiers are indicated by preceding each member with a + (public) or a - (private).
![](./res/UML-access.svg)

### Types
UML shows the types of variables and the return types of functions *after* the name of the variable or functions, separated by a colon.
![](./res/UML-types.svg)

### Constructors and Destructors
Constructors and destructors go in the *functions* section of the box.
![](./res/UML-constr.svg)
