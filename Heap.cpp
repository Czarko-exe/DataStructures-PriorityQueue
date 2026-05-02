#include "Heap.hpp"
#include <iostream>

void Heap::heapifyUp(int i) {	// Przesuwa element w górę kopca, aby zachować właściwość kopca
	while (i > 0 && heap[parent(i)].priority < heap[i].priority) {	// Porównuje priorytet elementu z jego rodzicem
		std::swap(heap[i], heap[parent(i)]);	// Jeśli priorytet jest większy, zamienia je miejscami
		i = parent(i);	// Przechodzi do indeksu rodzica
	}
}

void Heap::heapifyDown(int i) {	// Przesuwa element w dół kopca, aby zachować właściwość kopca
	int largest = i;
	int left = leftChild(i);
	int right = rightChild(i);
	if (left < heap.size() && heap[left].priority > heap[largest].priority) {
		largest = left;	// Jeśli lewe dziecko ma większy priorytet, aktualizuje największy indeks
	}
	if (right < heap.size() && heap[right].priority > heap[largest].priority) {
		largest = right;	// Jeśli prawe dziecko ma większy priorytet, aktualizuje największy indeks
	}
	if (largest != i) {
		std::swap(heap[i], heap[largest]);	// Zamienia miejscami element z największym priorytetem
		heapifyDown(largest);	// Rekurencyjnie wywołuje heapifyDown dla nowego indeksu
	}
}

void Heap::insert(const int value, int priority) {	// Wstawia nowy element do kopca
	heap.push_back({ value, priority });	// Dodaje nowy element na koniec wektora
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