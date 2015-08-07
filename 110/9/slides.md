class: middle
# Dynamic Memory Allocation
---
class: middle
# Initializing pointers
---
class: middle
.bigtext[.color1[Declare a pointer with an asterisk between the type and the variable name]]
---
class: middle
.bigtext[
```c++
int *p;
```
]
---
class: middle
.bigtext[This means that `p` is a pointer to an integer]
---
class: middle
.bigtext[We put the `*` close to the **variable name** (not the type):
```c++
char *c;
```
]
---
class: middle
.bigtext[to emphasize which variables are pointers when we declare multiple pointers
```c++
char *c, *d, e;
// c and d are pointers; e is not.
```
]
---
class: middle
.bigtext[The contents of an uninitialized pointer are undefined]

---
background-image:url(./res/pointer-init-table.png)
---
class: middle
.bigtext[
We initialize pointers to **0** or **NULL** to say that they point to nothing
]
---
class: middle
.bigtext[```c++
char *p = 0;
char *q = NULL;
```]
---
background-image:url(./res/pointer-init-table-null.png)
---
class: middle
# Dynamic Variables
---
class: middle
.bigtext[
Variables either live on the **stack** or on the **heap**
]
---
class: middle
## Stack:
.bigtext[
Static variables

Memory allocated at compile time

Maximum size known beforehand
]
---
class: middle
## Heap:
.bigtext[
Dynamic variables

Memory allocated at run time

Use as much memory as needed; return (*deallocate*) to heap after done
]
---
class: middle
.bigtext[
Create dynamic variables using **pointers** and the keyword **`new`**
]
---
class: middle
.bigtext[
To allocate a **single** variable:
```c++
new DataType;
```
]
---
class: middle
.bigtext[
To allocate an **array** of variables:
```c++
new DataType[size];
// where size is a number
```
]
---
class: middle
.bigtext[
`new` allocates a variable that has no name, and returns the address of that pointer.
]
---
class: middle
.bigtext[
We must assign the address to a pointer.
]
---
class: middle
.bigtext[
We can only access the new variable via pointers.
]
---
class: middle
.bigtext[
```c++
int *p = new int;
DataType *q = new DataType;
```
]
---
class: middle
.bigtext[
Consider these 2 cases:
```c++
int *p;
int  i = -1;
p = &i;
```
And
```c++
int *p = new int;
*p = -1;
```
]
---
class: middle
.bigtext[
In both, `p` is a pointer that points to an `int`.
]
---
class: middle
.bigtext[
In the first, the `int` is a static variable, allocated on the stack, and can be accessed using either `*p` or `i`.
]
---
class: middle
.bigtext[
In the second, the `int` is a dynamic variable, allocated on the heap, and can only be accessed using `*p`.
]
---
class: middle
# Deallocation
---
class: middle
.bigtext[
Everything that was allocated dynamically must be deallocated manually
]

Deallocation frees up the memory to be used again later
---
class: middle
.bigtext[
We deallocate memory using the keyword `delete`
]
---
class: middle
.bigtext[
Deallocating a single variable:
```c++
int *p = new int;
delete p;
```
]
---
class: middle
.bigtext[
Deallocating an array:
```c++
int *p = new int[100];
delete [] p;
```
]
---
class: middle
.bigtext[
`delete`-ing doesn't delete the **pointer**. It deallocates the memory **that is pointed to**.
]
---
class: middle
.bigtext[
So, after `delete`-ing, the pointer still points to the same address, but that address is no longer valid.

Such a pointer is called *dangling*.
]
---
class: middle
.bigtext[
Accidentally writing to a dangling pointer can corrupt your program's memory or cause a crash.
]
---
class: middle
.bigtext[
To avoid using dangling pointers, set your pointers to 0 or NULL after deallocating their memory:
```c++
delete p;
p = 0;
// or: p = NULL;
```
]
---
class: middle
# Memory Leaks
---
class: middle
.bigtext[
What happens if you don't `delete` a pointer?
]
---
class: middle
.bigtext[
```c++
void foo() {
   int *p = new int;
}
```
]

When `foo()` exits, `p` goes out of scope.

p is deallocated,

but the dynamically allocated `int` to which `p` points remains in memory.

Without `p`, we cannot access that `int` anymore, and we cannot deallocate it.

This is called a memory leak.

Lots of memory leak will use up all your memory.
---
class: middle
.bigtext[
Memory leak is also caused by double allocation:
```c++
int *p;
p = new int(10); // first allocation

p = new int(11); // new allocation;
                 // old memory is forgotten!
```
]
---
class: middle
.bigtext[
Memory leak occurs when we lose the address of dynamically allocated memory
]
---
class: middle
.bigtext[
Avoid memory leak by `delete`-ing for every `new` before you lose the address
]
---
class: middle
# Operations on Pointers
---
class: middle
.bigtext[
You can *assign* to pointers
]
---
class: middle
.bigtext[
```c++
int *p, *q;
int var = 10;
p = &var;
q = p;
q = new int;
p = q;
delete p;
```
]
---
class: middle
.bigtext[
You can *compare* pointers
]
---
class: middle
.bigtext[
```c++
int *p = new int(1), *q = p;
if (p == q) cout << "equal" << endl;

q = new int(2);
if (p < q) cout << "lt" << endl;
else cout << "gt" << endl;

delete p;
delete q;
```
]
---
class: middle
.bigtext[
You can *add* integers to pointers (and subtract them)
]
---
class: middle
.bigtext[
If `p` points to an integer,

`p+1` points to the integer *next to* `p` in memory

and `p-1` points to the one *before* `p`
]

(*Might not be a valid integer)
---
class: middle
.bigtext[
Adding or subtracting an integer from a pointer is called *pointer arithmetic*
]
---
class: middle
.bigtext[
When evaluating the result of a pointer arithmetic expression,

the compiler *multiplies* the integer by the size of the data type.

This is called *scaling*.
]
---
class: middle
.bigtext[
```c++
DataType *p;
return p + i;
```

The result is a pointer that is `i` steps (each the size of `DataType`) ahead of `p` in memory
]
---
class: middle
.bigtext[
```c++
int *p = new int(0);
p++; // p moves on by 4 bytes

char *c = new char('a');
c++; // c moves on by 1 byte
```
]
---
class: middle
### Careful!
.bigtext[
Pointer arithmetic allows us to access invalid memory
]
---
class: middle
# Dynamic Arrays
---
class: middle
.bigtext[
So far, we used *static* arrays
]
---
class: middle
.bigtext[
The size of a static array must be fixed at compile time
```c++
int array[10];
```
]
---
class: middle
.bigtext[
Setting the size at run time is illegal
```c++
cout << "How many elements?";
int size;
cin >> size;
int array[size];
```
]
---
class: middle
.bigtext[
Allocate *dynamic* arrays on the heap using the `new` keyword
```c++
int *array = new int[10];
```
]
---
class: middle
.bigtext[
The heap provides *dynamic* memory, so the size of the array can now be set at run time
```c++
cout << "How many elements?";
int size;
cin >> size;
int *array = new int[size];
```
]

`array` is a pointer that points to the first element of the array
---
class: middle
.bigtext[
Static and dynamic arrays store the address of the first element to their variables
]
---
class: middle
.bigtext[
You can iterate through an array using pointer arithmetic
]
---
class: middle
.bigtext[
```c++
int size = 99;
int *array = new int[size];

for (int i = 0; i < size; i++)
  *(array + i) = 0;
```
]
---
class: middle
.bigtext[OR
]
---
class: middle
.bigtext[
```c++
int size = 99;
int *array = new int[size];

for (int *i = array; i < array + size; i++)
  *i = 0;
```
]
---
class: middle
.bigtext[
This can also be done with static arrays
```c++
int size = 99;
int array[size];

for (int i = 0; i < size; i++)
  *(array + i) = 0;

// or

for (int *i = array; i < array + size; i++)
  *i = 0;
```
]
---
class: middle
.bigtext[
Dynamic arrays can be traversed using subscripts
]
---
class: middle
.bigtext[
```c++
int size = 99;
int *array = new int[size];

for (int i = 0; i < size; i++)
  array[i] = 0;
```
The expression `array[i]` uses pointer arithmetic and is equivalent to `*(array+i)`
]
---
class: middle
# 2D
---
class: middle
.bigtext[
Static 2D arrays are simple to declare
```c++
int twoD[2][3];
```
This gives us a 2D array with 2 rows and 3 columns
```
twoD[0][0] twoD[0][1] twoD[0][2]
twoD[1][0] twoD[1][1] twoD[1][2]
```
]
---
class: middle
.bigtext[
To declare a 2D *dynamic* array, first declare an array of pointers for the rows...
```c++
int **array = new int*[2];
```
]
---
class: middle
.bigtext[
... and then declare each row to be an array of columns
```c++
for (int row = 0; row < 2; row++)
  array[row] = new int[3];
```
]
---
class: middle
.bigtext[
This gives a slightly different situation in memory
```
twoD[0] -> {twoD[0][0], twoD[0][1], twoD[0][2]}
twoD[1] -> {twoD[1][0], twoD[1][1], twoD[1][2]}
```
]
---
class: middle
.bigtext[
The elements in the matrix are `int` values

The columns containing the values are pointers to those `int`s, so they are `int*` values

The rows containing the columns are pointers to `int*` values, so they are `int**` values
]
---
class: middle
.bigtext[
The elements of the dynamic matrix can be accessed by using double indices
```c++
int zeroOne = twoD[0][1]; //valid
```
]
---
class: middle
.bigtext[
To deallocate a dynamic 2D array, you have to loop through and deallocate each row...
```c++
for (int row = 0; row < rows; i++)
  delete [] twoD[row];
```
]
---
class: middle
.bigtext[
... and then deallocate the array of rows
```c++
delete [] twoD;
```
]
---
class: middle
.bigtext[
The standard `main` function signature uses a dynamic array
```c++
int main(int argc, char **argv) {
```
]
---
class: middle
.bigtext[
... which allows us to access an arbitrary number of arguments passed to the main program from command line
```
# suppose your program is called main
./main argument1 2 3 etc
```
]
---
class: middle
.bigtext[
```c++
int main(int argc, char **argv) {
```

`argc` is the number of arguments passed to the main program from command line

`argv` is the array of arguments, each of which is an array of characters
]
---
class: middle
# Pointers and Functions
---
class: middle
.bigtext[
When you pass a variable to a function
```c++
int variable = -1;
increment(variable);
```
]
---
class: middle
.bigtext[
... and that function takes the parameter as "pass-by-value"
```c++
void increment(int i) { i++; }
```
]
---
class: middle
.bigtext[
... then the function gets a **copy** of the variable, so the variable cannot be altered by the function
```c++
cout << variable << endl;
// still -1
```
]
---
class: middle
.bigtext[
If the function takes the parameter "by reference"
```c++
void increment(int& i) { i++; }
```
]
---
class: middle
.bigtext[
... then the function operates **directly** on the variable, so the variable can be altered by the function
```c++
cout << variable << endl;
// 0
```
]
---
class: middle
.bigtext[
If we pass a **pointer** to a function by **value**
```c++
void foo(int *i) {
  // try and increment the value pointed to:
  *i++;

  // try and increment the address:
  i++;
}
```
]
---
class: middle
.bigtext[
... then the function can can change the value that the pointer is pointing to, but not the address stored by the pointer.
```c++
int *p = new int(-1);
foo(p);
// p still points to the same place
// but the value at *p is now 0
```
]
---
class: middle
.bigtext[
If we pass a pointer to a function by **reference**
```c++
void foo(int *&i) {
  *i++;
  i++;
}
```
]
---
class: middle
.bigtext[
... then the function can modify both the value pointed to *and* the address of the pointer
```c++
int *p = new int(-1);
int *q = p;
foo(p);
// q points to 0
// p points to the address next to p
```
]
---
class: middle
.bigtext[
Passing a pointer by value is similar to passing a static variable by reference - both allow the function to change the variable, but not the reference (or pointer)
]
---
class: middle
.bigtext[
A function can return a pointer
]
---
class: middle
.bigtext[
But you cannot return a pointer to a local, static variable.
]
---
class: middle
.bigtext[
```c++
int *foo() {
  int x = 0;
  return &x; // invalid!
}
```
When the function returns, the local value goes out of scope and is deallocated. The caller gets a pointer to invalid memory.
]
---
class: middle
.bigtext[
Dynamic variables have no scope.
]
---
class: middle
.bigtext[
So you can return a pointer to a dynamically allocated variable from a function
```c++
int *foo() {
  int *x = new int(0);
  return x;
}
```
]
---
class: middle
.bigtext[
(Returning a pointer could be useful if you want to return a dynamic array)
]
---
class: middle
# Deep and Shallow Copies
---
class: middle
.bigtext[
Assigning one pointer to another creates a shallow copy
]
---
class: middle
.bigtext[
```c++
int *p = new int[10];
int *q = p;
```
Only the address is copied.

Both pointers refer to the same dynamic memory.
]
---
class: middle
.bigtext[
If one pointer modifies the memory,
```c++
p[1] = 0;
```
... or even deallocates it,
```c++
delete [] q;
```
... other pointer is also affected.
]
---
class: middle
.bigtext[
A deep copy means each pointer points to its own copy of the data
]
---
class: middle
.bigtext[
A deep copy must be created manually
```c++
int *p = new int(0);
int *q = new int(*p);
```
]
---
class: middle
.bigtext[
A deep copy of an array is created by iterating through the array

```c++
int *p = new int[10];
// fill with data...

int *q = new int[10];
// (we have to know the size
// of the original array)
for (int i = 0; i < 10; i++)
  q[i] = p[i];
```
]
---
class: middle
# That's it
