# OO, Classes & Objects


# This Lecture

1. Procedural Programming vs Object Oriented Programming
2. Classes and Objects; also in C++
3. Some Naming Conventions


# Part 1: Object Oriented Programming

## Data and Procedures

```c++
int inc(int i) { // this is a procedure
	return i+1;
}

int x = 99; // this is data
x = inc(x); // this is a procedure operating on data
```

## Procedural Programming
Procedural programming is *process*-oriented. At the top level,

procedures manipulate data.

## Problems with procedural programming
- Function hierarchy is implied
  - but any user can call any function
- Functions work with raw data
  - if data format changes, all client functions are out of whack

## Example problem
Suppose a program keeps track of some data using a variable:
```c++
string data;
```
And suppose many functions operate on the data in this manner:
```c++
void doSomething() {
	if (data == "") {
		// do nothing
	} else {
		doSomethingElse();
	}
}

void doSomethingElse() {
	string local = data;
	data = resultOfSomethingElse();
}
// and so on.
```

Now, suppose the program gets changed.

`data` is no longer stored in a variable, but in a text file.

Now, each call to access `data` must be changed to something like:

```c++
ifstream textFile("data.txt");
string dataCopy;
textFile >> dataCopy;
```

This must be done in every function that uses data!

## Object-Oriented programming
At the top level, there are classes and objects which *encapsulate* data and procedures.

#### Main features:
- Encapsulation
- Data hiding

## Encapsulation and data hiding
Encapsulation means that several data and procedures are contained in a single entity.

Data hiding is the capability of an object to *hide* whatever it encapsulates from code outside the object.

background-image: url(https://www.dropbox.com/s/mb6s7tp37p5yq63/radio1.jpg?dl=0&raw=1)

## Example problem -- solved!
The `data` from the previous problem is *encapsulated* in an object called `dataObject`. It is hidden from outside code, so it cannot be corrupted. And the object provides an *interface* for interacting with the data, so outside code don't have to know how the data is represented internally.

```c++
// Don't worry about how the code works,
// we're getting to that!
class Data {
private:
	string internal_data;
public:
	string getData() {
		return internal_data;
	}
	void setData(string newData) {
		internal_data = newData;
	}
};

Data dataObject;
```
Now, instead of operating on the data directly, outside code can do something like this:
```c++
void doSomething() {
	if (dataObject.getData() == "") {
		// do nothing
	} else {
		doSomethingElse();
	}
}

void doSomethingElse() {
	string local = dataObject.getData();
	dataObject.setData(resultOfSomethingElse());
}
// and so on.
```
If the *internal representation* of the data changes to being stored in a text file, only the `Data` class needs to change.
```c++
class Data {
public:
	string getData() {
		ifstream textFile("data.txt");
		string text_data;
    textFile >> text_data;
		return text_data;
	}
	void setData(string newData) {
		ofstream textFile;
    textFile.open("data.txt");
    textFile << newData;
    textFile.close();
	}
}
```
The *interface* stays the same, so no outside code needs to change.

## Other advantages of OO
#### Simple interfaces for complicated procedures
No matter how many sub-sub-subroutines are involved in an operation, the client only sees the public interface.
#### Contracts for cooperation
Many programmers often work on the same project. Interfaces act as contracts for how different software components should interact.
#### Object reusability
An object has a clear definition, purpose, set of functions, and (ideally) no side-effects. If it is useful in another context, it can be used safely.



# Part Two: Classes and Objects
### And specifically, classes and objects in C++

## Classes and Objects
The "entities" in which data and procedures are encapsulated in OO, are called *classes* and *objects*.

Objects in software model real-world objects. E.g. a program that keeps track of books in a library can have one book object for each real book.

Classes in software model classes of real-world objects. E.g. a `Book` class would define what attributes each book object in the above software has.

Classes define the *types* of objects.

Objects are *instantiations* of classes.

## Classes In C++: An Example You Already Know!
```c++
#include <string> // insert the string class definitions here

string name;  // instantiate an object called `name`;
			 // the type of the object (its class) is string

name = "Phlippie"; // assign a value to the object; stored internally

cout << name << endl; // the object returns its internal value to be printed

int length = name.length(); // call one of string's member functions;
						// the function returns a value
						// (can be stored as a variable or calculated ad hoc. doesn't matter)

name.append(" Bosman"); // modify the internal data
```

## I canz make a class?
To define a new class in C++, use the `class` keyword.

A class is almost exactly the same as a struct - only the default access modifier is private (we'll get to that).

Syntax:
```c++
class ClassName {
	// declarations go here...
};
```
This defines a class called `ClassName`.
**NB:** Remember the semicolon after the closing bracket!

## I can haz class memberz?
The class above doesn't have any *members*... yet.

A member is something that the class encapsulates. Classes encapsulate *data* and *procedures*. So classes can have:
- Member variables (data)
- Member functions (procedures)
## Example
```c++
class MessagePrinter() {
	string message; // member variable
	void printMessage(); // member function
};
```
## I can haz data hiding?
OO should provide data hiding. C++ implements this using *access modifiers*.

An access modifier is a statement that changes the visibility of a class's members to clients of that class.

Members can either be visible or invisible to outside code.

To make a member visible, we use the modifier `public:`. To make a member invisible, we use `private:`.
## Access modifiers syntax
Access modifiers affect all members on the lines following them, up to the next modifier.

E.g.:
```c++
class MyClass {
private:
	int x;
	void foo();
	void bar();
public:
	string y;
private:
	string argh();
};
```
What is `argh()`s visibility?

Notice that any order is valid. But try to keep your members grouped by access.

## Intended usage
In OO, objects usually hide their data, and define an *interface* through which clients can access the data. To do this in C++:
- Make data (member variables) `private`
- Make any functions used only internally `private` as well
- Make *only* the functions that comprise the public interface `public`.

Example:
```c++
class MessagePrinter() {
private:
	string message; // don't allow clients to see/change the internal data
public:
	void printMessage(); // only allow clients to print the data
};
```
Clients are not even allowed to set the value of `message`.

## #tbt
Recall that, unlike `struct`s, classes' default access modifier is `private`.

## I can haz implementation?
The member functions so far have only had *prototypes* - no implementation.

You can provide a function's implementation outside the class's declaration.

```c++
// class declaration:
class Printer() {
public:
	void print();
};

// class member function implementation:
void Printer::print() {
	cout << "Hello world!" << endl;
}
```

`Printer::` tells the compiler that the function is a member of the `Printer` class. `::` is called the scope resolution operator. **Note**: the return type is the first part of the line, *not* the scope resolution operator. Also **note**: implementation must follow declaration - you can't implement something that hasn't been declared yet.

We will elaborate on other ways to provide implementation soon.

## Implementation
The general format for the function header of a function definition outside a class:
```c++
ReturnType ClassName::functionName(Parameter1Type parameter1Name, ...) {
  // implementation...
}
```

## const member functions
Member functions can be declared to be `const`. This means they "promise" not to change anything. A `const` function will not compile if
- it modifies any member variables
- it calls any member functions that are not `const`.

E.g.
```c++
class Printer {
public:
	void print() const;
};

void Printer::print() const {
	//...
}
```

## Accessors and Mutators
In OO, member functions provide an interface through which clients can access member variables. It is very common for clients to want to know what value a variable has, or to change that value. Those two operations are often called **getting** and **setting**.

If we want to allow clients to get or set a variable, we create functions called **getters** and **setters** (a.k.a. **accessors** and **modifiers**):
```c++
class Person {
private:
	string name;
public:
	string getName();
	void setName(string n);
};
```

## Getters + const
Getters shouldn't be allowed to modify anything, so they should be `const`.

## I canz make an object?
Classes define types of objects, and objects are instantiations of classes. So the statement:
```c++
string name;
```
*instantiates* an object of type `string`. The name of the object is `name`.

This is very similar to the statement:
```c++
int i = 0;
```
even though `int` is not a class (it is a *primitive type*). Classes are like types, and objects are like variables.

## Object instantiation
The general form to instantiate an object is
```c++
ClassName objectName;
```
which instantiates a new object of type `ClassName`. The new object is called `objectName` and is an *instance* (hence "instantiation") of the class.

## I canz access memberz?
A class defines which members an object will have. To access those members, use the **dot operator**, which is literally a dot.
```c++
name.length();
```
What type of member of string do we access here?

This works for member variables and member functions.
```c++
class MyClass {
public:
	int memberVariable;
	int memberFunction();
}

// implementations ...

MyClass myObject;
myObject.memberVariable = 99;
int oldValue = myObject.memberVariable++;
cout << myObject.memberFunction();
```

## Only if you can access the members though!
```c++
class ParanoidAndroid {
// what is the default visibility?
	string secretMemberVariable;
	string suspiciousMemberFunction();
};

// ...

ParanoidAndroid marvin;
cout << marvin.secretMemberVariable << endl;
marvin.suspicousMemberFunction();
```
The above code won't compile.

## Stale Data
```c++
class Rectangle {
private:
	// member variables:
	double length;
	double width;
	double area;

public:
	// getters:
	double getLength() const;
	double getWidth() const;
	double getArea(const);

	//setters:
	void setLength(double l);
	void setWidth(double w);
};
```
## Stale Data
```c++
// the getters just return their variables:
double Rectangle::getLength() const {
	return length;
}
double Rectangle::getWidth() const {
	return width;
}
double Rectangle::getArea() const {
	return area;
}

// and the setters take care of everything else:
void Rectangle::setLength(double newLength) {
	length = newLength;
}
void Rectangle::setWidth(double newWidth) {
	width = newWidth;
	area = length * width; // NOTE THIS LINE!
}
```

`area` is a member variable that **depends** on the value of other variables. If `length` changes, `area` is no longer accurate and is said to be *stale*.

An elegant way to avoid the problem:
- dependent variables are not stored as variables
- instead, they are calculated each time they are needed

E.g.
```c++
class Rectangle {
private:
	double length, width; // no area!
public:
	// .. as before
};

// getLength() and getWidth() stay the same...

void Rectangle::setWidth(double newWidth) {
	width = newWidth; // no need to update area
}

double Rectangle::getArea() const {
	return length * width;
	// calculated from the current values, so
	// guaranteed to be accurate or your money back
}
```

## Pointers to Objects
(It starts...)

Creating a pointer and pointing it to an object: example:
```c++
MyClass anObject;
MyClass *aPointer; // not an object, just space for an address
aPointer = &anObject; // pointer now points to the object
```

## Smart Pointers to Objects
Smart pointers (type `unique_ptr`) allow us to create pointers without worrying about memory management.

Creating a smart pointer and pointing it to an object: example:
```c++
#include <memory>
unique_ptr<Rectangle> aPointer(new Rectangle);
```

1. include the code that defines `unique_ptr`
2. the type of the class is `unique_ptr`,
3. the pointer can point to `Rectangle` objects
4. `new Rectangle` allocates a new `Rectangle` object in memory and returns its address
5. the pointer is initialised with the address of the new object; it points to it

## Separate class specification from implementation
We've seen one way to provide implementation for member functions:
```c++
class MyClass {
	void memberFunction();
};

void MyClass::memberFunction() {
	// implementation
}
```

All of this is in one file.

A better way of doing this is as follows:
- class specification in one file
  - only the `class MyClass { ... };` part
	- goes into a *header file* or *specification file*
	- the file's suffix is `.h`
- class implementation in another file
  - all the `void MyClass::memberFunction() { ... }` stuff
	- goes into an *implementation* file
	- the file's suffix is `.cpp`
	- `#include`s the header file
- client code written in other files (main, mostly)
  - `#include` the header file
	- are compiled and linked with the implementation files

`printer.h`:
```c++
#ifndef PRINTER_H
#define PRINTER_H

class Printer {
public:
	void print();
};

#endif
```

`printer.cpp`:
```c++
#include "printer.h"
#include <iostream>
using namespace std;

void Printer::print() {
	cout << "hello" << endl;
}
```

`main.cpp`:
```c++

#include "printer.h"

int main() {
	Printer p;
	p.print();
}
```

to compile:
```bash
g++ -c main.cpp -o main.o
g++ -c printer.cpp -o printer.o
g++ main.o printer.o -o main
```

## Inline Member Functions
It is also possible to provide a member function's implementation in the class declaration. E.g.:
```c++
class Printer {
public:
	void print() {
		cout << "Hi!" << endl;
	}
};
```
We call `print` an *inline function*. No scope resolution operator is needed.

## Inline Member Functions
The compiler may treat inline member functions differently, which may impact your program's performance.

**Normally**, every time a function is called:
- special items (like the function's return address) are stored on the stack
- local variables are allocated
- the return value is allocated

But with inline functions, **inline expansion** takes place:
- the compiler finds each call in client code, and
- replaces it with the code from the function

(This is only done at the compiler's discretion)

How each approach would impact performance:
- Non-inline members increase computation time
- Inline members inflate the size of your object code.
