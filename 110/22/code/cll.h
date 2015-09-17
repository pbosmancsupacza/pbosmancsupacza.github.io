#ifndef CLIST_H
#define CLIST_H

#include <iostream>
using namespace std;

template <class T>
class CLList {
	class Node {
	public:
		T data;
		Node *next;
		Node(T d, Node* n=0): data(d), next(n) {}
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
void CLList<T>::printContents() {
	if (head) {
		cout << head->data << " ";
		CLList<T>::Node *current = head->next;
		while (current != head) {
			cout << current->data << " ";
			current = current->next;
		}
	}
	cout << endl;
}

template <class T>
void CLList<T>::printReverse() {
	cout << "not implemented!" << endl;
}


template <class T>
void CLList<T>::append(T d) {
	if (head == 0) {
		head = new CLList<T>::Node(d);
		head->next = head;
	} else {
		CLList<T>::Node *current = head;
		while (current->next != head)
			current = current->next;
		current->next = new CLList<T>::Node(d, head);
	}
}

template <class T>
void CLList<T>::insert(T d) {
	if (!head) {
		append(d);
	} else {
		CLList<T>::Node *current = head;
		if (head->data > d) {
			while (current->next != head)
				current = current->next;
			head = new CLList<T>::Node(d, head);
			current->next = head;
		} else {
			while (current->next != head && current->next->data < d)
				current = current->next;
			current->next = new CLList<T>::Node(d, current->next);
		}
	}
}

template <class T>
void CLList<T>::remove(T d) {
	if (!head) return; // or something
	CLList<T>::Node *n = head->next;
	while (n != head && n->data != d)
		n = n->next;
	if (n->data == d) {
		if (n == head) {
			if (n->next == n) {
				head = 0;
				delete n;
			} else {
				CLList<T>::Node *p = n;
				while (p->next != n)
					p = p->next;
				p->next = n->next;
				head = p->next;
				delete n;
			}
		} else {
			CLList<T>::Node *p = head;
			while (p->next != n)
				p = p->next;
			p->next = n->next;
			delete n;
		}
	}
}

template <class T>
CLList<T>::~CLList() {
	while (head) {
		T d = head->data;
		remove(d);
	}
}

#endif
