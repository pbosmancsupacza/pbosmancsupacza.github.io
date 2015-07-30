Todo: format code met tabs
Todo: praat oor standalone weergawe van ++

class: middle
# Operator overloading: increment and relational operators

---

# Prefix ++
The increment and decrement operators (++ and --) are **unary**, meaning they take only one operand. Overloading a unary operator is similar to overloading a binary operator. You just need to learn the mapping of operands to the calling object and/or parameters.

---

# Prefix ++ The following code
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

# Prefix ++ Example function declaration with overloaded operator:
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

# Prefix ++ Example implementation:
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
}
```
Note:
- we first perform the incrementation on the calling object ("this")
- then we return the calling object
This is so that our implementation matches the usual, expected behaviour of prefix incrementers, namely that the result equals the incremented operand.

Prefix -- is very similar.

---

# Postfix ++ The postfix increment operator is invoked like this:
```c++
Time t(1, 59, 59); t++;
```
and, if it behaves like it does for primitive types (like int, char, etc), then it should only cause its operand to be incremented **after** returning its current value.

The two main questions are
- what is the signature, and
- how to increment the object after returning its value

---

# Postfix ++

## The signature With prefix ++, the operand is already conceptually to the left of the operator. So, to distinguish itself, postfix++ uses a **dummy argument**:
```c++
Time &operator++(int);
```
The int argument is not used, and does not have to be named.

So, in summary, these two statements are equivalent:
```c++
++x;
x.operator(++);
```
as are these two:
```c++
y++;
y.operator++(0); // or any integer you want
```

---

# Postfix ++

## Correct behaviour
It's not possible to let a function perform any action after it has returned. Postfix incrementations only *appear* to increment after they return; what actually happens is this:
1. A copy of the object is made
2. The original ("this") is incremented
3. The copy is returned

So we add to our Time class:
```c++
class Time {
  // ... member vars...
public:
  // ... constructors...
  // postfix operators:
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
Note that, while prefix++ returned a reference, our postfix++ returns a non-reference. This is because we are note allowed to return a reference to a local variable or object; when the function returns, the local variable goes out of scope and is destroyed, and any references to that value are now dangling. But if we return the local value by *value*, a copy is made which will live on, in the scope of the caller.

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

## Alternative version
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

## Alternative version
Remember that, in the alternative version, the ++ operator is not a member of the class it takes as an operand. It is very likely that it will still need access to that class' private members. So in this example, the operator is declared as a `friend` function of the class.
```c++
class Time2 {
  int hour, minute, second;
public:
  // ...
  friend Time2 &operator++(Time2&);
  friend Time2  operator++(Time2&, int);
};

Time2 &operator++(Time2 &other) {
  if (++other.seconds > 59) {
    other.seconds %= 60;
    ++other.minutes;
  }
  if (other.minutes > 59) {
    ++other.hours;
  }
  return other;  
}

Time2  operator++(Time2 &other, int) {
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
