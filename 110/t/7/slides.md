class:middle
# LINKED LISTS
---
class:middle
![](./i/list.jpg)
---
class:middle
Each data element in the list is contained in a node.
---
class:middle
Each node contains one data element and a pointer to the next node in the list, if any, or otherwise to NULL.
---
class:middle
A linked list just needs to keep a pointer to the first node in the list. Every other node is reachable from there. The last node points to NULL as its next node.
---
class:middle
Node code:
```c++
struct Node {
	double data;
	Node *next; // self-referential
};
```
This node stores `double` data elements..nop[**]
---
class:middle
Linked list code:
```c++
class LinkedList {
	Node *head;
// member functions...
};
```
This linked list keeps a reference to the first node, called head.
---
class:middle
To traverse a linked list, you need a node pointer. Start by pointing it at head, and move it on to each node's `next` pointer until it reaches the node you want, or `NULL`.
---
class:middle
Print the contents of a node:
```c++
void LinkedList::printContents() {
	Node *current = head;
	while (current != 0) {
		cout << current->data << " ";
		current = current->next;
	}
}
```
The step `current = current->next` only changes the node that the pointer `current` points to. The nodes in the list are all left unchanged.
---
class:middle
Return `true` if a given value is in the list:
```c++
void LinkedList::contains(double el) {
	Node *current = head;
	while (current != 0 && current->data != el) {
		current = current->next;
	}
   return (current->data == el) ? true : false;
   // could also check if current != 0
}
```
---
class:middle
To insert a node at the end of a list:
```c++
Node *lastNode;
// traverse lastNode until it's the last node...
lastNode->next = new Node;
lastNode->next->data = el;
lastNode->next->next = 0;
```
---
class:middle
To insert a node at the start of a list:
```c++
Node *newNode = new Node;
newNode->data = el;
newNode->next = head;
head = newNode;
```
---
class:middle
To insert a node in between two other nodes:
```c++
Node *before, *after;
// traverse these nodes until they are before and
// after the position where you want the new node
Node *newNode = new Node;
newNode->data = el;
newNode->next = after;
before->next = newNode;
```
---
class:middle
To insert a node after another node:
```c++
Node *before;
// traverse this node until it points to the node
// before the position where you want the new node
Node *newNode = new Node;
newNode->data = el;
newNode->next = before->next;
before->next = newNode;
```
---
class:middle
To remove a node after another node:
```c++
Node *before:
// ...
Node *tmp = before->next;
before->next = before->next->next;
delete tmp;
```
