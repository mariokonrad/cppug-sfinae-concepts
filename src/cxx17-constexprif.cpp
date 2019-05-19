#include <iostream>
#include <type_traits>

namespace constexprif_cxx14
{
template <class T>
void func(T)
{
	if constexpr (std::is_integral_v<T>) {
		std::cout << __PRETTY_FUNCTION__ << '\n';
	} else if constexpr (std::is_floating_point_v<T>) {
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}
}
}

int main(int, char **)
{
	constexprif_cxx14::func(10);
	constexprif_cxx14::func(10.0);
	return 0;
}
