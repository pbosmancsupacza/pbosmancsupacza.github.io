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
      void remove(T d);
      bool isEmpty() {
         return head == 0;
      }
		T get(int);
      ~LinkedList();
};

#include "list.cpp"
#endif
