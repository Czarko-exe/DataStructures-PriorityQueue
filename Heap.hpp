#pragma once
#include "DynamicArray.hpp"

class Heap {
private:
	struct Node {	// Reprezentuje element w kopcu, zawiera wartość i priorytet
		int value;
		int priority;
		int insertion_id;	// Unikalny identyfikator wstawienia, używany do rozstrzygania konfliktów priorytetów
	};

	DynamicArray<Node> heap;	// Dynamiczna tablica przechowująca elementy kopca
	int heapSize;	// Aktualny rozmiar kopca
	int counter = 0;	// Licznik wstawień, używany do przypisywania unikalnych identyfikatorów wstawienia

	int parent(int index) const { return (index - 1) / 2; }		// Zwraca indeks rodzica dla danego indeksu
	int leftChild(int index) const { return 2 * index + 1; }	// Zwraca indeks lewego dziecka dla danego indeksu
	int rightChild(int index) const { return 2 * index + 2; }	// Zwraca indeks prawego dziecka dla danego indeksu

	bool isLess(const Node& a, const Node& b);	// Porównuje dwa elementy na podstawie priorytetu i identyfikatora wstawienia
	void heapifyUp(int index);	// Przesuwa element w górę kopca, aby zachować właściwość kopca
	void heapifyDown(int index);	// Przesuwa element w dół kopca, aby zachować właściwość kopca
public:
	Heap() : heapSize(0), counter(0) {}	// Konstruktor inicjalizujący rozmiar kopca i licznik wstawień

	void printHeap() const;	// Pomocnicza funkcja do debugowania, wyświetla zawartość kopca

	void insert(const int value, int priority);	// Wstawia nowy element do kopca
	int extract_max();	// Usuwa element o najwyższym priorytecie z kopca
	const int& peek() const;	// Zwraca element o najwyższym priorytecie bez usuwania go z kopca
	void modify_key(int value, int new_priority);	// Zmienia priorytet elementu w kopcu
	int return_size() const;	// Zwraca rozmiar kopca
};