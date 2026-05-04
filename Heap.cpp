#include "Heap.hpp"
#include <iostream>

bool Heap::isLess(const Node& a, const Node& b) {	// Porównuje dwa elementy na podstawie priorytetu i identyfikatora wstawienia
	if (a.priority != b.priority) {
		return a.priority < b.priority;	// Porównuje priorytety
	}
	return a.insertion_id > b.insertion_id;	// Jeśli priorytety są równe, porównuje identyfikatory wstawienia
}

void Heap::heapifyUp(int i) {	// Przesuwa element w górę kopca, aby zachować właściwość kopca
	while (i > 0 && isLess(heap[parent(i)], heap[i])) {	// Dopóki element nie jest korzeniem i jego priorytet jest większy niż priorytet rodzica
		std::swap(heap[i], heap[parent(i)]);	// Jeśli priorytet jest większy, zamienia je miejscami
		i = parent(i);	// Przechodzi do indeksu rodzica
	}
}

void Heap::heapifyDown(int i) {	// Przesuwa element w dół kopca, aby zachować właściwość kopca
	int largest = i;
	int left = leftChild(i);
	int right = rightChild(i);
	if (left < heap.size() && isLess(heap[largest], heap[left])) {
		largest = left;	// Jeśli lewe dziecko ma większy priorytet, aktualizuje największy indeks
	}
	if (right < heap.size() && isLess(heap[largest], heap[right])) {
		largest = right;	// Jeśli prawe dziecko ma większy priorytet, aktualizuje największy indeks
	}
	if (largest != i) {
		std::swap(heap[i], heap[largest]);	// Zamienia miejscami element z największym priorytetem
		heapifyDown(largest);	// Rekurencyjnie wywołuje heapifyDown dla nowego indeksu
	}
}

void Heap::printHeap() const {	// Pomocnicza funkcja do debugowania, wyświetla zawartość kopca
	std::cout << "Heap contents:\n";
	for (const auto& node : heap) {
		std::cout << "Value: " << node.value << ", Priority: " << node.priority << ", Insertion ID: " << node.insertion_id << "\n";
	}
}

void Heap::insert(const int value, int priority) {	// Wstawia nowy element do kopca
	heap.push_back({ value, priority, counter++ });	//	Dodaje nowy element do końca wektora, przypisując mu wartość, priorytet i unikalny identyfikator wstawienia
	heapifyUp(heap.size() - 1);	// Przesuwa nowy element w górę, aby zachować właściwość kopca
}

int Heap::extract_max() {	// Usuwa element o najwyższym priorytecie z kopca
	if (heap.empty()) {
		throw std::runtime_error("Heap is empty");	// Rzuca wyjątek, jeśli kopiec jest pusty
	}

	int max_value = heap[0].value;	// Zapisuje wartość elementu o najwyższym priorytecie (korzenia)
	heap[0] = heap.back();	// Przenosi ostatni element na miejsce korzenia
	heap.pop_back();	// Usuwa ostatni element
	if (!heap.empty()) {
		heapifyDown(0);	// Przesuwa element w dół, aby zachować właściwość kopca
	}

	return max_value;	// Zwraca wartość elementu o najwyższym priorytecie
}

const int& Heap::peek() const {
	if (heap.empty()) {
		throw std::runtime_error("Heap is empty");	// Rzuca wyjątek, jeśli kopiec jest pusty
	}
	return heap[0].value;	// Zwraca wartość elementu o najwyższym priorytecie (korzenia) bez usuwania go z kopca
}

void Heap::modify_key(int value, int newPriority) {	// Zmienia priorytet elementu w kopcu
	int index = -1;
	for (int i = 0; i < heap.size(); i++) {
		if (heap[i].value == value) {	// Szuka elementu o podanej wartości
			index = i;
			break;
		}
	}

	if (index == -1) {
		throw std::runtime_error("modify_key: element not found");	// Rzuca wyjątek, jeśli element o podanej wartości nie został znaleziony
	}

	int oldPriority = heap[index].priority;	// Zapisuje stary priorytet elementu

	heap[index].priority = newPriority;

	if (newPriority > oldPriority) {
		heapifyUp(index);	// Jeśli nowy priorytet jest większy, przesuwa element w górę, aby zachować właściwość kopca
	}
	else if (newPriority < oldPriority) {
		heapifyDown(index);	// Jeśli nowy priorytet jest mniejszy, przesuwa element w dół, aby zachować właściwość kopca
	}
}


int Heap::return_size() const {
	return heap.size();	// Zwraca rozmiar kopca
}