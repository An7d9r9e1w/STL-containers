#include <iostream>
#include <cstdio>

#include <vector>
#include <stack>

#include "../vector.hpp"
#include "../stack.hpp"

template <class Stack>
void test()
{
	Stack s;
	s.push(17);
	s.push(5);
	s.push(0);
	s.push(354);
	s.push(96);
	while (!s.empty()) {
		std::cout << s.top() << ' ';
		s.pop();
	}
	std::cout << '\n';
}

int main()
{
	test<std::stack<int, std::vector<int> > >();
	test<std::stack<int, ft::vector<int> > >();
	test<ft::stack<int, std::vector<int> > >();
	test<ft::stack<int, ft::vector<int> > >();
	std::getchar();
	return 0;
}
