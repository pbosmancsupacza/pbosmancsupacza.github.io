class:middle
# Recursion
---
### Recursion
Recursion is when a function calls itself. This results in loop-like behaviour. Many algorithms and problems are intuitively defined recursively.

A light-hearted definition for recursion goes as follows: For recursion, see recursion.
---
### Example
The following recursive function
```c++
void foo(int i) {
   if (i >= 10) return;
   foo(i+1);
}
```
is more or less equivalent to the following loop
```c++
for (int i = 0; i < 10; i++)
```
- Which part causes the "loop" to stop? How?
--

*The first line of the function. If a certain condition is met, the function will not make another recursive call, allowing the stack to begin unwinding.*
--

- What is that part called in recursion?
--

*The base case.*
--

- When is i set to 0?
--

*When the function is called with 0 as a parameter. Note that, in recursion, we mostly use parameters and return values instead of local variables. There isn't much to initialise; starting conditions are usually given by the first parameters a function gets called with.*
---
### Example 2
This recursive function prints stuff:
```c++
void bar(int i) {
   if (i > 0) {
      cout << i << ',';
      bar(i/2);
   }
}
```
- This function appears to have no base case. Is that really so?
--

*No. The base case can be considered as the outside of the `if`-block. It's equivalent to:*
```c++
void car(int i) {
   if (i < 1) return;
   cout << i << ',';
   car(i/2);
}
```
--
- What will the function print if it is called with 16?
--

*16,8,4,2,1*
---
### Example 3
This function calculates stuff:
```c++
int goo(int i) {
   return i <= 1 ? 1 : i * goo(i-1);
}
```
- When will this function stop recursing?
--

*When called with an int less than or equal to 1.*
--

- How do we know that it will eventually stop?
--

*Because each recursive call uses a smaller-valued parameter.*
--

- What does it calculate?
--

*The product of all integers from 1 to the parameter value; a.k.a. the factorial.*
---
# Questions
Which is more efficient: recursion or iterative programming (loops)? Why?
--


*Iterative programming. Recursion makes far more function calls, each of which requires space on the stack. In iterative programming, the same variables are re-used for the entire loop.*
--


(Note how this question was answered. When asked to compare two choices, try and contrast them with one another by describing both.)
---
#Questions
Write a recursive function that calculates the sum of all integers from 0 up to its parameter.
--

```c++
int sum(int n) {
   if (n == 0) return 0;
   return n + sum(n-1);
}
```
or
```c++
int sum(int n) {
   if (n > 0)
      return n + sum(n-1);
   return 0;
}
```
---
#Questions
Will the following function print its numbers in ascending or descending order? Suggest a simple way in which the order can be reversed.
```c++
void yo(int x) {
   if (x > 20) return;
   cout << x << endl;
   yo(x+2);
}
```
--
Ascending.

The numbers can be printed in descending order by calling `yo(x+2)` **before** printing `x` - i.e. swapping the last two lines.
---
#Questions
Aside from the name, what's wrong with this function?
```c++
void aayyylmao(int z) {
   cout << "ayyyy lmao" << endl;
   aayyylmao(z-1);
   if (z < 0) return;
}
```
--
*The base case has no effect, because it is only checked after the recursive step. The function will never terminate. `ayyyy lmao` will be printed until the end of time. It's literally a living nightmare. (Okay, in reality, recursive functions fill up the stack pretty quickly, so this will just crash your program.)*
---
#Questions
Suppose this function is invoked with `5` as a parameter. Will it terminate? If so, what will it return? If not, why not?
```c++
int zzz(int m) {
   if (m < 15) {
      int n = zzz(m*2);
      int o = zzz(m-1);
      return n * o;
   }
}
```
--
*No. But not because there are two recursive calls; that's 100% legit, as long as both approach the base case. In this case, though, the second call* diminishes *the parameter, which means it will never reach the base case.*
---
#Questions
Now suppose this function is invoked with `5` as a parameter. Will it terminate? If so, what will it return? If not, why not?
```c++
int asdf(int qwerty) {
   if (qwerty < 1) return 0;
   cout << qwerty << endl;
   return(asdf(asdf(qwerty-1)));
}
```
--
*Yes. Output will be:*
```
5
4
3
2
1
```
---
# Recursive functions with arrays
When we write recursive functions that operate on arrays, the strategy is usually something like this:
- Base case: the array has one or 0 cells
- Do something on a small part (like the first cell) of the array
- Call the function of the remainder of the array
---
# Recursive functions with arrays
For example, if we want to count the amount of elements in this array: [1,2,3], we could do it like this:
- Count the first element (1) (add 1 to total)
- Recursively count the rest of the array ([2,3])
   - Count the first element (2)
   - Recursively count the rest of the array ([3])
      - Count the first element (3)
      - Recursively count the rest of the array ([])
         - Count the first element ([])
         - No elements; return 0
      - return 0 + 1 = 1
   - return 1 + 1 = 2
- return 2 + 1 = 3
---
# Recursive functions with arrays
Note that we passed a smaller portion of the array to each new recursive call. In C++, we usually do this *logically*, instead of actually creating a subset of the array, which would be very inefficient. How do we do this logically? We pass the whole array, but tell the recursive function which (smaller) part of the array to operate on. For example:
```c++
int sum(int arr[], int start, int length) {
   if (start >= length) return 0;
   return arr[start] + count(arr, start+1, length);
}
```
The key part here is that, in the recursive call, we pass **start+1**. The other key part is that we don't regard `arr[0]` as the start of the array, but rather `arr[start]` (I suppose then we could say we don't regard it as the start of the array, but the element to process).
---
#Questions
Write a recursive function that reverses an array by swapping the first and last elements, then reversing the remaining elements. The function should have this signature:
```c++
void reverse(int arr[], int start, int length)
```
--
```c++
{
   if (start >= length-1) return;
   int tmp = arr[start];
   arr[start] = arr[length-1];
   arr[length-1] = tmp;
   reverse(arr, start+1, length-1);
}
```
---
#Questions
In the previous question, if a user wanted to use our function, they would always have to call it with `start = 0`, which is sort of dumb. There are two ways of fixing this:
1. Write a different function that the user can call, which calls the recursive function with the right parameters
--

   ```c++
   void reverse(int arr[], int length) {
      reverse(arr, 0, length);
   }
   ```
2. Use default parameters
--

   ```c++
   void reverse(int arr[], int length, int start = 0) {
      // old implementation
   }
   ```
---
#Questions
A nice thing about recursion is that it results in backtracking, which can be very useful in many situations, for example in linked lists. Write a function that prints the contents of a linked list in reverse.
- What will the base case be? (Which list doesn't require you to do anything recursively?)
--

*Here you **could** say a list with one element. But then your code wouldn't work for empty lists. An empty list is a better fit here, because it represents both a base case and a corner case.*
--

- What will the rest of the function look like? Remember that you want to print the contents of the nodes as you backtrack.
--

*The idea is to divide the list into the first node and the rest. Print the rest of the list in reverse, then print this node.*
--

- Write the function.
--


```c++
void LinkedList<T>::printReverse(Node *n) {
   if (n == 0) return;
   printReverse(n->next);
   cout << n->data; // you could make this look nicer, yes  
}
```
---
#Questions
You want to write a recursive function that will reverse a linked list.
- What will the base case be? (Which linked list is already reversed?)
--

*Duh-doy! An empty list! Also a list with one element, but you need the empty list case anyway, soooo....*
--

- What will the rest of the function do? (Something with the first element, and something with the rest...)
--

*Reverse the rest of the list, and put the first element at the end.*
--

- You'll also need to fix the linked list's `head` member variable - ideally when the recursion is done. Is it *really* practical to defer this to only the original step though?
--

*Not really. No specific recursive call knows whether it's the first, so it's better to treat them all the same.*
--

- Write the code.
---
# Questions

```c++
void LinkedList<T>::reverse(Node *n) {
   if (n == 0) return;
   Node *rest = n->next;
   reverse(rest);
   head = rest;
   n->next = 0;
   if (rest) {
      for (; rest->next != 0; rest = rest->next);
      rest->next = n;
   } else
      head = n;
}
```
.nop[*]
---
