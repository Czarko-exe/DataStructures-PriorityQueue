#include <iostream>
#include <string>
#include "menu.hpp"
//#include "Tester.hpp"

int menu() {
	bool running = true;	// Flaga kontrolująca działanie menu
	bool amount_menu = false;	// Flaga kontrolująca wyświetlanie menu wyboru ilości danych
	bool function_menu = false;	//	Flaga kontrolująca wyświetlanie menu wyboru funkcji
	int choice;	// Zmienna przechowująca wybór użytkownika
	std::string structure;	// Zmienna przechowująca wybraną strukturę danych
	int amount;	// Zmienna przechowująca wybraną ilość danych
	std::string function;	// Zmienna przechowująca wybraną funkcję do testowania

	while (running) {
		// Wyświetlanie głównego menu
		std::cout << "=====MENU=====" << std::endl;
		std::cout << "1. Test everything" << std::endl;
		std::cout << "2. Heap" << std::endl;
		std::cout << "3. Doubly Linked List" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << std::endl;
		std::cin >> choice;
		switch (choice) {
		case 1:
			structure = "All";
			break;
		case 2:
			structure = "Heap";
			break;
		case 3:
			structure = "Doubly_Linked_List";
			break;
		case 0:
			running = false;
			break;
		default:
			std::cerr << "Incorrect choice" << std::endl;
			break;
		}
		if (0 < choice && choice < 4) {	// Jeśli użytkownik wybrał poprawną opcję, przechodzimy do menu wyboru ilości danych
			amount_menu = true;
		}

		while (amount_menu) {
			// Wyświetlanie menu wyboru ilości danych
			std::cout << "Select data amount:" << std::endl;
			std::cout << "1. 1000" << std::endl;
			std::cout << "2. 2000" << std::endl;
			std::cout << "3. 4000" << std::endl;
			std::cout << "4. 8000" << std::endl;
			std::cout << "5. 16000" << std::endl;
			std::cout << "6. 32000" << std::endl;
			std::cout << "7. 64000" << std::endl;
			std::cout << "8. 128000" << std::endl;
			std::cout << "9. All" << std::endl;
			std::cout << "0. Back" << std::endl;
			std::cout << std::endl;
			std::cin >> choice;
			switch (choice) {
			case 1:
				amount = 1000;
				break;
			case 2:
				amount = 2000;
				break;
			case 3:
				amount = 4000;
				break;
			case 4:
				amount = 8000;
				break;
			case 5:
				amount = 16000;
				break;
			case 6:
				amount = 32000;
				break;
			case 7:
				amount = 64000;
				break;
			case 8:
				amount = 128000;
				break;
			case 9:
				amount = -1;	// Używamy -1 jako specjalnej wartości oznaczającej "All"
				break;
			case 0:
				amount_menu = false;
				break;
			default:
				std::cerr << "Incorrect choice" << std::endl;
				break;
			}

			if (0 < choice && choice < 10) {	// Jeśli użytkownik wybrał poprawną opcję, przechodzimy do menu wyboru funkcji
				amount_menu = false;
				function_menu = true;
			}
		}


		while (function_menu) {
			// Wyświetlanie menu wyboru funkcji do testowania
			std::cout << "Select function:" << std::endl;
			std::cout << "1. All" << std::endl;
			std::cout << "2. Insert(e,p)" << std::endl;
			std::cout << "3. Extract-max()" << std::endl;
			std::cout << "4. Peek()" << std::endl;
			std::cout << "5. Modify-key(e,p)" << std::endl;
			std::cout << "6. Return-size" << std::endl;
			std::cout << "0. Back" << std::endl;
			std::cout << std::endl;
			std::cin >> choice;
			switch (choice) {
			case 1:
				function = "All";
				break;
			case 2:
				function = "insert";
				break;
			case 3:
				function = "extract-max";
				break;
			case 4:
				function = "peek";
				break;
			case 5:
				function = "modify-key";
				break;
			case 6:
				function = "return-size";
				break;
			case 0:
				function_menu = false;
				break;
			default:
				std::cerr << "Incorrect choice" << std::endl;
				break;
			}

			if (0 < choice && choice < 7) {	// Jeśli użytkownik wybrał poprawną opcję, przechodzimy do testowania
				function_menu = false;
			}
		}
		std::string structures[] = { // Lista dostępnych struktur danych
			"Heap",
			"Doubly_Linked_List"
		};

		int amounts[] = { // Lista dostępnych ilości danych do testowania
			1000,
			2000,
			4000,
			8000,
			16000,
			32000,
			64000,
			128000
		};

		std::string functions[] = { // Lista dostępnych funkcji do testowania
			"insert",
			"extract-max",
			"peek",
			"modify-key",
			"return-size"
		};

		if (structure != "" && function != "" && amount != 0) {	// Jeśli użytkownik wybrał wszystkie opcje, przechodzimy do testowania
			running = false;
			if (structure == "All") {
				if (amount == -1) {
					if (function == "All") {
						for (const auto& s : structures) {
							for (const auto& a : amounts) {
								for (const auto& f : functions) {
									//test_structure(s, a, f);	// Testujemy każdą strukturę danych z każdą ilością danych i każdą funkcją
								}
							}
						}
					}
					else {
						for (const auto& s : structures) {
							for (const auto& a : amounts) {
								//test_structure(s, a, function);	// Testujemy każdą strukturę danych z każdą ilością danych i wybraną funkcją
							}
						}
					}
				}
				else if (function == "All") {
					for (const auto& s : structures) {
						for (const auto& f : functions) {
							//test_structure(s, amount, f);	// Testujemy każdą strukturę danych z wybraną ilością danych i każdą funkcją
						}
					}
				}
				else {
					for (const auto& s : structures) {
						//test_structure(s, amount, function);	// Testujemy każdą strukturę danych z wybraną ilością danych i wybraną funkcją
					}
				}
			}
			else if (amount == -1) {
				if (function == "All") {
					for (const auto& a : amounts) {
						for (const auto& f : functions) {
							//test_structure(structure, a, f);	// Testujemy wybraną strukturę danych z każdą ilością danych i każdą funkcją
						}
					}
				}
				else {
					for (const auto& a : amounts) {
						//test_structure(structure, a, function);	// Testujemy wybraną strukturę danych z każdą ilością danych i wybraną funkcją
					}
				}
			}
			else if (function == "All") {
				for (const auto& f : functions) {
					//test_structure(structure, amount, f);	// Testujemy wybraną strukturę danych z wybraną ilością danych i każdą funkcją
				}
			}
			else {
				//test_structure(structure, amount, function);	// Testujemy wybraną strukturę danych z wybraną ilością danych i wybraną funkcją
			}
		}

	}

	return 0;
}