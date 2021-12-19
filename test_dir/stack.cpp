// stack::push/pop
#include <iostream>       // std::cout
#include <stack>          // std::stack

#include "../stack.hpp"

template <class Stack>
void test()
{
  Stack mystack;

  for (int i=0; i<5; ++i) mystack.push(i);

  std::cout << "Popping out elements...";
  while (!mystack.empty())
  {
     std::cout << ' ' << mystack.top();
     mystack.pop();
  }
  std::cout << '\n';
}

int main()
{
	test<std::stack<int> >();
	test<ft::stack<int> >();
	return 0;
}
