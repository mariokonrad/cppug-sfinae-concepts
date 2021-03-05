#include <iostream>
#include <type_traits>

namespace concepts_cxx20
{
// concepts
template <class T>
concept Integral = std::is_integral_v<T>;

template <class T>
concept FloatingPoint = std::is_floating_point_v<T>;

template <Integral T>
void func(T)
{ std::cout << __PRETTY_FUNCTION__ << '\n'; }

template <FloatingPoint T>
void func(T)
{ std::cout << __PRETTY_FUNCTION__ << '\n'; }

// constraints

template <class T>
	requires (std::is_integral_v<T>)
void func2(T)
{ std::cout << __PRETTY_FUNCTION__ << '\n'; }

template <class T>
	requires (std::is_floating_point_v<T>)
void func2(T)
{ std::cout << __PRETTY_FUNCTION__ << '\n'; }


// abbreviated templates:

void func3(Integral auto)
{ std::cout << __PRETTY_FUNCTION__ << '\n'; }

void func3(FloatingPoint auto)
{ std::cout << __PRETTY_FUNCTION__ << '\n'; }
}

int main(int, char **)
{
	concepts_cxx20::func(10);
	concepts_cxx20::func(10.0);

	concepts_cxx20::func2(10);
	concepts_cxx20::func2(10.0);

	concepts_cxx20::func3(10);
	concepts_cxx20::func3(10.0);
	return 0;
}
