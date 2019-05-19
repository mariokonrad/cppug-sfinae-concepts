#include <iostream>

namespace concepts_cxx20
{
template <class T>
concept HasAdd = requires(T t)
{
	{ t.add(int(), int()) } -> int;
};

template <class T>
concept HasSomeType = requires
{
	typename T::some_type;
};


template <HasAdd T>
void func(T t, int a, int b)
{ std::cout << __PRETTY_FUNCTION__ << ": " << t.add(a, b) << '\n'; }


template <HasSomeType T>
void func2(T)
{ std::cout << __PRETTY_FUNCTION__ << '\n'; }
}

struct foo { int add(int a, int b) { return a + b; } };

struct bar {
	using some_type = float;
	int sub(int a, int b) { return a - b; }
};

int main(int, char **)
{
	//concepts_cxx20::func(bar(), 1, 2); // ERROR
	concepts_cxx20::func(foo(), 1, 2); // OK

	concepts_cxx20::func2(bar()); // OK
	//concepts_cxx20::func2(foo()); // ERROR
	return 0;
}
