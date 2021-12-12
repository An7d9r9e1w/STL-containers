#include <iostream>
#include <stdexcept>

int main()
{
	try {
		throw std::bad_alloc();
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	return 0;
}
