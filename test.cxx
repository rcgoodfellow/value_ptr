#include "value_ptr"
#include <iostream>
#include <string>

using std::value_ptr;
using std::cout;
using std::endl;
using std::string;

void test_int()
{
  value_ptr<int> a;
  value_ptr<int> b{1};

  cout << *a << endl
       << *b << endl << endl;

  a = b;
  
  cout << *a << endl
       << *b << endl << endl;

  *a = 47;
  
  cout << *a << endl
       << *b << endl << endl;
  
  *b = 74;
  
  cout << *a << endl
       << *b << endl << endl;
}

struct Food
{
  virtual string kind() = 0;
  virtual Food* clone() = 0;
};

struct Pizza : Food
{
  string kind() override { return "pizza"; }
  Pizza* clone() override { return new Pizza; }
};

struct Muffin : Food
{
  string kind() override { return "muffin"; }
  Muffin* clone() override { return new Muffin; }
};

void test_food()
{
  value_ptr<Food> a{Pizza{}};
  value_ptr<Food> b{Muffin{}};

  cout << a->kind()<<"\t"<<a.get() << endl
       << b->kind()<<"\t"<<b.get() << endl << endl;

  a = b;
  
  cout << a->kind()<<"\t"<<a.get() << endl
       << b->kind()<<"\t"<<b.get() << endl << endl;

  b = value_ptr<Food>{Pizza{}};
  
  cout << a->kind()<<"\t"<<a.get() << endl
       << b->kind()<<"\t"<<b.get() << endl << endl;

}

int main()
{
  test_int();
  test_food();
}


