#include <iostream>
using namespace std;

template <class T>
Stack<T>::~Stack() {
   Node *n = top;
   while (!isEmpty()) {
      top = top->next;
      delete n;
      n = top;
   }
}

template <class T>
Stack<T>::Stack(Stack &other) {
   top = 0;
   if (!other.top) return;
   Node *n = other.top;
   top = new Node(n->val, 0);
   Node *p = top;
   n = n->next;
   while (n) {
      p->next = new Node(n->val, 0);
      p = p->next;
      n = n->next;
   }
}

template <class T>
void Stack<T>::push(T v) {
   top = new Stack<T>::Node(v, top);
}

template <class T>
void Stack<T>::pop(T &item) {
   if (isEmpty())
      throw "Stack is empty!";
   item = top->val; // get the top item back
   Node *n = top->next;
   delete top;
   top = n;
}

template <class T>
void Stack<T>::printStack() {
   Node *n = top;
   cout << "stack:" << endl;
   if (n) {
      cout << n->val << endl << "---" << endl;
      n = n->next;
   }
   while (n) {
      cout << n->val << endl;
      n = n->next;
   }
}
