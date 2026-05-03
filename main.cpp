#include <iostream>
#include "Heap.hpp"

int main()
{
	Heap kolejka;
	kolejka.insert(10, 1);
	kolejka.insert(20, 2);
	kolejka.insert(15, 1);
	kolejka.insert(30, 3);
	kolejka.insert(25, 2);
	std::cout << "Peek: " << kolejka.peek() << std::endl;
	for (int i = 0; i < 5; ++i) {
		std::cout << "Extracted max: " << kolejka.extract_max() << std::endl;
	}
}
