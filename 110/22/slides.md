class:middle
## OTHER TYPES OF LINKED LISTS
### *doubly-linked and circularly-linked lists*
---
class:middle
In the linked lists we have created so far, each node has **one** link, which is a pointer to the next node in the list. The list maintains a pointer to the first node, and the last node's link is set to `NULL`.

What we have simply been calling "linked lists" are actually specifically *singly linked lists*, because nodes are connected a single links.

We will look at two variations of linked lists: doubly linked lists, and circularly linked lists.
---
class:middle
### Doubly linked lists
In a doubly linked list, each node has **two** links: one to the next node, as with singly linked lists, and also one to the *previous* node.
---
class:middle
![](./i/doublyll.gif)
---
class:middle
Doubly linked nodes have 3 fields: the element data, a link to the next node, and a link to the previous node.
```c++
template <class T>
class DoublyLinkedList {
	class Node {
		T data;
		Node *next, *prev;
	} *head;
	// ....
};
```
Again, the linked list itself only needs a pointer to the first node. (What would the pros and cons of also maintaining a pointer to the last node be?)
---
class:middle
In a doubly linked list, traversing backwards is more efficient, but maintaining correct links in operations like `insert` and `delete` can be more complex.
---
class:middle

---
class:middle

---
class:middle

---
class:middle

---
class:middle

---
class:middle

---
class:middle

---
class:middle

---
class:middle
