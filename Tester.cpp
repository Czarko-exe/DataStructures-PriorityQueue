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
	int limit = 2 * N;	// Ustawiamy limit na 2 razy większy niż ilość danych, aby zwiększyć różnorodność losowanych liczb
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

		//tester elo


		out << structure << ";" << operation << ";" << N << ";" << seed;	// Zapisujemy wyniki do pliku CSV
		for (int i = 0; i < 10; ++i) out << ";" << times[i];
		out << "\n";
	}
}