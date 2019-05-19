#include <type_traits>
#include <iterator>
#include <vector>
#include <forward_list>
#include <list>
#include <iostream>

// NOTE: only for demonstration purposes


template <class Iterator, class Category>
constexpr bool is_category_v = std::is_same_v<Category,
	typename std::iterator_traits<Iterator>::iterator_category>;

template <class Iterator>
constexpr bool is_forward = is_category_v<Iterator, std::forward_iterator_tag>;

template <class Iterator>
constexpr bool is_bidirectional = is_category_v<Iterator, std::bidirectional_iterator_tag>;

template <class Iterator>
constexpr bool is_random_access = is_category_v<Iterator, std::random_access_iterator_tag>;



template <class Iterator,
	std::enable_if_t<is_forward<Iterator> || is_bidirectional<Iterator>, int> = 0>
Iterator mysearch(Iterator first, Iterator last,
	const typename std::iterator_traits<Iterator>::value_type & element)
{
	std::cout << __PRETTY_FUNCTION__ << ": " << __LINE__ << '\n';
	for (; first != last; ++first)
		if (element == *first)
			return first;
	return last;
}


template <class Iterator, std::enable_if_t<is_random_access<Iterator>, int> = 0>
Iterator mysearch(Iterator first, Iterator last,
	const typename std::iterator_traits<Iterator>::value_type & element)
{
	std::cout << __PRETTY_FUNCTION__ << ": " << __LINE__ << '\n';
	while (first < last) {
		auto m = first + std::distance(first, last) / 2;
		if (element == *m) { return m; }
		if (element < *m)  { last = m; }
		if (element > *m)  { first = m; }
	}
	return last;
}


int main(int, char **)
{
	{
		std::vector<int> a = { 1, 2, 3, 4, 5 };
		auto i = mysearch(begin(a), end(a), 2);
		std::cout << "pos: " << std::distance(begin(a), i) << '\n';
	}
	{
		std::forward_list<int> a = { 1, 2, 3, 4, 5 };
		auto i = mysearch(begin(a), end(a), 4);
		std::cout << "pos: " << std::distance(begin(a), i) << '\n';
	}
	{
		std::list<int> a = { 1, 2, 3, 4, 5 };
		auto i = mysearch(begin(a), end(a), 4);
		std::cout << "pos: " << std::distance(begin(a), i) << '\n';
	}
	return 0;
}
