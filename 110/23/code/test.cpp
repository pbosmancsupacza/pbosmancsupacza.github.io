#include <list>
#include <iostream>
using namespace std;

int main() {

   // push_back; back; push_front; front; size
   list<int> list1;
   list1.push_back(12);
   list1.push_back(23);
   cout << list1.front() << " " << list1.back() << endl;

   list<int> list2;
   list2.push_front(99);
   list2.push_front(1);
   cout << list2.front() << " " << list2.back() << endl;

   // size
   cout << list1.size() << endl;
   list1.push_back(34);
   cout << list1.size() << endl;

   // pop_back, pop_front
   cout << list2.back() << endl;
   list2.pop_back();
   cout << list2.back() << endl;

   cout << list1.front() << endl;
   list1.pop_front();
   cout << list1.front() << endl;

   // empty
   cout << list2.empty() << endl;
   list2.pop_front();
   cout << list2.empty() << endl;

   // reverse
   list2.push_back(1);
   list2.push_back(2);
   list2.push_back(3);
   list2.reverse();
   cout << list2.front() << " " << list2.back() << endl;

   // sort
   list2.sort();
   cout << list2.front() << " " << list2.back() << endl;

   // swap
   cout << "unswapped: " << endl << list1.front() << " " << list1.back() << endl;
   cout << list2.front() << " " << list2.back() << endl;
   list1.swap(list2);
   cout << "swapped: " << endl << list1.front() << " " << list1.back() << endl;
   cout << list2.front() << " " << list2.back() << endl;

   // merge
   list1.sort();
   list2.sort();
   list1.merge(list2);
   cout << list2.empty() << endl;
   cout << list1.front() << " " << list1.back() << endl;

   // begin and end
   list<int>::iterator i;
   for (i = list1.begin(); i != list1.end(); i++) // note: < doesn't work
      cout << *i << " ";
   cout << endl;

   // rbegin and rend
   list<int>::reverse_iterator ri;
   for (ri = list1.rbegin(); ri != list1.rend(); ri++) // note: < doesn't work
      cout << *ri << " ";
   cout << endl;

   // insert
   i = list1.begin();
   i++;
   i++;
   i++;
   list1.insert(i, 12);
   for (i = list1.begin(); i != list1.end(); i++)
      cout << *i << " "; cout << endl;
   list1.insert(list1.end(), 45);
   for (i = list1.begin(); i != list1.end(); i++)
      cout << *i << " "; cout << endl;

   // erase
   i = list1.end();
   i--;
   i--;
   list1.erase(i);
   for (i = list1.begin(); i != list1.end(); i++)
      cout << *i << " "; cout << endl;

   i = list1.begin();
   list<int>::iterator j = list1.begin();
   j++; j++;
   list1.erase(i,j);
   for (i = list1.begin(); i != list1.end(); i++)
      cout << *i << " "; cout << endl;

   i = list1.begin(); i++; i++;
   j = list1.begin();
   /* list1.erase(i,j); // seg fault!
   for (i = list1.begin(); i != list1.end(); i++)
      cout << *i << " "; cout << endl;*/

   // splice
   list2.push_back(-1);
   list2.push_back(-2);
   list2.push_back(-3);
   i = list1.begin();
   i++;
   i++; // -> 23
   list1.splice(i, list2);
   cout << "1: ";for (i = list1.begin(); i != list1.end(); i++)
      cout << *i << " "; cout << endl;
   cout << "2: ";for (i = list2.begin(); i != list2.end(); i++)
      cout << *i << " "; cout << endl;

   // unique
   list2.push_back(1);
   list2.push_back(2);
   list2.push_back(1);
   list2.push_back(3);
   list2.push_back(3);
   list2.push_back(3);
   list2.push_back(3);
   list2.push_back(4);
   list2.unique();
   for (i = list2.begin(); i != list2.end(); i++)
      cout << *i << " "; cout << endl;
}
