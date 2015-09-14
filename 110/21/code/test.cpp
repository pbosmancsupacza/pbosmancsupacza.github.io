#include <iostream>
#include "list.h"
using namespace std;

int main() {
   LinkedList<double> list;
   for (int i = 0; i < 5; i++)
      list.append(i);

   for (int i = 0; i < 5; i++)
     cout << list.get(i) << " ";
    cout << endl;

   list.insert(3.0);
   list.remove(0.0);
   list.printContents();
}
