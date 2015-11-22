#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <value_ptr>
#include <string>
#include <iostream>

#define BLUE    "\x1b[38;5;33m"
#define GREEN   "\x1b[38;5;36m"
#define SUBDUE  "\x1b[38;5;12m"
#define RESET   "\x1b[0m"

using std::value_ptr;
using std::string;
using std::cout;
using std::endl;
using std::move;


struct A : public std::clonable<A>
{
  string data{"I have been default constructed"};

  A() { cout << __PRETTY_FUNCTION__ << endl; };
  A(string data) : data{data} { cout << __PRETTY_FUNCTION__ << endl; }
  A(const A & a) : data{a.data} { cout << __PRETTY_FUNCTION__ << endl; }
  A(A && a) : data{move(a.data)} { cout << __PRETTY_FUNCTION__ << endl; }

  A& operator=(A && a) &&
  {
    cout << __PRETTY_FUNCTION__ << endl;
    data = move(a.data);
    return *this;
  }
 
  A& operator=(const A & a) &
  {
    cout << __PRETTY_FUNCTION__ << endl;
    data = a.data;
    return *this;
  }

};

TEST_CASE("ctors", "[values]")
{
  cout << GREEN << "Constructors" << RESET << endl;

  cout << BLUE <<  "Construct" << RESET << endl;
  value_ptr<A> a{"a"}, b{"b"};
  cout << a->data << endl;
  cout << endl;

  cout << BLUE << "Move" << RESET << endl;
  a = value_ptr<A>{"aa"};
  cout << a->data << endl;
  cout << endl;

  cout << BLUE << "Copy" << RESET << endl;
  a = b;
  cout 
    << a->data << endl
    << b->data << endl
    << endl;

  cout << BLUE << "Move Explicit" << RESET << endl;
  {
    value_ptr<A> tmp{"a"};
    a = move(tmp);
  }
  cout 
    << a->data << endl
    << b->data << endl
    << endl;

  cout << BLUE << "Copy Assign" << RESET << endl;
  value_ptr<A> aa{"aa"};
  a = aa;
  cout 
    << aa->data << endl
    << a->data << endl
    << b->data << endl
    << endl;
}

struct Base
{
  virtual string id() = 0;
  virtual Base* clone() const = 0;
};

struct B : public Base
{
  string data{"muffins"};
  string id() override { return "I am B with " + data; }

  B() { cout << __PRETTY_FUNCTION__ << endl; };
  B(string data) : data{data} { cout << __PRETTY_FUNCTION__ << endl; }
  B(const B & b) : data{b.data} { cout << __PRETTY_FUNCTION__ << endl; }
  B(B && b) : data{move(b.data)} { cout << __PRETTY_FUNCTION__ << endl; }

  B& operator=(B && b) &&
  {
    cout << __PRETTY_FUNCTION__ << endl;
    data = move(b.data);
    return *this;
  }
 
  B& operator=(const B & b) &
  {
    cout << __PRETTY_FUNCTION__ << endl;
    data = b.data;
    return *this;
  }

  B* clone() const override
  { 
    cout << __PRETTY_FUNCTION__ << endl;
    return new B{*(this)};
  }

};

struct C : public Base
{
  string data{"pizza"};
  string id() override { return "I am C with " + data; }

  C() { cout << __PRETTY_FUNCTION__ << endl; };
  C(string data) : data{data} { cout << __PRETTY_FUNCTION__ << endl; }
  C(const C & c) : data{c.data} { cout << __PRETTY_FUNCTION__ << endl; }
  C(C && c) : data{move(c.data)} { cout << __PRETTY_FUNCTION__ << endl; }

  C& operator=(C && c) &&
  {
    cout << __PRETTY_FUNCTION__ << endl;
    data = move(c.data);
    return *this;
  }
 
  C& operator=(const C & c) &
  {
    cout << __PRETTY_FUNCTION__ << endl;
    data = c.data;
    return *this;
  }

  C* clone() const override
  { 
    cout << __PRETTY_FUNCTION__ << endl;
    return new C{*(this)};
  }

};

TEST_CASE("polymorphics", "[values]")
{
  cout << GREEN << "Polymorphics" << RESET << endl;

  cout << BLUE << "Construction" << RESET << endl;
  value_ptr<Base> b = new B{},
                  c = new C{};

  cout << b->id() << endl
       << c->id() << endl
       << endl;

  
  cout << BLUE << "Copy Passing" << RESET << endl;
  auto f = [](value_ptr<Base> p) { cout << p->id() << endl; };

  f(b);
  f(c);
  cout << endl;
  
  cout << BLUE << "Move Passing" << RESET << endl;
  auto mf = [](value_ptr<Base> &&p) { cout << p->id() << endl; };
  {
    value_ptr<Base> bb = new B{},
                    cc = new C{};

    mf(move(bb));
    mf(move(cc));
  }

  cout << endl;
}
