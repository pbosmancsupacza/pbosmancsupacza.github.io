class:middle
## LINKED LISTS AS TEMPLATES
### *AND NODES AS CLASSES*
---
class:middle
Previously, we defined `Node` as a struct in the linked list class
```c++
struct Node {
	T data;
	Node *next;
};
```
.nop[*i*]
---
class:middle
We could also define it as a class with a constructor to make new node initializations more efficient
```c++
class Node {
public:
	T data;
	Node *next;
	Node(T d, Node *n = 0):
	  data(d), next(n) {
	}
};
```
.nop[*i*]
class:middle
---
class:middle
For example, we can rewrite the following code, which appends a node to an empty list...
```c++
LinkedList<T>::Node *newNode = new LinkedList<T>::Node;
newNode->data = d;
newNode->next = 0;
head = newNode;
```
.nop[*i*]
---
class:middle
...to just this:
```c++
head = new LinkedList<T>::Node(d);
```
---
class:middle
Another example: inserting a node between two other node pointers called `current` and `previous` was previously done like this:
```c++
Node *newNode = new LinkedList<T>::Node;
newNode->next = current;
prev->next = newNode;
```
...and can now be done like this:
```c++
prev->next = new LinkedList<T>::Node(d, current);
```
---
class:middle
To insert a new node after a given node pointer, we can do this:
```c++
current->next = new LinkedList<T>::Node(d, current->next);
```
The need for a pointer called `newNode` is eliminated in several cases.
---
class:middle
Converting your linked list into a template:
```c++
class LinkedList {
	class Node {
		double data;
		Node *next;
		Node(double d, Node *n = 0):
		  data(d), next(n) {}
	} *head;
	void insert(double el);
	void remove(double el);
	double at(int i);
	// etc
};
```
---
class:middle
becomes this:
```c++
template <class T> // template prefix
class LinkedList {
	class Node { // no template prefix needed for inner class
		T data; // datatype is now T
		Node *next;
		Node(T d, Node *n = 0): // datatype adjusted for
								//constructor
		  data(d), next(n) {}
	} *head;
	void insert(T el); // member function parameters adjusted
	void remove(T el);
	double at(int i); // member function return type adjusted
	// etc
};
```
---
class:middle
Functions defined outside the class for non-template version:
```c++
// note: no template prefix
void LinkedList::insert(double d) { // no template in scope
	LinkedList::Node *newNode, *current; // no template in
										 // Node scope

	newNode = new LinkedList::Node;
	newNode->data = d;

	current = head;
	while (current && current->next && current->next->data < d) {
		current = current->next;
	}

   if (current == head && (!current || current->data > d)) {
         head = newNode;
         newNode->next = current;
   } else {
      newNode->next = current->next;
      current->next = newNode;
   }
}
```
---
class:middle
...must also be adjusted for template version:
```c++
template <class T> // template prefix
void LinkedList<T>::insert(T d) { // function belongs to the
				// scope of a class template;
				// parameter type is a template type

	LinkedList<T>::Node *newNode, *current; // new node pointers
						// use template type in class scope...

	newNode = new LinkedList<T>::Node; // ... and memory allocation
	newNode->data = d;

	current = head;
	while (current && current->next && current->next->data < d) {
		current = current->next;
	}

   if (current == head && (!current || current->data > d)) {
         head = newNode;
         newNode->next = current;
   } else {
      newNode->next = current->next;
      current->next = newNode;
   }
}
```
---
class:middle
The template version still uses relation operators (`==`, `<`) to compare element data. It also uses the stream insertion operator (`<<`) to print elements to the screen. Therefore, the template can only be instantiated for types and classes that support those operators.
---
class:middle
If we want to create our own class that we are able to store in such a templatized linked list, it must overload those operators.
```c++
class Cookie {
	double deliciousness;
public:
	// ...
	bool operator < (Cookie &o) {
		return this.deliciousness < o.deliciousness;
	}
	// ==, etc...
	friend ostream &operator << (ostream &os, Cookie &c);
};
```
---
