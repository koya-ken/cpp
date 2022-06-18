#include <array>
#include <iostream>
#include <memory>
#include <vector>

// https://qiita.com/termoshtt/items/3397c149bf2e4ce07e6c
// https://rinatz.github.io/cpp-book/ch07-08-assignment-operator/
// https://cpplover.blogspot.com/2009/11/rvalue-reference_23.html
class A
{
public:
  A();
  ~A();
  A(const A& a);
  A(const A&& a);
  A& operator=(const A& a);
  A& operator=(const A&& a);
};

// https://www.slideshare.net/KeisukeFukuda/effective-modern-c-item-22
class B
{
private:
  std::unique_ptr<A> aPtr = std::make_unique<A>();
};

void log(const char* msg)
{
  std::cout << msg << std::endl;
}

void func_log(const char* msg)
{
  std::cout << "[call] " << msg << std::endl;
}
A::A()
{
  func_log("call A()");
}

A::~A()
{
  func_log("call ~A()");
}

A::A(const A& a)
{
  func_log("call A(const A& a)");
}

A::A(const A&& a)
{
  func_log("call A(const A&& a)");
}

A& A::operator=(const A& a)
{
  func_log("call A::operator=(const A& a)");
  return *this;
}

A& A::operator=(const A&& a)
{
  func_log("call A::operator=(const A&& a)");
  return *this;
}

A return_local_a()
{
  A a;
  return a;
}

A return_with_constructor()
{
  return A();
}

int main(int argc, const char* args)
{

  log("A a1;");
  A a1;
  log("A a2;");
  A a2;
  log("a2 = a1;");
  a2 = a1;
  log("a2 = A();");
  a2 = A();
  log("a2 = return_local_a();");
  a2 = return_local_a();
  log("auto a3 = return_local_a();");
  auto a3 = return_local_a();
  log("auto a4 = return_with_constructor();");
  auto a4 = return_with_constructor();
  log("");

  log("// unique ptr");
  log("auto aPtr1 = std::make_unique<A>();");
  auto aPtr1 = std::make_unique<A>();
  log("auto aPtr2 = std::make_unique<A>();");
  auto aPtr2 = std::make_unique<A>();
  log("aPtr1 = std::make_unique<A>();");
  aPtr1 = std::make_unique<A>();
  log("aPtr1 = std::move(aPtr2);");
  aPtr1 = std::move(aPtr2);
  log("");

  log("// shared ptr");
  log("auto aPtrS1 = std::make_shared<A>();");
  auto aPtrS1 = std::make_shared<A>();
  log("auto aPtrS2 = std::make_shared<A>();");
  auto aPtrS2 = std::make_shared<A>();
  log("aPtrS1 = std::make_shared<A>();");
  aPtrS1 = std::make_shared<A>();
  log("aPtrS1 = aPtrS2;");
  aPtrS1 = aPtrS2;
  log("");

  log("// native array");
  log("A aNArr[2];");
  A aNArr[2];
  log("");

  log("// std::array");
  log("std::array<A, 2> aArr;");
  std::array<A, 2> aArr;
  log("aArr[0] = a1;");
  aArr[0] = a1;
  log("");

  // B
  log("// B ");
  B b1;
  B b2;
  // b2 = b1;
  log("");

  log("end");
  return 0;
}