#include <iostream>

namespace sfinae_cxx98
{
template <class T> struct is_integral { static const bool value = false; };
template <> struct is_integral<char> { static const bool value = true; };
template <> struct is_integral<int> { static const bool value = true; };
template <> struct is_integral<short> { static const bool value = true; };
template <> struct is_integral<long> { static const bool value = true; };
template <> struct is_integral<long long> { static const bool value = true; };
template <> struct is_integral<unsigned char> { static const bool value = true; };
template <> struct is_integral<unsigned int> { static const bool value = true; };
template <> struct is_integral<unsigned short> { static const bool value = true; };
template <> struct is_integral<unsigned long> { static const bool value = true; };
template <> struct is_integral<unsigned long long> { static const bool value = true; };

template <class T> struct is_floating_point { static const bool value = false; };
template <> struct is_floating_point<float> { static const bool value = true; };
template <> struct is_floating_point<double> { static const bool value = true; };
template <> struct is_floating_point<long double> { static const bool value = true; };

template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> { typedef T type; };


template <class T>
void func(T, typename enable_if<is_integral<T>::value, int>::type = 0)
{ std::cout << __PRETTY_FUNCTION__ << '\n'; }

template <class T>
void func(T, typename enable_if<is_floating_point<T>::value, int>::type = 0)
{ std::cout << __PRETTY_FUNCTION__ << '\n'; }
}

int main(int, char **)
{
	sfinae_cxx98::func(10);
	sfinae_cxx98::func(10.0);
	return 0;
}
