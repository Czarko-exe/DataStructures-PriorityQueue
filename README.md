# Struktury Danych - Miniprojekt 2: Kolejka Priorytetowa (DataStructures-PriorityQueue)

Projekt zrealizowany w ramach przedmiotu **Struktury Danych**. Celem zadania była samodzielna implementacja abstrakcyjnej struktury kolejki priorytetowej (priority queue) typu MAX w języku C++ oraz przeprowadzenie empirycznych badań czasu wykonywania poszczególnych operacji. 

Projekt został zrealizowany w parach.

## 🛠 Zaimplementowane struktury danych

Zgodnie z wymogami projektu na ocenę 4.0-5.0, wdrożyliśmy następujące struktury:
1. **Kopiec maksymalny (Max Heap)** - struktura oparta na tablicy, działająca na zasadzie drzewa binarnego, w którym każdy węzeł ma wartość większą bądź równą wartościom swoich dzieci.
2. **Sortowana lista dwukierunkowa (Sorted Doubly Linked List)** - oparta na wskaźnikach `head`, `tail`, `prev` oraz `next`. Elementy są utrzymywane i przechowywane malejąco względem priorytetu, co zapewnia natychmiastowy dostęp do wartości maksymalnej.

## ⚙️ Badane operacje

Dla każdej z powyższych struktur przygotowaliśmy testy badające czas wykonywania następujących operacji:
* **`insert(e, p)`** - Dodanie elementu o wartości `e` i priorytecie `p`.
* **`extract-max()`** - Usunięcie i zwrócenie elementu o najwyższym priorytecie.
* **`find-max()` / `peek()`** - Podejrzenie elementu o najwyższym priorytecie (bez jego usuwania ze struktury).
* **`modify-key(e, p)`** - Zmiana priorytetu pierwszego napotkanego elementu o wartości `e` na nowy priorytet `p`.
* **`get-size()` / `return-size()`** - Zwrócenie aktualnego rozmiaru (liczby elementów) struktury.

## 🚀 Jak uruchomić projekt

Projekt został utworzony w środowisku Visual Studio.

1. Sklonuj repozytorium:
   ```bash
   git clone [https://github.com/Czarko-exe/DataStructures-PriorityQueue.git](https://github.com/Czarko-exe/DataStructures-PriorityQueue.git)
2. Otwórz plik rozwiązania (.sln / .slnx) w programie Visual Studio.

3. Skompiluj projekt (zalecane użycie trybu Release dla dokładniejszych wyników badań wydajnościowych).

4. Uruchom aplikację. Obsługa programów testujących odbywa się za pomocą interaktywnego menu w konsoli.

## 📊 Wyniki badań (Sprawozdanie)
* Z przeprowadzonych badań (dla zestawów danych od 1000 do 128 000 elementów) płyną następujące wnioski:Max Heap jest strukturą znacznie lepiej skalowalną. Operacje zależne od wysokości kopca (insert, modify-key) wykazały logarytmiczny wzrost czasu $O(\log n)$.
* Sorted DLL wypada lepiej jedynie dla bardzo małych zbiorów danych. Wraz ze wzrostem liczby elementów, operacje wymagające przejścia przez listę (insert, modify-key) zajmują znacznie więcej czasu ze względu na złożoność $O(n)$.
* Operacje stałoczasowe (peek, get-size) wykazały minimalne różnice między strukturami, potwierdzając teoretyczną złożoność $O(1)$.

## 👨‍💻 Autorzy
[github.com/Czarko-exe](github.com/Czarko-exe)  
[github.com/R0-0F](github.com/R0-0F)
