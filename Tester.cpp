#include "Tester.hpp"
#include "Heap.hpp"
#include "SortedDLL.hpp"
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <filesystem>
#include <vector>
namespace fs = std::filesystem;

// Funkcja do generowania losowych danych na podstawie ziarna
std::vector<int> generate_data(int N, int seed) {
	std::vector<int> data;
	std::mt19937 rng(seed);
	int limit = 3 * N;	// Ustawiamy limit na 3 razy większy niż ilość danych, aby zwiększyć różnorodność losowanych liczb
	std::uniform_int_distribution<int> dist(1, limit);	// Zakres losowanych liczb

	for (int i = 0; i < N; ++i) {
		data.push_back(dist(rng));	// Generujemy losową liczbę i zapisujemy ją do wektora
	}
	return data;
}

// Funkcja do wczytywania ziaren z pliku
std::vector<int> loadSeeds(const std::string filename) {
	std::vector<int> seeds;
	std::ifstream in(filename);
	int s;
	while (in >> s) {
		seeds.push_back(s);	// Wczytujemy kolejne ziarna z pliku i zapisujemy je do wektora
	}
	return seeds;
}

void test_structure(std::string structure, int N, std::string operation) {
	if (!fs::exists("output"))
		fs::create_directory("output");	// Tworzymy katalog output, jeśli nie istnieje

	// Jeśli plik results.csv nie istnieje, tworzymy go i zapisujemy nagłówki kolumn
	if (!fs::exists("output/results.csv")) {
		std::ofstream out("output/results.csv", std::ios::app);	// Otwieramy plik w trybie dopisywania, ale ponieważ plik nie istnieje, zostanie utworzony
		out << "Struktura; Operacja; Rozmiar; Seed";
		for (int i = 1; i <= 10; ++i) out << ";Time" << i;
		out << "\n";
	}
	std::ofstream out("output/results.csv", std::ios::app);
	std::vector<int> seeds = loadSeeds("seeds.txt");	// Wczytujemy ziarna z pliku seeds.txt

	for (int s_idx = 0; s_idx < seeds.size(); ++s_idx) {	// Dla każdego ziarna generujemy dane i mierzymy czas wykonania operacji
		int seed = seeds[s_idx];
		std::vector<int> data = generate_data(N, seed);	// Generujemy dane na podstawie ziarna
		long long times[10] = {};

		for (int i = 0; i < 10; ++i) {
			if (structure == "Heap") {
				Heap h;
				for (int d_idx = 0; d_idx < data.size(); ++d_idx) h.insert(d_idx + 1, data[d_idx]);	// Wstawiamy dane do kopca, gdzie wartość to indeks + 1 (unikalna dla każdego elementu), a priorytet to losowa liczba z danych
				long long t = measure_time([&]() {
					if (operation == "insert") h.insert(N+1, 10);
					else if (operation == "extract-max") h.extract_max();
					else if (operation == "peek") h.peek();
					else if (operation == "modify-key") h.modify_key(N,500);
					else if (operation == "return-size") h.return_size();
					});
				times[i] = t;	// Zapisujemy zmierzony czas do tablicy
			}
			else if (structure == "SortedDLL") {
				SortedDLL dll;
				for (int d_idx = 0; d_idx < data.size(); ++d_idx) dll.insertSDLL(d_idx + 1, data[d_idx]);	// Analogicznie wstawiamy dane do posortowanej listy dwukierunkowej
				long long t = measure_time([&]() {
					if (operation == "insert") dll.insertSDLL(N+1, 10);
					else if (operation == "extract-max") dll.extractMax();
					else if (operation == "peek") dll.findMax();
					else if (operation == "modify-key") dll.modifyKey(N,500);
					else if (operation == "return-size") dll.getSize();
					});
				times[i] = t;
			}
		}


		out << structure << ";" << operation << ";" << N << ";" << seed;	// Zapisujemy wyniki do pliku CSV
		for (int i = 0; i < 10; ++i) out << ";" << times[i];
		out << "\n";
	}
}