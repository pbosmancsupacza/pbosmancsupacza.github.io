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
*p = &i;
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

(Might not be a valid integer)
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
return *p + i;
```

The result is a pointer that is `i` steps (each the size of `DataType`) ahead of `p` in memory
]
---
class: middle
.bigtext[
```c++
int *p = new int(0);
p++; // p moves on by 4 bytes

char * c = new char('a');
c++; // c moves on by 1 byte
```
]
---
class: middle
.bigtext[
