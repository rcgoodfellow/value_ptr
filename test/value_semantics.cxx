#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <value_ptr>
#include <string>
#include <iostream>

#define BLUE    "\x1b[38;5;33m"
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
