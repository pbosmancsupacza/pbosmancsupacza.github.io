background-image:url(./i/toolbox.jpg)
# STL
### Standard Template Library
---
# STL
.big[C++ provides a library of generic templates to help you perform common tasks.]

We're going to look at some data structures and some algorithms provided by the STL.
---
## STL Abstract data types

The most important data types in the STL are
- containers
- iterators
--


*Containers* are classes that store and organize data.

--

*Iterators* are classes that access and traverse containers.
---
## STL Containers

Containers are categorized as either *sequenced* or *associative*.

--

A sequence container organizes data sequentially, like an array.

--

An associative container uses keys to provide direct access to its elements.

---
## STL Sequential Containers
STL provides 3 important sequential containers: vectors, deques, and lists.

--

`vector` is the simplest template. Elements can be added and removed from the back or middle.

--

`deque` is like `vector`, but elements can also be added or removed from the front.

--

`list` is a doubly linked list. Elements can be added or removed anywhere, but access is sequential, not random.
---
## STL Sequential Containers
The different classes provide different pros and cons, performance-wise
- `vector`: elements can be added/removed from the end quickly, and access to any element is fast. Adding/removing elements from the middle is slow.
- `deque`: same as vector, and adding/removing elements from the start is also quick.
- `list`: adding/removing elements from anywhere is quick, but accessing is slower than with `vector` or `deque`.
---
## STL Associative Containers
STL provides 4 important associative containers: sets, multisets, maps, and multimaps.

--

A `set` stores a collection of keys. No duplicates are allowed.

A `multiset` is like a `set` but allows duplicate keys to be stored.

--

A `map` stores a collection of data elements that are each "mapped to" (associated with) a key value. Only one key is allowed per element.

A `multimap` allows multiple keys to map to the same element, and duplicates of elements are allowed.
---
## Using vectors
```c++
#include <vector>
#include <iostream>
using namespace std;
int main() {
	vector<int> v;
	int i = 0;
	while(i != -1) {
		cin >> i;
		v.push_back(i);
	}
	//...
```
--

To use vectors, you must include the `<vector>` header file.

--

`vector` is a template class. To create an instance, you must specify which type it is going to store. For example, `vector<int> v;` creates an instance of a vector class that stores `int`-type values.

--

To add a value to a vector, use `push_back(T)`. The value is added to the end of the vector.
---
## Using vectors
```c++
//...
int i = 0;
for ( ; i < v.size()-1; i++)
	cout << v[i] << ", ";
cout << v.at(i) << endl;
//...
```
--

The `size()` member function returns the number of elements in the vector.

--

There is also a `capacity()` function that returns the maximum number of elements the vector can hold in the memory currently allocated. If more elements must be stored, more memory will automatically be allocated.

--

To access an element by its index, you can either use the overloaded `[]`-operator, which works like it does with arrays, or the `at(size_type)` member function.
---
## Using vectors
```c++
//...
int firstElement = v.front();
int firstElement = v.back();
//...
```
--

The `front()` and `back()` member functions return the first and last element, respectively.

--

```c++
//...
while (!v.empty())
	v.pop_back();
//...
```
--

`empty()` only returns true if there are no elements in the vector.

--

`pop_back` removes the last element from the vector.
---
## Iterators
Iterators are generalizations of vectors. An iterator represents a position in a container, and is used to traverse through the elements of that container.

--

Iterators are categorized by how they can be advanced through their elements. They can be
- forward,
- bidirectional, or
- random access

--

They are also categorized in terms of what they allow you to do with the accessed element. They can be
- input or
- output

--

The type of the iterator depends on the container. Vectors and deques have random-access iterators, while lists and all the associative containers discussed have bidirectional iterators.
---
## Using Iterators
```c++
#include <vector>
#include <iostream>
using namespace std;
int main() {
	vector<int> v;
	for (int i=0; i<10; i++)
		v.push_back(i);
	vector<int>::iterator it;
	for (it = v.begin(); it < v.end()-1; it++)
		cout << *it << ", ";
	cout << *it << endl;
	//...
```
--

Iterators are associated with containers. To use vector iterator, you only have to include the `<vector>` header file.

--

The vector iterator is part of the vector template. To create one, you must use the vector template along with a type as a scope. For example: `vector<int>::iterator i;`
---
## Using Iterators
```c++
#include <vector>
#include <iostream>
using namespace std;
int main() {
	vector<int> v;
	for (int i=0; i<10; i++)
		v.push_back(i);
	vector<int>::iterator it;
	for (it = v.begin(); it < v.end()-1; it++)
		cout << *it << ", ";
	cout << *it << endl;
	//...
```
`vector` has a member function called `begin()` that returns an iterator that points to the first element of the vector, and a member called `end()` that points to the element **after** the last element.

--

Iterators can be compared using relational operators (like `<`), and advanced using arithmetic like `++`.

---
## Using Iterators
```c++
#include <vector>
#include <iostream>
using namespace std;
int main() {
	vector<int> v;
	for (int i=0; i<10; i++)
		v.push_back(i);
	vector<int>::iterator it;
	for (it = v.begin(); it < v.end()-1; it++)
		cout << *it << ", ";
	cout << *it << endl;
	//...
```
To access the element that an iterator points to, dereference it:

```c++
cout << *it; // prints the element that it points to
*it = 1; // sets the element that it point to to 1
```
.nop[**]
---
## Using Iterators
Some of `vector`'s member functions use iterators to refer to specific positions in the vector.
```c++
//...
for (it = v.begin(); it < v.end(); v++)
	if (*it == 4)
		break;
v.erase(it);
it++;
v.insert(it, 4);
//..
```

--

`erase(vector<T>::iterator)` removes the element that its iterator parameter points to from the list.

--

`insert(vector<T>::iterator, T)` inserts a new element into the list, just before the element that the iterator parameter points to.
---
# STL Algorithms
STL provides many algorithms that programmers frequently use on container elements. The algorithms are provided as function templates so that they can be used on containers that store any (or most) types.
---
## Using STL Algorithms
Using `random_shuffle`, `sort`, and `binary_search`:
```c++
#include <algorithm>
#include <vector>
using namespace std;
int main() {
	vector<int> v;
	for (int i = 0; i < 10; i++)
		v.push_back(i);

	random_shuffle(v.begin(), v.end());
	sort(v.begin(), v.end());
	bool contains7 = binary_search(v.begin(), v.end(), 7);
	int instancesOf2 = count(v.begin(), v.end(), 2);
	//...
```
--

All 3 algorithms take 2 iterators to specify which elements to operate on. No vector is necessary.
---
## Using STL Algorithms
Using `min_element`, `max_element` and `find`:
```c++
//...
vector<int>::iterator it = v.min_element();
cout << "Smallest element: " << *it << endl;
cout << "Largest element: " << *(v.max_element()) << endl;

it = v.find(9);
// can be used to e.g. erase(it);
```
All 3 algorithms return an iterator pointing to the requested element.
---
## Using STL Algorithms
The `for_each` algorithm is used to apply a function on each element in a container.

For example, given the function:
```c++
void increment(int &i) {
	i++;
}
```
The following code will increment each element in the vector:
```c++
//...
for_each(v.begin(), v.end(), increment);
//...
```
Only the name of the function is given to the algorithm as a parameter.
---
