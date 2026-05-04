#include <iostream>
#include "Heap.hpp"

int main()
{
	Heap h;
	h.insert(10, 1); // ID 0
	h.insert(20, 1); // ID 1
	h.insert(30, 1); // ID 2

	h.modify_key(30, 1); // priorytet taki sam — kolejność nie powinna się zmienić

	std::cout << h.extract_max() << "\n"; // 10
	std::cout << h.extract_max() << "\n"; // 20
	std::cout << h.extract_max() << "\n"; // 30


}
