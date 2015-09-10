#include <iostream>
#include "list.h"
using namespace std;

int main() {
   LinkedList<double> list;
   for (int i = 0; i < 5; i++)
      list.append(i);

   list.printContents(); cout << endl;
   list.remove(4);
   list.remove(4);
   list.printContents(); cout << endl;
}
