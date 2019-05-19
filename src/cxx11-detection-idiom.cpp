#include <iostream>
#include <type_traits>

namespace cxx11_detection_idom
{
template <class T>
struct has_add
{
	template <class U>
	static constexpr decltype(std::declval<U>().add(int(), int()), bool()) test(int)
	{ return true; }

	template <class U>
	static constexpr bool test(...)
	{ return false; }

	static constexpr bool value = test<T>(int());
};


template <class T, typename std::enable_if<has_add<T>::value, int>::type = 0>
void func(T t, int a, int b)
{ std::cout << __PRETTY_FUNCTION__ << ": " << t.add(a, b) << '\n'; }
}

struct foo { int add(int a, int b) { return a + b; } };
struct bar { int sub(int a, int b) { return a - b; } };

int main(int, char **)
{
	//cxx11_detection_idom::func(bar(), 1, 2); // ERROR
	cxx11_detection_idom::func(foo(), 1, 2); // OK
	return 0;
}
