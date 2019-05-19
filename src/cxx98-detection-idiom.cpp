#include <iostream>

namespace detection_idiom_cxx98
{
template <class T>
struct has_add
{
	typedef char yes[1];
	typedef char no[2];

	template <class U, U u> struct has_mem_fun;

	template <class U>
	static yes & test(has_mem_fun<int (U::*)(int, int), &U::add>*);

	template <class U>
	static no & test(...);

	static const bool value = sizeof(test<T>(NULL)) == sizeof(yes);
};

template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> { typedef T type; };


template <class T>
void func(T t, int a, int b, typename enable_if<has_add<T>::value, int>::type = 0)
{ std::cout << __PRETTY_FUNCTION__ << ": " << t.add(a, b) << '\n'; }
}

struct foo { int add(int a, int b) { return a + b; } };
struct bar { int sub(int a, int b) { return a - b; } };

int main(int, char **)
{
	//detection_idiom_cxx98::func(bar(), 1, 2); // ERROR
	detection_idiom_cxx98::func(foo(), 1, 2); // OK
	return 0;
}
