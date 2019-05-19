#include <iterator>
#include <type_traits>
#include <iostream>
#include <vector>
#include <forward_list>
#include <list>

// NOTE: only for demonstration purposes


template <class Iterator>
concept bool HasForwardIteratorTag = std::is_same_v<std::forward_iterator_tag,
	typename std::iterator_traits<Iterator>::iterator_category>;

template <class Iterator>
concept bool HasBidirectionalIteratorTag = std::is_same_v<std::bidirectional_iterator_tag,
	typename std::iterator_traits<Iterator>::iterator_category>;


template <class Iterator>
concept SimpleIterator = requires(Iterator i)
{
	typename Iterator::value_type;
	requires HasForwardIteratorTag<Iterator> || HasBidirectionalIteratorTag<Iterator>;
};

template <class Iterator>
concept RandomAccessIterator = requires(Iterator i, typename std::iterator_traits<Iterator>::difference_type n)
{
	typename Iterator::value_type;
	{ ++i    } -> Iterator&;
	{ i++    } -> Iterator;
	{ *i     } -> Iterator::value_type&;
	{ i != i } -> bool;
	{ i < i  } -> bool;
	{ i = i  } -> Iterator&;
	{ i + n  } -> Iterator;
	{ i - n  } -> Iterator;
	{ i += n } -> Iterator&;
	{ i -= n } -> Iterator&;
	{ i - i  } -> decltype(n);
};


template <SimpleIterator It>
auto mysearch(It first, It last, const typename It::value_type & element) -> It
{
	std::cout << __PRETTY_FUNCTION__ << ": " << __LINE__ << '\n';
	for (; first != last; ++first)
		if (element == *first)
			return first;
	return last;
}

template <RandomAccessIterator It>
auto mysearch(It first, It last, const typename It::value_type & element) -> It
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
		auto i = mysearch(begin(a), end(a), 4);
		std::cout << "pos: " << std::distance(i, end(a)) << '\n';
	}
	{
		std::forward_list<int> a = { 1, 2, 3, 4, 5 };
		auto i = mysearch(begin(a), end(a), 3);
		std::cout << "pos: " << std::distance(i, end(a)) << '\n';
	}
	{
		std::list<int> a = { 1, 2, 3, 4, 5 };
		auto i = mysearch(begin(a), end(a), 3);
		std::cout << "pos: " << std::distance(i, end(a)) << '\n';
	}
	return 0;
}
