#ifndef STACK
#define STACK
template <class T>
class Stack {
   class Node {
   public:
      T val;
      Node *next;
      Node(T v, Node *n):
         val(v), next(n) {
      }
   } *top;
public:
   Stack(): top(0) {}
   Stack(Stack &);
   ~Stack();
   void push(T);
   void pop(T&);
   bool isEmpty() {
      return top == 0;
   }
   void printStack();
};
#include "dynamicstack.cpp"
#endif
