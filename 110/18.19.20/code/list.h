#ifndef LIST_H
#define LIST_H

#include <iostream>
using namespace std;

template <class T>
class LinkedList {
	struct Node {
		T data;
		Node *next;
	} *head;
public:
      LinkedList();
      void append(T d);
      void printContents();
      void insert(T d);
      void insert2(T d);
      void remove(T d);
      bool isEmpty() {
         return head == 0;
      }
      ~LinkedList();
};

template <class T>
LinkedList<T>::LinkedList() : head(0) {
}

template <class T>
void LinkedList<T>::append(T d) {
	if (head == 0) {
		LinkedList<T>::Node *newNode = new LinkedList<T>::Node;
		newNode->data = d;
		newNode->next = 0;
		head = newNode;
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

template <class T>
void LinkedList<T>::printContents() {
	LinkedList<T>::Node *current = head;
	while (current != 0) {
		cout << current->data << " ";
		current = current->next;
	}
}

template <class T>
void LinkedList<T>::insert(T d) {
	LinkedList<T>::Node *newNode, *current, *prev = 0;

	newNode = new LinkedList<T>::Node;
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
void LinkedList<T>::insert2(T d) {
	LinkedList<T>::Node *newNode, *current;

	newNode = new LinkedList<T>::Node;
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
void LinkedList<T>::remove(T d) {
	LinkedList<T>::Node  *current = head,
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
LinkedList<T>::~LinkedList() {
      LinkedList<T>::Node *tmp;
      while (!isEmpty()) {
         tmp = head->next;
         delete head;
         head = tmp;
      }
}

#endif
