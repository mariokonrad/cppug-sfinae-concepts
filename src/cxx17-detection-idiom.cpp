#include <iostream>
#include <type_traits>

namespace cxx17_detection_idom
{
// remember: template <class ...> using void_t = void;

template <class, class = void>
struct has_add : std::false_type
{};

template <class T>
struct has_add<T, std::void_t<decltype(std::declval<T>().add(int(), int()))>> : std::true_type
{};

template <class T, std::enable_if_t<has_add<T>::value, int> = 0>
void func(T t, int a, int b)
{ std::cout << __PRETTY_FUNCTION__ << ": " << t.add(a, b) << '\n'; }

template <class T>
void func2([[maybe_unused]] T t, [[maybe_unused]] int a, [[maybe_unused]] int b)
{
	if constexpr (has_add<T>::value) {
		std::cout << __PRETTY_FUNCTION__ << ": " << t.add(a, b) << '\n';
	} else {
		// does not work well if 'else if constexpr' present
		static_assert(has_add<T>::value, "member function 'add' not supported");
	}
}
}

struct foo { int add(int a, int b) { return a + b; } };
struct bar { int sub(int a, int b) { return a - b; } };

int main(int, char **)
{
	//cxx17_detection_idom::func(bar(), 1, 2); // ERROR
	cxx17_detection_idom::func(foo(), 1, 2); // OK

	//cxx17_detection_idom::func2(bar(), 1, 2); // ERROR
	cxx17_detection_idom::func2(foo(), 1, 2); // OK
	return 0;
}
