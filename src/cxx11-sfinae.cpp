#include <iostream>
#include <type_traits>

namespace sfinae_cxx11
{
template <class T, typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
void func(T)
{ std::cout << __PRETTY_FUNCTION__ << '\n'; }

template <class T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
void func(T)
{ std::cout << __PRETTY_FUNCTION__ << '\n'; }
}

int main(int, char **)
{
	sfinae_cxx11::func(10);
	sfinae_cxx11::func(10.0);
	return 0;
}
