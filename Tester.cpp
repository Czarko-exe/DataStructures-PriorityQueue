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
		std::vector<int> insert_prio = generate_data(N, 9676);	// Generujemy 10 losowych liczb, które posłużą do testowania różnych operacji (np. modyfikacji klucza)
		std::vector<int> modify_value = generate_data(N / 3, 3245);	// Generujemy N/3 losowych liczb, które posłużą do testowania różnych operacji (np. modyfikacji klucza)
		std::vector<int> modify_prio = generate_data(N, 2167);	// Generujemy 10 losowych liczb, które posłużą do testowania różnych operacji (np. modyfikacji klucza)
		if (structure == "Heap") {
			Heap baseHeap;	// Tworzymy bazowy kopiec, do którego wstawiamy dane, aby mieć je gotowe do testowania operacji na kopcu
			for (int d_idx = 0; d_idx < data.size(); ++d_idx) baseHeap.insert(d_idx + 1, data[d_idx]);
			for (int i = 0; i < 10; ++i) {
				std::cout << "Testing " << structure << " with operation " << operation << " for N = " << N << " and seed = " << seed << " (Test " << i + 1 << "/10)" << std::endl;
				Heap h = baseHeap;
				long long t = measure_time([&]() {
					if (operation == "insert") h.insert(N+1, insert_prio[i]);
					else if (operation == "extract-max") h.extract_max();
					else if (operation == "peek") h.peek();
					else if (operation == "modify-key") h.modify_key(modify_value[i], modify_prio[i]);
					else if (operation == "return-size") h.return_size();
					});
				times[i] = t;	// Zapisujemy zmierzony czas do tablicy
				std::cout << "Time: " << times[i] << " ns" << std::endl;	// Wyświetlamy zmierzony czas na konsoli
			}
		}
		else if (structure == "SortedDLL") {
			SortedDLL baseDLL;	// Tworzymy bazową listę dwukierunkową, do której wstawiamy dane, aby mieć je gotowe do testowania operacji na liście
			for (int d_idx = 0; d_idx < data.size(); ++d_idx) baseDLL.insertSDLL(d_idx + 1, data[d_idx]);
			for (int i = 0; i < 10; ++i) {
				std::cout << "Testing " << structure << " with operation " << operation << " for N = " << N << " and seed = " << seed << " (Test " << i + 1 << "/10)" << std::endl;
				SortedDLL dll = baseDLL;
				long long t = measure_time([&]() {
					if (operation == "insert") dll.insertSDLL(N+1, insert_prio[i]);
					else if (operation == "extract-max") dll.extractMax();
					else if (operation == "peek") dll.findMax();
					else if (operation == "modify-key") dll.modifyKey(modify_value[i], modify_prio[i]);
					else if (operation == "return-size") dll.getSize();
					});
				times[i] = t;
				std::cout << "Time: " << times[i] << " ns" << std::endl;	// Wyświetlamy zmierzony czas na konsoli
			}
		}
		out << structure << ";" << operation << ";" << N << ";" << seed;	// Zapisujemy wyniki do pliku CSV
		for (int i = 0; i < 10; ++i) out << ";" << times[i];
		out << "\n";
	}
}