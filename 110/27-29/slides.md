background-image:url(./i/q.jpg)
# Queues
---
## Queues
Like stacks, queues are
- sequential data structures
- elements are inserted at one end only, and removed at one end only

Unlike stacks, elements are not inserted and removed at the same end. Not coincidentally, queues are processed like check-out lines at a grocery store or at the local DMV. Queues are *first-in, first out* (equivalently, *last-in, last-out*) -- the first element to be inserted into a queue will also be the first one that gets removed.

The basic operations on queues are usually
- enqueue, to insert a new element into the **rear** of the queue, and
- dequeue, to remove and return the **front** element of the queue
---
## Applications of queues
Queues are appropriate in many situations where limited resources are to be provided to multiple recipients on a first-come, first-serve basis. For example, a printer can only print one document at a time, but multiple printing requests can be made almost simultaneously. In order to provide fair access to the printer, most operating systems utilize a printing queue, where printing requests are naturally ordered from old to new, and older requests are processed first.

The first-come, first-serve nature of queues are also appropriate in several network applications, where it is not about *fairness* but about maintaining the correct order of, for example, packages.
---
## Implementing queues
As with stacks, we will look at two ways to implement queues, namely
- as an array (statically), and
- as a linked list (dynamically)
---
## Static queue implementation
As with stacks, a static queue implementation will use an array to store elements, and one or more indices to keep track of the positions of the back and potentially the front of the queue.
---
## Static queue implementation - enqueue
If a queue class keeps track of the index of the back item, enqueuing is simple:
- make sure the queue isn't full yet
- increment the back index
- set the element at the back index to the value that is being enqueued
---
## Static queue implementation - dequeue
One way to implement dequeue is as follows:
- make sure the queue isn't empty (e.g. rear != -1)
- store the front element's value in a temporary variable, to be returned
- move all the items to the left (except the old front)
- decrement the back index
- return the old front element

This implementation has the advantage that it is simple and familiar. The front of the list is always at index 0. However, it is very inefficient compared to alternatives, as you will see. Every call to dequeue an item leads to every item in the queue being moved.
---
## Static queue implementation - dequeue
A second way to implement dequeuing, which overcomes the inefficiency of the first, is to let the front index change. When an item is dequeued:
- increment the front index
- return the old front item's value (it's still in the array, so)

Note that enqueue still works as before, which means that both the front and back indices can change. A new problem introduced by this implementation is that the occupied elements (between `front` and `back`) of the array eventually *crawl* towards the end of the array, so that the array's capacity as a queue can be exhausted long before it is actually filled.
---
## Static queue implementation - dequeue
The third and preferred implementation, which overcomes the shortcoming of the second, is to regard the array as *circular*. If the queue is shorter than the array, it can wrap around. In other words, if the last array position is used, but there is still space from the first array position onward, new items can be enqueued between the start of the array and the start of the queue.
---
## Static queue implementation - dequeue
To achieve this, `front` and `rear` will protentially have to be wrapped around each time they are incremented. There different ways to implement this. One way is with an `if`-statement, for example:
```c++
rear++;
if (rear == queueSize)
   rear = 0;
```

Another way is with modular arithmetic:
```c++
rear = (rear+1) % queueSize;
// i.e. ++rear %= queueSize;
```
---
## Static queue implementation - when's it full or empty?
The last implementation scheme makes it harder to detect the state of a queue. When `rear == front`, does it mean that the queue is full or empty?

One approach is to always leave one empty element between the last and the first element. The queue is full when
```c++
(rear+2) % queueSize == front
```
and empty if rear is just behind front, i.e. when
```c++
(rear+1) % queueSize == front
```
---
## Static queue implementation - when's it full or empty?
Another approach is to use a variable to keep track of the number of items in the queue. Since the user might request this information anyway, this approach is preferred in the textbook. Also, note that the textbook interprets `front`'s value to be the position **before** the first element (and so should you).
---
### Static queue - code
`queue.h:`
```c++
#ifndef Q_H
#define Q_H
template <class T>
class Queue {
private:
   T *queueArray; // for storing the elements
   int queueSize; // the size of the array
   int front; // position BEFORE the front item
   int rear; // position of the rear item
   int numItems; // number of items in the queue
public:
   Queue(int);
   Queue(const Queue&);
   ~Queue();
   void enqueue(T);
   void dequeue(T&); // note return mechanism!
   bool isEmpty();
   bool isFull();
   void clear(); // new function that removes all items
}
#endif
```
.nop[*]
---
### Static queue - code
`queue.cpp:`
```c++
template<class  T>
Queue<T>::Queue(int s) {
   queueArray = new T[s];
   queueSize = s;
   front = -1;
   rear = -1;
   numItems = 0;
}
```
---
### Static queue - code
...`queue.cpp...`
```c++
Queue<T>::Queue(const Queue &other) {
   queueSize = other.queueSize;
   queueArray = new T[queueSize];
   front = other.front;
   rear = other.rear;
   numItems = other.numItems;
   for (int i=0; i<queueSize; i++)
      queueArray[i] = other.queueArray[i];
}
```
---
### Static queue - code
...`queue.cpp`...
```c++
template <class T>
Queue<T>::~Queue() {
   delete [] queueArray;
}
```
---
### Static queue - code
...`queue.cpp`...
```c++
template<class T>
void Queue<T>::enqueue(T item) {
   if (isFull())
      throw "Queue is full"; // or something

   rear++;
   rear %= queueSize;

   queueArray[rear] = item;
   numItems++;
}
```
---
### Static queue - code
...`queue.cpp`...
```c++
template<class T>
void Queue<T>::dequeue(T &item) {
   if (isEmpty())
      throw "Queue is empty"; // or something

   // front represents the position BEFORE the first element,
   // so we increment it first
   front++;
   front %= queueSize;

   item = queue[front];
   numItems--;
}
```
---
### Static queue - code
...`queue.cpp`...
```c++
template <class T>
bool Queue<T>::isEmpty() {
   return numItems == 0;
}
```
---
### Static queue - code
...`queue.cpp`...
```c++
template <class T>
bool Queue<T>::isFull() {
   return numItems == queueSize;
}
```
---
### Static queue - code
...`queue.cpp`...
```c++
template <class T>
void Queue<T>::clear() {
   front = rear = queueSize -1;
   // could also just be -1? I think so
   // (could really be anything, as long as both are equal and:)
   numItems = 0;
}
```
---
## Dynamic queue
A dynamically implemented queue is structured much like a linked list. Each element in stored in a node, and each node has a link to the next node.

A dynamic implementation offers some advantages over a static implementation:
- The size can change at runtime, so a capacity doesn't have to be determined beforehand
- Nodes can be added or removed without us having to worry about where everything is in memory, which is more intuitive than the static implementation
- The queue won't get full
- No unnecessary memory is used for unused capacity
---
### Dynamic queue - front and rear
Our dynamic queue implementation will differ from the linked list and dynamic stack implementations we've seen so far, in that the queue class will maintain two pointers: one to the front of the queue, and one to the rear. Having both allows us to dequeue from the front and enqueue to the rear very efficiently, because there is no need to traverse the entire list to reach either end. We just have to take care to adjust these pointers when we enqueue or dequeue.
---
### Dynamic queue - code
```c++
template <class T>
class Queue {
   class Node {
   public:
      T value;
      Node *next;
      Node (T v, Node *n=0): value(v), next(n) {}
   } *front, *rear;
   int numItems;
public:
   Queue();
   ~Queue();
   void enqueue(T);
   void dequeue(T&); // note the return mechanism
   bool isEmpty() const;
   // we don't need isFull() because the queue is never full
   void clear();
}
```
We used a different `Node` class than the textbook does; make sure to also check out the textbook's version.
.nop[*]
---
### Dynamic queue - code
The constructor just initializes all pointers to NULL, and the number of items to zero.
```c++
template <class T>
Queue<T>::Queue() {
   front = 0;
   rear = 0;
   numItems = 0;
}
```
---
### Dynamic queue - code
The destructor calls `clear`, which will be defined shortly, to deallocate all nodes in the queue.
```c++
template <class T>
Queue<T>::~Queue() {
   clear();
}
```
---
### Dynamic queue - code
Enqueue allocates a new node, sets its value to the item to be enqueued, and inserts it at the rear of the queue if it isn't empty. If the queue is empty, both `front` and `rear` are pointed to the new node.
```c++
template <class T>
void Queue<T>::enqueue(T el) {
   if (!isEmpty()) {
      rear = rear->next = new Node(el);
      // remember that = associates from right to left, so
      // this is equivalent to:
      //    rear->next = new Node(el);
      //    rear = rear->next;
   } else {
      front = rear = new Node(el);
   }
}
```
---
### Dynamic queue - code
Dequeue saves the value of the front item into the reference parameter, logically removes the front element from the queue by advancing `front` to the next element, deallocates the node using `delete`, and decrements the number of items.

If there was only one element left in the queue, `rear` would still be pointing to it, so we can also set `rear` to `null` in this case. Although, since `isEmpty()` uses `numItems` and not the value of `rear` to determine whether there are still elements left, this isn't necessary.
```c++
template <class T>
void Queue<T>::dequeue(T &num) {
   if (isEmpty()) throw "Queue is empty!";
   item = front->value;
   if (front == rear)
      rear = 0;
   Node *tmp = front;
   front = front->next;
   delete tmp;
   numItems--;
}

```
.nop[*]
---
### Dynamic queue - code
The queue is empty if there are no items.
```c++
template <class T>
bool Queue<T>::isEmpty() {
   return numItems == 0;
}
```
---
### Dynamic queue - code
To clear the queue, we can repeatedly dequeue items until it is empty.
```c++
template <class T>
void Queue<T>::clear() {
   int dummy; // we don't care about the values we dequeue
   // but we still have to give the function a parameter
   while (!isEmpty())
      dequeue(dummy);
}
```
