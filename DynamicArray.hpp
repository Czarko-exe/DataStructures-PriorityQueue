#pragma once
#include <algorithm>
#include <iostream>

template<typename T>
class DynamicArray {
public:
	DynamicArray(); //Konstruktor
	~DynamicArray(); //Destruktor
	DynamicArray(const DynamicArray& other);	//Konstruktor kopiujący

	void pushFront(const T& value); //Dodaje element na początek tablicy
	void pushBack(const T& value);	//Dodaje element na koniec tablicy
	void pushAt(int index, const T& value); //Dodaje element na określonej pozycji w tablicy
	
	void popFront(); //Usuwa pierwszy element z tablicy
	void popBack(); //Usuwa ostatni element z tablicy
	void popAt(int index); //Usuwa element z określonej pozycji w tablicy

	T& operator[](int index);	//Przeciążenie operatora [], umożliwiające dostęp do elementów tablicy za pomocą indeksu
	const T& operator[](int index) const;	//Przeciążenie operatora [] dla stałych obiektów, umożliwiające dostęp do elementów tablicy za pomocą indeksu

	T get(int index) const;	//Zwraca wartość elementu na określonej pozycji w tablicy
	void set(int index, const T& value);	//Zmienia wartość elementu na określonej pozycji w tablicy
	void swap(int i, int j);	//Zamienia miejscami dwa elementy w tablicy

	int getSize() const { return size; }	//Zwraca aktualny rozmiar tablicy

private:
	T* data; //Wskaźnik na dynamiczną tablicę
	int size; //Aktualny rozmiar tablicy
	int capacity; //Aktualna pojemność tablicy

	void resize(); //Funkcja do zmiany rozmiaru tablicy, gdy jest pełna
};

template<typename T>
DynamicArray<T>::DynamicArray() : data(nullptr), size(0), capacity(0) {} // Konstruktor inicjalizujący wskaźnik na tablicę jako nullptr, rozmiar jako 0 i pojemność jako 4

template<typename T>
DynamicArray<T>::~DynamicArray() { // Destruktor zwalniający pamięć zajmowaną przez tablicę
	delete[] data;
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other) : size(other.size), capacity(other.capacity)	// Konstruktor kopiujący, który tworzy nową tablicę o tej samej pojemności i kopiuje elementy z innej tablicy
{
	if (capacity == 0) {
		data = nullptr;
		return;
	}

	data = new T[capacity];	// Alokujemy nową tablicę o tej samej pojemności
	std::copy(other.data, other.data + size, data);	// Kopiujemy elementy z innej tablicy do nowej tablicy
}

template<typename T>
void DynamicArray<T>::pushFront(const T& value) {
	if (size == capacity) { // Sprawdzamy czy tablica jest pełna
		resize(); // Jeśli tak, to zwiększamy jej pojemność
	}
	for (int i = size - 1; i >= 0; --i) { // Przesuwamy wszystkie elementy o jedno miejsce w prawo
		data[i + 1] = data[i];
	}
	data[0] = value; // Dodajemy nowy element na początek tablicy
	size++; // Zwiększamy rozmiar
}

template<typename T>
void DynamicArray<T>::pushBack(const T& value) {
	if (size == capacity) { // Sprawdzamy czy tablica jest pełna
		resize(); // Jeśli tak, to zwiększamy jej pojemność
	}
	data[size++] = value; // Dodajemy nowy element na koniec tablicy i zwiększamy rozmiar
}

template<typename T>
void DynamicArray<T>::pushAt(int index, const T& value) {
	if (index < 0 || index > size) return;
	if (index == 0) {	// Jeśli indeks to 0, dodajemy element na początek tablicy
		pushFront(value);
	}
	else if (index == size) {	// Jeśli indeks to rozmiar, dodajemy element na koniec tablicy
		pushBack(value);
	}
	else {
		if (size == capacity) {
			resize();
		}
		for (int i = size; i > index; --i) {	// Przesuwamy wszystkie elementy od indeksu do końca o jedno miejsce w prawo
			data[i] = data[i - 1];
		}
		data[index] = value;
		++size;
	}
}

template<typename T>
void DynamicArray<T>::popFront() {
	if (size > 0) {
		for (int i = 0; i < size - 1; i++) { // Przesuwamy wszystkie elementy o jedno miejsce w lewo
			data[i] = data[i + 1];
		}
		size--; // Zmniejszamy rozmiar
	}
}

template<typename T>
void DynamicArray<T>::popBack() {
	if (size > 0) {
		size--; // Zmniejszamy rozmiar, usuwając ostatni element
	}
}

template<typename T>
void DynamicArray<T>::popAt(int index) {
	if (index < 0 || index >= size) return;
	if (index == 0) {	// Jeśli indeks to 0, usuwamy element z początku tablicy
		popFront();
	}
	else if (index == size - 1) {	// Jeśli indeks to rozmiar - 1, usuwamy element z końca tablicy
		popBack();
	}
	else {
		for (int i = index; i < size - 1; i++) {	// Przesuwamy wszystkie elementy od indeksu do końca o jedno miejsce w lewo
			data[i] = data[i + 1];
		}
		size--;
	}
}

template<typename T>
void DynamicArray<T>::resize() {
	if (capacity == 0) {
		capacity = 1; // Jeśli pojemność jest 0, ustawiamy ją na 1
	}
	else {
		capacity *= 2; // Podwajamy pojemność
	}

	T* newData = new T[capacity];
	if (data) {
		std::copy(data, data + size, newData);
	}
	delete[] data;
	data = newData;
}

template<typename T>
T& DynamicArray<T>::operator[](int index) {	// Przeciążenie operatora [], umożliwiające dostęp do elementów tablicy za pomocą indeksu
	return data[index];
}

template<typename T>
const T& DynamicArray<T>::operator[](int index) const {	// Przeciążenie operatora [] dla stałych obiektów, umożliwiające dostęp do elementów tablicy za pomocą indeksu
	return data[index];
}

template<typename T>
T DynamicArray<T>::get(int index) const {	// Zwraca wartość elementu na określonej pozycji w tablicy
	return data[index];
}

template<typename T>
void DynamicArray<T>::set(int index, const T& value) {	// Zmienia wartość elementu na określonej pozycji w tablicy
	data[index] = value;
}

template<typename T>
void DynamicArray<T>::swap(int i, int j) {	// Zamienia miejscami dwa elementy w tablicy
	T temp = data[i];
	data[i] = data[j];
	data[j] = temp;
}
