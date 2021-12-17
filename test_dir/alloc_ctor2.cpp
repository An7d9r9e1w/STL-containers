#include <iostream>
#include <string>
#include <memory>

int main()
{
	std::allocator<std::string> alloc;

	std::string* str1 = alloc.allocate(1);
	std::string* str2 = alloc.allocate(1);

	alloc.construct(str1, "Hello, world");
	alloc.construct(str2, *str1);
	std::cout << *str1 << '\n' << *str2 << '\n';
	alloc.destroy(str2);
	alloc.destroy(str1);
	alloc.deallocate(str2, 1);
	alloc.deallocate(str1, 1);
	return 0;
}
