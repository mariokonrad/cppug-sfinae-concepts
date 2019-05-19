.PHONY: all
all : \
	cxx98-sfinae \
	cxx11-sfinae \
	cxx17-sfinae \
	cxx17-constexprif \
	cxx20-concepts \
	cxx98-detection-idiom \
	cxx11-detection-idiom \
	cxx17-detection-idiom \
	cxx20-detection-concepts \
	overloadset

.PHONY: examples
examples : \
	ex1-cxx17 \
	ex1-cxx20 \
	ex2-cxx20

cxx98-sfinae : src/cxx98-sfinae.cpp
	$(CXX) -std=c++98 -Wall -Wextra $< -o $@

cxx11-sfinae : src/cxx11-sfinae.cpp
	$(CXX) -std=c++11 -Wall -Wextra $< -o $@

cxx17-sfinae : src/cxx17-sfinae.cpp
	$(CXX) -std=c++17 -Wall -Wextra $< -o $@

cxx17-constexprif : src/cxx17-constexprif.cpp
	$(CXX) -std=c++17 -Wall -Wextra $< -o $@

cxx20-concepts : src/cxx20-concepts.cpp
	$(CXX) -std=c++2a -Wall -Wextra -fconcepts $< -o $@

cxx98-detection-idiom : src/cxx98-detection-idiom.cpp
	$(CXX) -std=c++98 -Wall -Wextra $< -o $@

cxx11-detection-idiom : src/cxx11-detection-idiom.cpp
	$(CXX) -std=c++11 -Wall -Wextra $< -o $@

cxx17-detection-idiom : src/cxx17-detection-idiom.cpp
	$(CXX) -std=c++17 -Wall -Wextra $< -o $@

cxx20-detection-concepts : src/cxx20-detection-concepts.cpp
	$(CXX) -std=c++2a -Wall -Wextra -fconcepts $< -o $@

overloadset : src/overloadset.cpp
	$(CXX) -Wall -Wextra $< -o $@

slides.pdf : doc/slides.md
	pandoc -t beamer $^ -o $@

ex1-cxx17 : src/ex1/cxx17.cpp
	$(CXX) -std=c++17 -Wall -Wextra $< -o $@

ex1-cxx20 : src/ex1/cxx20.cpp
	$(CXX) -std=c++2a -Wall -Wextra -fconcepts $< -o $@

ex2-cxx20 : src/ex2/cxx20.cpp
	$(CXX) -std=c++2a -Wall -Wextra -fconcepts $< -o $@

.PHONY: clean
clean :
	rm -f *.o
	rm -f cxx98-sfinae
	rm -f cxx11-sfinae
	rm -f cxx17-sfinae
	rm -f cxx17-constexprif
	rm -f cxx20-concepts
	rm -f cxx98-detection-idiom
	rm -f cxx11-detection-idiom
	rm -f cxx17-detection-idiom
	rm -f cxx20-detection-concepts
	rm -f overloadset
	rm -f slides.pdf
	rm -f ex1-cxx17
	rm -f ex1-cxx20
	rm -f ex2-cxx20

