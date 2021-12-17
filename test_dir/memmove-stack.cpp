#include <iostream>
#include <cstring>

int main()
{
	char str1[] = "Hello, world";

	std::cout << "1: " << str1 << '\n';

	const int size = sizeof(str1) / sizeof(char);
	char str2[size] = { 0 };

	std::memmove(str2, str1, size);
	std::cout << "2: " << str2 << '\n';

	std::memset(str1, 0, size);
	std::cout << "1: " << str1 << '\n';
	std::cout << "2: " << str2 << '\n';

	return 0;
}
