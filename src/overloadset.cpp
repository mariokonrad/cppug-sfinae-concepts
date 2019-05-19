#include <iostream>

struct foo {};
struct base {};
struct derived : base {};

void func(int)     { std::cout << __PRETTY_FUNCTION__ << '\n'; }
void func(double)  { std::cout << __PRETTY_FUNCTION__ << '\n'; }
void func(base)    { std::cout << __PRETTY_FUNCTION__ << '\n'; }
void func(...)     { std::cout << __PRETTY_FUNCTION__ << '\n'; }

int main(int, char **)
{
	func(10);
	func(10.0);
	func(foo{});
	func(base{});
	func(derived{});
}
