#include <vector>
#include <iostream>
#include <cstddef>
#include <string>
#include <limits>

const char* separate(unsigned long long n)
{
    static char buf[64];

    int i = sizeof(buf) - 1;
	int j = 0;
    buf[i] = '\0';

    do {
        buf[--i] = '0' + (n % 10);
        if (j++ % 3 == 2)
            buf[--i] = '\'';
    } while (n /= 10);

    return buf + i + (buf[i] == '\'' ? 1 : 0);
}

template <class T>
size_t max_size()
{
	size_t type_size = sizeof(T);
	if (type_size == 1) type_size = 2;
	return std::numeric_limits<size_t>::max() / type_size;
}

template <class T>
void test(const std::string& prompt)
{
    std::vector<T> v;
	std::cout << prompt << '[' << sizeof(T)
	<< "]\nmax[" << separate(v.max_size())
	<< "]\nmax[" << separate(max_size<T>()) << "]\n\n";
}

int main()
{
	test<bool>("bool");
	test<char>("char");
	test<short>("short");
	test<int>("int");
	test<double>("double");
	test<long double>("long double");
	test<std::string>("std::string");
	return 0;
}
