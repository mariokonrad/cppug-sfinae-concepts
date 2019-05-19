#include <iostream>
#include <type_traits>

namespace sfinae_cxx14
{
template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
void func(T)
{ std::cout << __PRETTY_FUNCTION__ << '\n'; }

template <class T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
void func(T)
{ std::cout << __PRETTY_FUNCTION__ << '\n'; }
}

int main(int, char **)
{
	sfinae_cxx14::func(10);
	sfinae_cxx14::func(10.0);
	return 0;
}
