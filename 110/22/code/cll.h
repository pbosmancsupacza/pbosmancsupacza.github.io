#ifndef CLIST_H
#define CLIST_H

#include <iostream>
using namespace std;

template <class T>
class CLList {
	class Node {
		T data;
		Node *next;
	} *head;
public:
      CLList();
      void printContents();
		void printReverse();
      void append(T d);
      void insert(T d);
      void remove(T d);
      bool isEmpty() {
         return head == 0;
      }
      ~CLList();
};

template <class T>
CLList<T>::CLList() : head(0) {
}

template <class T>
void CLList<T>::append(T d) {
	if (head == 0) {
		CLList<T>::Node *newNode = new CLList<T>::Node;
		newNode->data = d;
		newNode->next = 0;
		head = newNode;
	} else {
		CLList<T>::Node *newNode = new CLList<T>::Node;
		newNode->data = d;
		newNode->next = 0;

		CLList<T>::Node *current = head;
		while (current->next != 0)
			current = current->next;
		current->next = newNode;
	}
}

template <class T>
void CLList<T>::printContents() {
	CLList<T>::Node *current = head;
	while (current != 0) {
		cout << current->data << " ";
		current = current->next;
	}
}

template <class T>
void CLList<T>::insert(T d) {
	CLList<T>::Node *newNode, *current, *prev = 0;

	newNode = new CLList<T>::Node;
	newNode->data = d;

	current = head;
	while (current && current->data < d) {
		prev = current;
		current = current->next;
	}

	if (prev == 0)
		head = newNode;
	else
		prev->next = newNode;

	newNode->next = current;
}

template <class T>
void CLList<T>::insert2(T d) {
	CLList<T>::Node *newNode, *current;

	newNode = new CLList<T>::Node;
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

template <class T>
void CLList<T>::remove(T d) {
	CLList<T>::Node  *current = head,
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
CLList<T>::~CLList() {
      CLList<T>::Node *tmp;
      while (!isEmpty()) {
         tmp = head->next;
         delete head;
         head = tmp;
      }
}

#endif
