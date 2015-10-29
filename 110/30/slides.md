class:middle
# Recursion
---
## Recursion
In C++, functions can be called from the bodies of other functions.
```c++
void foo() {
   // ...
}

void bar() {
   foo();
}
```
---
## Recursion
Functions can also call themselves:
```c++
void foo() {
   foo();
}
```
A function that calls itself is called *recursive*.
--


This example will keep calling itself infinitely - or at least until it uses up all the stack space. Obviously it's not good code, but it demonstrates that, when a function calls itself, it creates a **loop**.
---
## Recursion
Like in a traditional loop, we probably want some mechanism to make the recursive function stop at some point. Here, `foo()` has been modified to run `n` times for a given `n`:
```c++
void foo(int n) {
   if (n > 0)
      foo(n-1);
}
```
Now, each time `foo` executes, it will call itself with a slightly (incrementally) smaller value of `n`, until `n` is no longer larger than 0. When that happens, `foo` won't call itself again, and simply return.
---
## Recursion
Suppose we call this `foo` with a parameter of 3. It will create a call stack like this:
```
foo(3)
   foo(2)
      foo(1)
         foo(0)
         return
      return
   return
return
```
--


After `foo(3)` calls `foo(2)`, it has to wait for `foo(2)` to return before *it* can return. Similarly, `foo(2)` waits for `foo(1)`, and `foo(1)` waits for `foo(0)`.

`foo(0)` doesn't call anything else (luckily!), so it can return immediately. This allows `foo(1)` to stop waiting and also return. We bubble all the way down the call stack, until we return control to the initial caller of `foo(3)`.
---
## Recursion
So far, when we needed code to loop, we'd use a control structure like `for` or `while`. In these cases, we can say that we'd use an *iterative* loop.

By contrast, we can also use functions with recursive calls to loop through code. Then we'd call the loop recursive.
---
## Recursion
In an iterative loop, we needed some basic ingredients:
- An initial state
- A stopping condition
- Something that modifies the state, so that the stopping condition will eventually be reached
---
## Recursion
```c++
for (int i = 0; // initial state
     i < 10; // stopping condition
     i++ // modifier
     ) {...}
```
---
## Recursion
```c++
bool b = true; // initial state
int i;
while (b) { // stopping condition
   cin >> i;
   if (i == 0) b = false; // modifier
}
```
---
## Recursion
In recursion, if we want our code to function correctly (i.e. loop a controlled amount of times) we need equivalent ingredients. Unlike in an iterative loop, the conditions/state are defined in terms of the function's parameters.

- The initial state is determined by how the function gets called initially (which parameters)
- The stopping condition is called the **base case**, and it is the parameter values for which the function will not incur another recursive call
- The recursive case is the the `else` to the base case's `if`. In the recursive case, the function calls itself, but with different parameters.
---
## Recursion
Let's rewrite our `foo` example to reflect the structure more clearly:
```c++
void foo(int n) {
   if (n < 1) //base case
      return; //base case

   else        //recursive case
      foo(n-1);//recursive case
}
```
The initial state is not part of the recursive function (why?), but if we call `foo` with, for example, `n` = 6, then that is the initial state. (We generally don't care as much about initial states, though, because recursive functions are usually designed to be functions, where we shouldn't expect to have control over how they get called initially.)
---
class:middle
# Using recursion - why and how
---
## Why should you use recursion?
Recursion is actually never *necessary* to solve a problem. Anything you can do with recursion, you can also do iteratively. In fact, recursion is less efficient than iteration, because each recursive call requires far more overhead than an iteration of a loop.

However, if you understand recursion, you'll find that some problems are represented more naturally (or intuitively) by recursion. For those problems, a recursive solution can be much easier (and therefore faster) to design, and less painful to read.
---
## How to solve a problem recursively
Recursive solutions usually work by repeatedly breaking a problem down into smaller, easier problems, which are passed to the next recursive call, until there is nothing left to solve. This is why we have a base case and a recursive case.

Basically:
- If the problem can be solved immediately, without recursion, the function solves it and returns the solution
- If the problem cannot be solved immediately, the function breaks it down and calls itself with an easier problem

In this overview, the "problem" is represented by the parameters passed to a specific invocation of the function.
---
## Factorial example
The factorial of a number, *n!*, is defined as follows:

*n! = 1 x 2 x 3 x ... x n*

or, equivalently,

*n! = n x (n-1) x (n-2) x ... x 1*

This is clearly a repetitive problem, and as it happens, a good candidate for recursion.
---
## Factorial example
We can define the factorial of *n* as:
- *n x (n-1) x (n-2) ...* for any *n* larger than 1
- 1 if *n* is 1 or 0

--

The second bullet makes for a nice base case, but how should we define the recursive case?
---
## Factorial example
Note that the value of *5!* can be calculated as
```
5 * 4 * 3 * 2 * 1
```
which can be grouped as
```
5 * (4 * 3 * 2 * 1)
```
which is
```
5 * 4!
```
Neat, huh?
---
## Factorial example
Furthermore, that remaining *4!* can be written as
```
4 * (3 * 2 * 1)
```
which is
```
4 * 3!
```
Following this trend, *3! = 3 x 2!*, and *2! = 2 x 1!*, and finally, because we know the base case, *1! = 1*.

--


So we can define *n!* as
- 1 if *n <= 1*
- *n* times *(n-1)!* otherwise

---
## Factorial example
This is very easy to translate to C++ code:
```c++
int factorial(int n) {
   if (n <= 1)
      return 1;
   return n * factorial(n-1);
}
```
--

- Which part is the base case?
- How does the recursive case break the problem into smaller problems?
- How does the recursive case work towards the base case?
- Even though the last line is a return statement, the function does not immediately return. Why?
---
## Factorial example
We can picture the expanded calls of an execution of the factorial function like this:
```
factorial(4) {
   return 4 * factorial(3) {
      return 3 * factorial(2) {
         return 2 * factorial(1) {
            return 1;
            // 1 is returned
         }
         // 2 is returned
      }
      // 6 is returned
   }
   // 24 is returned
}
```
---
## Character search example
Suppose we want to search for a specific character in a string and return the number of occurrences.
- What will the base case be? (For which string can we immediately return?)
- How can we break the problem down in the recursive case?
  - What little piece of the problem can we break off to solve now?
  - What is the remainder of the problem that we pass to the next recursive call?
---
## Character search example
The **base case** can be an empty string, because we know that it doesn't contain the character we're looking for. (It can also be a string of length 1, where we can easily check if that one character is the character. However, the code will be less elegant.)

The **recursive case** is, of course, any string that has characters to check. We can quickly check the first character, and if it matches our search, add 1 to the result. Then we can pass the rest of the string to a recursive call to the same function. Since each new call uses a shorter string, we will eventually reach the base case.
---
## Character search example
Suppose we want to count the occurrences of `U` in the string `ZUUL`. A simple overview of how this could look, recursively, is as follows:
```
occurrencesOf(U, ZUUL)
   return 0 + occurrencesOf(U, UUL)
      return 1 + occurrencesOf(U, UL)
         return 1 + occurrencesOf(U, L)
            return 0 + occurrencesOf(U,)
               return 0
            // 0 is returned
         // 1 is returned
      // 2 is returned
   // 2 is returned
// 2 is returned
```
---
## Character search example
To make the C++ code more efficient, we won't actually get substrings of the string at each step. Instead, we'll pass the whole string to each recursive call, but also tell the call which character it should *regard* as the first one - or, in other words, which character to check. Then we'll just increment this character-to-check at each new call.
---
## Character search example
```c++
int numChars(char c, string str, int subscript) {
   // base case: "empty string"
   // (actually, subscript is past string length)
   if (subscript >= str.length())
      return 0;

   // else, check if char at subscript matches
   int result = 0;
   if (str[subscript] == c)
      result = 1;

   // then call the function again with an increased subscript
   // (i.e. check the next character)
   // and add the accumulated result to what we have so far
   result += numChars(c, str, subscript + 1);

   // finally, return the result
   return result;
}
```
---
## Character search example
That code is rather clunky, but it clearly shows which part each section plays in the recursive structure. We could rewrite it as:
```c++
int numChars(char c, string std, int subscript) {
   if (subscript >= str.length())
      return 0;
   else if (str[subscript] == c)
      return 1 + numChars(c, str, subscript+1);
   else
      return numChars(c, str, subscript+1);
}
```
Here, we have two locations where `numChars` could be called from the code. However, the only difference between the two is that, in the first instance, 1 is added to the result of the call before it is returned. The two calls are separated by an `if-else` structure, so only one will be called anyway. So this is still a simple function.
---
## Direct and indirect recursion
The functions we've looked at so far only call themselves to create recursion. We call this **direct** recursion.

**Indirect** recursion is also possible. It results from a more complex scheme, where two or more functions call each other recursively.
---
## Indirect recursion example
Here is a useless but hopefully demonstrative example of indirect recursion:
```c++
void bar(int);
void foo(int i) {
   if (i > 0)
      bar(i);
   cout << "foo " << i << endl;
}
void bar(int i) {
   cout << "bar" << endl;
   foo(i-1);
}

int main() {
   foo(3);
}
```
Q: What will it output?
---
## Indirect recursion example
A:
```
bar
bar
bar
foo 0
foo 1
foo 2
foo 3
```
---
