#include <iostream>
//#include "sll.h"
//#include "dll.h"
#include "cll.h"
using namespace std;

int main() {
   CLList<double> list;
   /*
   for (int i = 1; i < 6; i++)
      list.append(i);
   */
   list.insert(1);
   list.insert(4);
   list.insert(0);
   list.insert(6);
   list.insert(2);
   list.insert(3);
   list.insert(5);
   list.printContents();
   /*
   list.remove(4);
   list.remove(1);
   list.printContents();
   list.remove(0);
   list.remove(1);
   list.remove(6);
   list.remove(5);
   list.remove(3);
   list.remove(2);
   list.insert(2);
   list.insert(0);
   list.insert(6);
   list.printContents();
   list.printContents();
   list.remove(5);
   list.printContents();
   list.printContents();
   list.insert(5);
   list.printContents();
   list.insert(0);
   list.printContents();
   list.insert(1);
   list.printContents();
   list.printReverse();
   */
   cout << "done" << endl;
   return 0;
}
