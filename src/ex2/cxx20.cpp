#include <iostream>
#include <string>
#include <vector>

// NOTE: only for demonstration purposes


class person
{
public:
	person(const std::string & name, int age = 0)
		: name_(name)
		, age_(age)
	{}

	int age() const { return age_; }
	const std::string & name() const { return name_; }

private:
	std::string name_;
	int age_ = 0;
};


template <class T>
concept PersonElement = requires(T p)
{
	{ p.name() } -> std::string;
};


template <class T, class U>
concept EqualityComparable = requires(T t, U u)
{
	{ t == u } -> bool;
};


template <class Iterator, class Element = typename std::iterator_traits<Iterator>::value_type>
	requires EqualityComparable<Element, Element>
Iterator mysearch(Iterator first, Iterator last, const Element & element)
{
	std::cout << __PRETTY_FUNCTION__ << ": " << __LINE__ << '\n';
	for (; first != last; ++first)
		if (element == *first)
			return first;
	return last;
}

template <class Iterator, class Element = typename std::iterator_traits<Iterator>::value_type>
	requires PersonElement<Element>
Iterator mysearch(Iterator first, Iterator last, const Element & element)
{
	std::cout << __PRETTY_FUNCTION__ << ": " << __LINE__ << '\n';
	for (; first != last; ++first)
		if (element.name() == first->name())
			return first;
	return last;
}


template <class Iterator, PersonElement Element>
Iterator mysearch2(Iterator first, Iterator last, const Element & element)
{
	std::cout << __PRETTY_FUNCTION__ << ": " << __LINE__ << '\n';
	for (; first != last; ++first)
		if (element.name() == first->name())
			return first;
	return last;
}


int main(int, char **)
{
	{
		std::vector<int> a = { 5, 2, 7, 4, 6, 1, 3 };
		auto i = mysearch(begin(a), end(a), 6);
		std::cout << "pos: " << std::distance(begin(a), i) << '\n';
	}
	{
		std::vector<person> a = { {"Bjarne", 65}, {"Herb", 58}, {"Scott", 55} };
		auto i = mysearch(begin(a), end(a), person("Herb"));
		std::cout << "pos: " << std::distance(begin(a), i) << '\n';
	}
	{
		std::vector<person> a = { {"Bjarne", 65}, {"Herb", 58}, {"Scott", 55} };
		auto i = mysearch2(begin(a), end(a), person("Herb"));
		std::cout << "pos: " << std::distance(begin(a), i) << '\n';
	}
	return 0;
}
