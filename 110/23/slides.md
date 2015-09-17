class:middle
## STL LISTS
---
### STL lists
The standard template library provides a linked list class template, called `list`. It's implemented as a doubly linked list with pointers to the head and tail of the list.

We're gonna go over some of the class's public member functions that you can use.
---

### `back`
returns the last element in the list.

e.g, if a list called `myList` has these elements:
```
1 3 5 7 9
```
then this statement:
```c++
cout << myList.back() << endl;
```
will print
```
9
```
---

### `front`
returns the first element in the list.

e.g, if a list called `myList` has these elements:
```
3 1 4 1 5
```
then this statement:
```c++
cout << myList.front() << endl;
```
will print
```
3
```
---

###`empty`
returns `true` if a list contains zero elements, and `false` otherwise.

e.g.
```c++
while(!myList.empty()) {
	// ...
}
```
---
###`size`
returns the number of elements in the list

e.g. if `myList` contains
```
0 1 2 2 3 4 4 4
```
then the expression
```c++
myList.size()
```
will return 8
---

###`push_back`
inserts the given element into the back of the list (as the last element)

e.g. if `myList` already contains
```
1 2 3
```
then after this statement
```c++
myList.push_back(4);
```
it will contain
```
1 2 3 4
```
---

###`push_front`
inserts the given element into the front of the list (as the first element)

e.g. if `myList` already contains
```
1 2 3
```
then after this statement
```c++
myList.push_front(0);
```
it will contain
```
0 1 2 3
```
---

###`pop_back`
removes the last element from the list

e.g. if `myList` contains
```
0 1 3
```
then after this operation
```c++
myList.pop_back()
```
it will contain
```
0 1
```
---

###`pop_front`
removes the first element from the list

e.g. if `myList` contains
```
0 1 3
```
then after this operation
```c++
myList.pop_front()
```
it will contain
```
1 3
```
---

###`reverse`
reverses the order of a list's elements

e.g. if `myList` contains
```
10 30 50 0
```
then after this statement
```c++
myList.reverse()
```
it will contain
```
0 50 30 10
```
---

###`sort`
sorts the elements of a list in (weak) ascending order

e.g. a list that contains
```
1.1 0.3 1000 -2
```
in that order, will be re-ordered to contain
```
-2 0.3 1.1 1000
```
after a call to `myList.sort()`
---

###`swap`
swaps the elements of one list with those of another

e.g. given two lists containing elements as shown:
```
list1 = {1, 2, 3, 9}
list2 = {5, 6}
```
then after this statement
```c++
list1.swap(list2);
```
the lists will contain elements as shown:
```
list1 = {5, 6}
list2 = {1, 2, 3, 9}
```
---

###`merge`
removes all the elements from the list passed as a parameter and adds them to the calling list object in their correct (sorted) position.

e.g. given two lists with elements
```
list1 = {0, 1, 3, 5, 10}
list2 = {2, 4, 6, 7, 8, 9}
```
then this statement
```c++
list.merge(list2);
```
will result in the lists containing these elements:
```
list1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
list2 = {}
```
---

###`merge` (continued)
note that `merge` requires both lists to be sorted

if you are not sure that both will be sorted, you can sort both lists before merging:
```c++
list1.sort();
list2.sort();
list1.merge(list2);
```

`splice` is like merge, but doesn't require lists to be sorted; instead, you pass an iterator to the function to indicate where the rhs list should be inserted into the lhs list
---
###`begin`
returns an iterator pointing to the first element

e.g. if `myList` contains
```
1 2 3 4 5
```
then the statement
```c++
list<int>::iterator i = myList.begin();
```
creates an iterator called `i` pointing to `1`; the statement
```c++
i++;
```
advances `i` so that it points to `2`;
---
###`end`
returns an iterator that represents the position *beyond* the last element

e.g. if `myList contains`
```
1 2
```
then after these statements
```c++
list<int>::iterator i = myList.begin();
i++;
i++;
```
the expression `i == myList.end()` will be true
---
###`end` (continued)
end is used as a stopping condition when iterating through a list in a loop:
```c++
for ( list<int>::iterator i = myList.begin();
      i != myList.end();
      i++ ) {
	// ...
}
```
---
###`rbegin` and `rend`
return reverse_iterators to use when traversing a list in reverse
```c++
for ( list<int>::reverse_iterator ri = myList.rbegin();
      ri != myList.rend();
      ri++ ) {
	// ...
}
```
`rbegin` points the last element

`rend` represents the position *beyond* the first element

note that we still traverse using `++`
---
###`begin`, `end`, `rbegin` and `rend`
are all *bidirectional* iterators, so you can traverse the list in either direction using `++` or `--`

`iterator`s and `reverse_iterators` are **not** interchangeable, and most functions that take an `iterator` do **not** have an overloaded version that takes a `reverse_iterator`
---
###`insert`
inserts a given element into the position just before a given iterator

e.g. if `myList` contains
```
1 2 4 8
```
then after the statement
```c++
myList.insert(myList.end(), 16);
```
it will contain
```
1 2 4 8 16
```
---
###`erase`
removes the element pointed to by the given iterator

e.g. if myList contains
```
1 2 3 4 8
```
then the statements
```
list<int>::iterator i = myList.begin();
i++;
i++;
myList.remove(i);
```
will remove `3` from the list
---
###`erase`
will remove all the elements between two given iterators, if two are passed

e.g. if myList contains
```
0 20 21 22 100
```
then the statements
```c++
list<int>::iterator i = myList.begin(),
	j = myList.begin();
i++; // -> 20
j++;
j++;
j++; // -> 22
myList.erase(i, j);
```
will remove 20 and 21, but not 22

the first iterator must precede the second in the list, else a seg fault will occur
---
###`splice`
moves all the elements of a given list into the calling list at the position just before a given iterator, without requiring that either list should be sorted

e.g. suppose you have two lists with elements as shown:
```
list1 = {1 2 3}
list2 = {4 5 6}
```
then, after the statement
```c++
list1.splice(list1.rbegin(), list2);
```
the lists will have elements as shown:
```
list1 = {1 2 4 5 6 3}
list2 = {}
```
---
###`unique`
removes any elements that have the same value as the element before it

in a sorted list, it will ensure that a list only has unique values:
```
// list1 contains {1, 2, 2, 3, 3, 3, 3, 4}
list1.unique();
// list1 now contains {1, 2, 3, 4}
```

but in an unsorted list, only contiguous duplicates are removed:
```
// list2 contains {1, 2, 2, 1, 3, 4, 1, 4}
list2.unique();
// list2 now contains {1, 2, 1, 3, 4, 1, 4}
```
---
