#pragma once
#include <chrono>
#include <string>
#include <vector>

std::vector<int> generate_data(int N, int seed);
std::vector<int> loadSeeds(const std::string filename);
void test_structure(std::string structure, int N, std::string operation);

template<typename Func> // Funkcja do mierzenia czasu wykonania operacji
long long measure_time(Func f) {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(); // Zwraca czas w nanosekundach
}