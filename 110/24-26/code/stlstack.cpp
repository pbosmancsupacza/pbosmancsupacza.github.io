#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class myContainer {
public:
   void push_back(int) {
      cout << "push!" << endl;
   }

   void pop_back() {
      cout << "pop!" << endl;
   }

   int back(int) {
      cout << "back!" << endl;
   }
};

int main() {
   stack<float> myStack1;
   deque<char> myDeque1;
   myDeque1.push_back('x');
   myDeque1.push_back('y');
   myDeque1.push_back('z');
   stack<char> myStack2(myDeque1);
   /*
   stack<int, myContainer> myStack3;
   */
}
