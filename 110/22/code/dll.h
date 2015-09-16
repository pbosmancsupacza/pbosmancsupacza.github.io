/*
	doubly linked list
*/


#ifndef DLLIST_H
#define DLLIST_H

#include <iostream>
using namespace std;

template <class T>
class DLList {
	/*
		note: Node is an inner class of DLList,
		so no naming conflicts arise, even though
		it has the same name as the inner class of
		SLList. Neat!
	*/
	class Node {
	public:
		T data;
		Node *prev, *next;
		Node(T d, Node* p, Node *n):
			data(d), prev(p), next(n) {}
	} *head;
public:
      DLList();
		void printNodes();
      void printContents();
		void printReverse();
      void append(T d);
      void insert(T d);
      void remove(T d);
      bool isEmpty() {
         return head == 0;
      }
      ~DLList();
};

template <class T>
DLList<T>::DLList() : head(0) {
}

template <class T>
void DLList<T>::printNodes() {
	DLList<T>::Node *current = head;
	while (current != 0) {
		cout << '[';
		if (current->prev)
			cout << current->prev->data;
		else
			cout << ' ';
		cout << "|" << current->data << "|";
		if (current->next)
			cout << current->next->data;
		else
			cout << ' ';
		cout << "] ";
		current = current->next;
	}
	cout << endl;
}

template <class T>
void DLList<T>::printContents() {
	DLList<T>::Node *current = head;
	while (current != 0) {
		cout << current->data << " ";
		current = current->next;
	}
	cout << endl;
}

template <class T>
void DLList<T>::printReverse() {
	DLList<T>::Node *n = head;
	while (n && n->next != 0) n = n->next;
	while (n != 0) {
		cout << n->data << " ";
		n = n->prev;
	}
	cout << endl;
}

template <class T>
void DLList<T>::append(T d) {
	if (head == 0) {
		head = new DLList<T>::Node(d, 0, 0);
	} else {
		DLList<T>::Node *current = head;
		while (current->next != 0)
			current = current->next;
		current->next = new DLList<T>::Node(d, current, 0);
	}
}

template <class T>
void DLList<T>::insert(T d) {
	DLList<T>::Node *current = head;
	while (current && current->next && current->next->data < d) {
		current = current->next;
	}
   if (current == head && (!current || current->data > d)) {
      head = new DLList<T>::Node(d, 0, current);
   } else {
		if (current->next)
			current->next = current->next->prev = new DLList<T>::Node(d, current, current->next);
		else
      	current->next = new DLList<T>::Node(d, current, current->next);
   }
}

template <class T>
void DLList<T>::remove(T d) {
	DLList<T>::Node *current = head;
	while (current && current->data != d) {
		current = current->next;
	}
	if (current) {
		if (current->prev)
			current->prev->next = current->next;
		else
			head = current->next;
		if (current->next)
			current->next->prev = current->prev;
		delete current;
	}
	// else throw an exception or whatever
}

template <class T>
DLList<T>::~DLList() {
      DLList<T>::Node *tmp;
      while (!isEmpty()) {
         tmp = head->next;
         delete head;
         head = tmp;
      }
}

#endif
