background-image: url(./carrots.jpg)

---

class: middle
# Operator overloading: increment and relational operators

---

## Prefix ++
The increment and decrement operators (++ and --) are **unary**, meaning they take only one operand. Overloading a unary operator is similar to overloading a binary operator. You just need to learn the mapping of operands to the calling object and/or parameters.

---

## Prefix ++
The following code
```c++
MyClass obj(1);
++obj;
```
will invoke the **prefix** increment operator.

Even though the operator is written to the left of the operand, the invocation is equivalent to this:
```c++
obj.operator++() ;
```
which is the representation we should use when overloading. This is the normal form of most unary operators.

---

## Prefix ++
Example function declaration with overloaded operator:
```c++
class Time {
private:
  int hours, minutes, seconds;
public:
  // constructors etc
  Time &operator++ ();
  Time &operator-- ();
};
```
(Everything said about ++ is more or less equivalent for --)

---

## Prefix ++
Example implementation:
```c++
Time &Time::operator++ () {
  if (++seconds > 59) {
    seconds %= 60;
    ++minutes;
  }
  if (minutes > 59) {
    ++hours;
  }
  return *this;
```
}
Note:
- we first perform the incrementation on the calling object ("this")
- then we return the calling object

This is so that our implementation matches the usual, expected behaviour of prefix incrementers, namely that the result equals the incremented operand.

Prefix -- is very similar.

---

## Postfix ++
The postfix increment operator is invoked like this:
```c++
Time t(1, 59, 59);
t++;
```
and, if it behaves like it does for primitive types (like int, char, etc), then it should only cause its operand to be incremented **after** returning its current value.

The two main questions are
- what is the signature, and
- how to increment the object after returning its value

---
## Postfix ++
### The signature
With prefix ++, the operand is already conceptually to the left of the operator. So, to distinguish itself, postfix++ uses a **dummy argument**:
```c++
Time &operator++(int);
```
The int argument is not used, and does not have to be named.

So, in summary, these two statements are equivalent:
```c++
++x;
x.operator++();
```
as are these two:
```c++
y++;
y.operator++(0); // or any integer you want
```

---

## Postfix ++
### Correct behaviour
It's not possible to let a function perform any action after it has returned. Postfix incrementations only *appear* to increment after they return; what actually happens is this:
1. A copy of the object is made
2. The original ("this") is incremented
3. The copy is returned

---

## Postfix ++
### Correct behaviour
So we add to our Time class:
```c++
class Time {
  // ...
  Time operator++ (int);
  Time operator-- (int);
};
```
Implementation:
```c++
Time Time::operator++(int) {
  Time result (*this);
  ++(*this);
  return result;
}
```

---

## Postfix++
### Return types
Note that, while prefix++ returned a reference, our postfix++ returns a non-reference. This is because we are not allowed to return a reference to a local variable or object; when the function returns, the local variable goes out of scope and is destroyed, and any references to that value are now dangling. But if we return the local value by *value*, a copy is made which will live on, in the scope of the caller.

Also note that, for a statement like this to be valid:
```c++
Time obj2 = obj1++;
```
`Time` must have a copy constructor that takes a `const` reference as a parameter.

---

## Postfix++
### To rewrite or not to rewrite
In our implementation of postfix ++, we invoke prefix ++ on `*this`. It is up to you to decide whether you would rather rewrite the code from prefix ++ here. It would certainly be more efficient not to always call a function from within a function, but consider these points:
- Prefix++ takes a reference parameter and returns its value by reference, so minimal copying occurs even with a nested function call
- One advantage of good object oriented code is that it minimizes code duplication, which makes the code less error prone. If you find a bug with the prefix increment code, or want to change what it means for your class (e.g. increment minutes instead of seconds), changing it in the prefix operator would change it for the postfix operator as well.

---

## Standalone versions
Apart from the representation we've seen so far, increment operators can also be represented as **standalone** functions taking the (only) operand as their first parameter. If, for some class, increment operators are overloaded as non-members, then for an object `x` of that class, the following statements are equivalent:
```c++
++x;
operator++(x);
```
as are the following:
```c++
x++;
opeator++(x, 0); // or any int
```

---

## Standalone versions
Remember that, in the alternative version, the ++ operator is not a member of the class it takes as an operand. It is very likely that it will still need access to that class' private members. So in this example, the operator is declared as a `friend` function of the class.
```c++
class Time {
  // ...
  friend Time &operator++(Time&);
  friend Time  operator++(Time&, int);
};

Time &operator++(Time &other) {
  if (++other.seconds > 59) {
    other.seconds %= 60; ++other.minutes;
  }
  if (other.minutes > 59)
    ++other.hours;
  return other;  
}

Time2 operator++(Time2 &other, int) {
  Time2 result (other);
  ++other;
  return result;  
}
```

---

class: middle
# Relational operators

---

## Relational operators
```c++
bool x = a == b ? c < d : e >= f;
```
Relation operators tell us how different values relate to one another. We often use them as conditions for `if` blocks and `for` or `while` loops. Like most, conditional operators can be overloaded.

Our `Time` class could benefit from some overloaded conditional operators.

---

## Relational operators
```c++
class Time {
  // ...
  bool operator == (const Time&) const;
  bool operator != (const Time&) const;
  bool operator <  (const Time&) const;
  bool operator <= (const Time&) const;
  bool operator >  (const Time&) const;
  bool operator >= (const Time&) const;
};
```

---

## Relational operators
```c++
bool Time::operator == (const Time &other) const {
  return hours == other.hours &&
    minutes == other.minutes &&
    seconds == other.seconds;
}

bool Time::operator < (const Time &other) const {
  return  hours < other.hours ||
    (hours == other.hours &&
      (minutes < other.minutes ||
        (minutes == other.minutes && seconds < other.seconds)));
}
```
The rest can be defined in terms of these two:
```c++
return !(*this == other); // !=
return (*this == other || *this < other); // <=
return !(*this <= other); // >
return !(*this < other); // >=
```

---

## Relational operators
### Return type
It makes **way** more sense to let these operators return `bool` values than anything else, but, to my knowledge, this is not enforced.

---

## Relational operators
### As standalone functions
These operators could also have been overloaded as standalone functions. For example:
```c++
class Time2 {
  // ...
  friend bool operator==(Time2&, Time2&);
};

bool operator==(Time2 &l, Time2 &r) {
  return l.hours == r.hours && l.minutes == r.minutes && l.seconds == r.seconds;
}
```

---

## Relational operators
### As standalone functions
Sometimes, we **have** to overload operators as standalone functions. To see why, imagine that `Time` provides a version of `==` that compares itself to an int value:
```c++
class Time {
  // ...
  bool operator== (int &rhs) {
    return (360*hours + 60*minutes + seconds) == rhs;
  }
};
```

---

## Relational operators
### As standalone functions
This version will work fine for a statement like
```c++
timeObject == 100;
```
... but not one like
```c++
100 == timeObject;
```
In the latter, the operator is not called on a `Time` instance. Nor is it "called on" an integer - integers are primitive and have no member functions. Rather, a standalone version of the operator will be invoked, if it exists:
```c++
bool operator == (int &lhs, Time &rhs) { ... }
```

---

class: middle
# That's all folks
