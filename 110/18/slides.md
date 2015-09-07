class:middle
#Linked Lists
---
class:middle
An array is a *sequential list*. Data is ordered by its position in memory.
---
class:middle
background-image:url(./i/eggs.jpg)
An array's size is fixed. Element positions are inflexible - insertion and deletion require a lot of data movement.
---
class:middle
background-image:url(./i/lights.jpg)
Linked lists encapsulate elements in *nodes* that can be placed anywhere in memory. The order of nodes in the list is determined by pointers that connect nodes.
---
class:middle
Nodes can be allocated dynamically and placed anywhere in memory (don't have to be contiguous). To reorder nodes, links are adjusted.
---
class:middle
A node contains data and a pointer to the next node in the list.

![](./i/nodes.png)

```c++
template <class T>
struct Node {
	T data;
	Node *next; // self-referential
};
```
*.nop[i]*
---
class:middle
A linked list is a data structure containing 0 or more nodes.

The list has a pointer (called `head`) that points to the first node. Each node in the list points to the next, until the last node, which points to `NULL`.

![](./i/list.jpg)

```c++
template <class T>
class LinkedList {
	Node<T> *head;
//...
};
```
If a linked list has 0 elements, the `head` member points to NULL.
*.nop[i]*
---
class:middle
You can define the `Node` struct *inside* the `LinkedList` class. This will make the struct invisible to clients.
```c++
template <class T>
class LinkedList {
	struct Node {
		T data;
		Node *next;
	} head;
};
```
*.nop[i]*
---
class:middle
To insert the first element in an empty list:
1. Create a new node
  1. Initialize it with the element data
  2. Set its `next` pointer to `NULL`
2. Point the list's `head` pointer to the new node
---
class:middle
```c++
template <class T>
void LinkedList<T>::append(T d) {
	if (head == 0) {
		LinkedList<T>::Node *newNode = new LinkedList<T>::Node;
		newNode->data = d;
		newNode->next = 0;
		head = newNode;
	}
	// else ...
}
```
*.nop[i]*
---
class:middle
To append a new element to a non-empty list:
1. Create a new node
  1. Initialize it with the element data
  2. Set its `next` pointer to `NULL`
2. Find the last element in the list
  1. Create a node pointer
  2. Point it to the first element
  3. While its `next` pointer is not `NULL`, traverse it to its `next` pointer
3. Point the last node's `next` pointer to the new node
---
class:middle
```c++
template <class T>
void LinkedList<T>::append(T d) {
	if (head == 0) {
		// ...
	} else {
		LinkedList<T>::Node *newNode = new LinkedList<T>::Node;
		newNode->data = d;
		newNode->next = 0;

		LinkedList<T>::Node *current = head;
		while (current->next != 0)
			current = current->next;
		current->next = newNode;
	}
}
```
*.nop[i]*
---
class:middle
The code for finding the last node also demonstrates how you traverse a linked list: by repeatedly setting a `Node` pointer to its own `next` field.
---
class:middle
To print a list's contents, you can use a `Node` pointer to traverse the list and print each `Node`'s `data` field.
```c++
template <class T>
void LinkedList<T>::printContents() {
	LinkedList<T>::Node *current = head;
	while (current != 0) {
		cout << current->data << " ";
		current = current->next;
	}
}
```
*.nop[i]*

What does this code do if the list is empty?
---
class:middle
Next lecture: inserting anywhere
