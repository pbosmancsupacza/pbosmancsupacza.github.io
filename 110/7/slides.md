class: middle
# Operator overloading
## Stream and array subscript operators

---

class: middle
# Overloading the stream extraction and insertion operators

---

## Stream operators
The stream insertion (`<<`) and extraction (`>>`) operators can be overloaded to make our classes more usable. For example, given a `Time` class, we might want the following sort of behaviour:
```c++
Time timeObject(2, 45, 00);
cout << timeObject << endl;
// should print out:
// 2:45:00
cin >> timeObject;
// should read in seconds and convert to HH:MM:SS
```

---

## Overloading stream operators
There arises a problem: In the following statement,
```c++
cout << timeObject;
```
... the left-hand side operand is not an object of our class. Therefore, we cannot overload the `<<` operator as a member of our class. In face, the `<<` operator belongs to the `ostream` class, which we cannot edit. Similarly, `>>` is part of the `istream` class.

(Note that `cout` and `cin` are instances of the `ostream` and `istream` classes, respectively.)

---

## Overloading stream operators
To overcome this problem, we use an alternative representation of binary operators. The statement:
```c++
cout << timeObject;
```
will invoke **one of** the following formal representations, depending on which one is defined:
```c++
cout.operator<<(timeObject); // either this
operator<<(cout, timeObject); // or this
```
The first representation isn't and cannot be defined, so we just have to create a **standalone** operator in the form of the second representation.

---

## Overloading stream operators
We define our overloaded `<<` operator **outside** our class:
```c++
class Time {
   int h, m, s;
   // ...
};

ostream &operator << (ostream &out, Time &time) {
   out << h << ':' << m << ':' << s;
   return out;
}
```
In our previous example statement, `cout` will play the role of the left argument, and `timeObject` will be the right argument.

Note that the operator returns the `ostream` object (by reference); this allows us to chain calls like this:
```c++
cout << timeObject1 << " and " << timeObject2 << endl;
```
