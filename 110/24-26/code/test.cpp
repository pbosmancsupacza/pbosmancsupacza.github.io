#include <iostream>
#include "dynamicstack.h"
using namespace std;

int main() {
   Stack<int> s;
   int i;
   do {
      cin >> i;
      s.push(i);
   } while (i != -1);

   cout << "s:" << endl;
   s.printStack();
   Stack<int> s2 = s;
   cout << "s2:" << endl;
   s2.printStack();
/*
   while (!s.isEmpty()) {
      s.pop(i);
      cout << i << endl;
   }
*/
   return 0;
}
