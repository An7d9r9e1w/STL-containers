# STL-containers
The Standard Template Library (STL) is a standard C++ library that provides structures and algorithms for storing and manipulating data of any type.
These structures and methods are encapsulated in containers.
Some of them was reimplemented in this study project:
1. Vector
2. Stack
3. Map
4. Set

### Vector
The vector is a dynamically expanding array. It allows you to quickly get data by index or remove the last element,
but takes some time when you need to add data to the end of the container,
and takes much longer when you want to add new element anywhere in the container or remove an element from there.

Time complexity:
  Function  |Amortized|Worst Case
|-----------|---------|---------|
**Search**	|	*O*(1)  | *O*(1)
**Insert**	|	*O*(n)  |	*O*(n)
**Delete**	|	*O*(n)  |	*O*(n)

> n is the amount of elements in the container

### Stack
The stack itself is not a container, but contains one inside and provides an interface
for interacting with it according to FILO (first in, last out) rule.
It means you only have access to the last (top) element of the stack.
The vector can act as an internal stack container.

### Map
The map is a container consisting of key/value pairs. Unlike an array, keys in a map can be of any data type.
The map is implemented via a [red-black tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree "Red-Black tree"),
that is a kind of self-balancing binary search tree. Due to the last fact, elements in a map are already sorted.
The map is a compromise between searching speed and insert/delete speed.
Searching operations in a map are slower compared to a vector, but insert and delete operations are much faster.

Time complexity:
  Function  |  Amortized  |Worst Case
|-----------|-------------|---------|
**Search**	|	*O*(log n)  | *O*(log n)
**Insert**	|	*O*(1)      |	*O*(log n)
**Delete**	|	*O*(1)      |	*O*(log n)

### Set
The set is similar to a map, but does not consist of pairs, but only of keys.

## Tests
Unit tests was implemented to test this project.
The main source for implementation is [GoogleTest](https://github.com/google/googletest "GoogleTest") framework.

In order to run tests:
1. Download googletest and prepare the build system: `cmake -S . -B build`
2. Run the build system and wait for it to complete: `cmake --build build`
3. Run tests: `./build/stl_tests`
