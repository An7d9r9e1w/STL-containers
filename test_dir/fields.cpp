#include <iostream>
#include <vector>

int main()
{
	const int size = 10;
	const int size2 = 5;
	std::vector<int> v(size);
	v.resize(size2);
	for (int i = 0; i < size2; ++i)
		v[i] = i + 1;

	std::cout << "data[" << v.data() << "]\n"
		<< "    [" << *((size_t*)&v + 2) << "]\n";
	return 0;
}
