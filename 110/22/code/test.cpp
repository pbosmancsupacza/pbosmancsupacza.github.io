#include <iostream>
#include "sll.h"
#include "dll.h"
using namespace std;

int main() {
   DLList<double> list;
   for (int i = 1; i < 6; i++)
      list.append(i);

   list.printContents();
   list.remove(4);
   list.remove(4);
   list.printContents();
   list.insert(4);
   list.printContents();
   list.remove(1);
   list.printContents();
   list.remove(5);
   list.printContents();
   list.insert(6);
   list.printContents();
   list.insert(5);
   list.printContents();
   list.insert(0);
   list.printContents();
   list.insert(1);
   list.printContents();
   list.printReverse();
}
