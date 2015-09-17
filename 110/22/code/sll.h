/*
	singly linked list, yo
*/

#ifndef SLLIST_H
#define SLLIST_H

#include <iostream>
using namespace std;

template <class T>
class SLList {
	class Node {
	public:
		T data;
		Node *next;
		Node(T d, Node* n=0): data(d), next(n) {}
	} *head;
public:
      SLList();
      void printContents();
		void printReverse();
      void append(T d);
      void insert(T d);
      void remove(T d);
      bool isEmpty() {
         return head == 0;
      }
      ~SLList();
};

template <class T>
SLList<T>::SLList() : head(0) {
}

template <class T>
void SLList<T>::printContents() {
	SLList<T>::Node *current = head;
	while (current != 0) {
		cout << current->data << " ";
		current = current->next;
	}
	cout << endl;
}

template <class T>
void SLList<T>::printReverse() {
	SLList<T>::Node *lastPrinted = 0, *current = head;
	while (lastPrinted != head) {
		current = head;
		while (current->next != lastPrinted) {
			current = current->next;
		}
		cout << current->data << " ";
		lastPrinted = current;
	}
	cout << endl;
}


template <class T>
void SLList<T>::append(T d) {
	if (head == 0) {
		head = new SLList<T>::Node(d);
	} else {
		SLList<T>::Node *current = head;
		while (current->next != 0)
			current = current->next;
		current->next = new SLList<T>::Node(d);
	}
}

template <class T>
void SLList<T>::insert(T d) {
	SLList<T>::Node *current = head;
	while (current && current->next && current->next->data < d) {
		current = current->next;
	}
   if (current == head && (!current || current->data > d)) {
         head = new SLList<T>::Node(d, current);
   } else {
      current->next = new SLList<T>::Node(d, current->next);
   }
}

template <class T>
void SLList<T>::remove(T d) {
	SLList<T>::Node  *current = head,
								*prev = 0;
	while (current && current->data != d) {
		prev = current;
		current = current->next;
	}

   if (head == 0 || current == 0) {
      return; // or throw an exception
   } else if (prev == 0) {
      head = current->next;
      delete current;
   } else {
      prev->next = current->next;
      delete current;
   }
}

template <class T>
SLList<T>::~SLList() {
      SLList<T>::Node *tmp;
      while (!isEmpty()) {
         tmp = head->next;
         delete head;
         head = tmp;
      }
}

#endif
