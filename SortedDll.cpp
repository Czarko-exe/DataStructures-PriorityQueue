#include "SortedDLL.hpp"
#include <iostream>
using namespace std;

SortedDLL::SortedDLL() {    //konstruktor
    head = nullptr;
    tail = nullptr;
    size = 0;
}

SortedDLL::~SortedDLL() {   //destruktor
    DLLNode* current = head;    //przechodzimy przez wszystkie node'y od heada

    while(current != nullptr) { //aż do końca
        DLLNode* nextNode = current -> next;
        delete current;
        current = nextNode;     //tworzymy nexta, usuwamy currenta, podmieniamy je
    }

    head = nullptr;             //zerujemy parametry
    tail = nullptr;
    size = 0;
}

void SortedDLL::insertSDLL(int value, int priority) {
    DLLNode* newNode = new DLLNode(value, priority);    //tworzymy nowy węzeł

    if(head == nullptr) {                                  //przypadek pustej listy        
        head = tail = newNode;                          //ustawiamy wskaźniki
        size++;                                         //zwiększamy rozmiar
        return;
    }

    if(priority > head -> priority) {                   //przypadek gdy new ma największe priority
        newNode -> next = head;                         //przepinamy wskaźniki
        head -> prev = newNode;
        head = newNode;                                 //ustawiamy nowy head
        size++;                                         //zwiększamy rozmiar
        return;
    }

    if(priority <= tail -> priority) {                  //przypadek gdy new ma najmniejsze priority
        tail -> next = newNode;                         //przepinamy wskaźniki
        newNode -> prev = tail;
        tail = newNode;                                 //wstawiamy nowy tail
        size++;                                         //zwiększamy rozmiar
        return;
    }

    DLLNode* current = head;                            //przypadek 'standardowy'

    while(current != nullptr && current -> priority >= priority) {
        current = current -> next;                      //iterujemy po wszystkich node'ach
    }                                                   //aż znajdziemy taki który ma priority mniejsze od szukanego

    DLLNode* prevNode = current -> prev;                //bierzemy element o jeden wcześniej

    prevNode -> next = newNode;                         //wcisamy pomiędzy nie nasz newNode
    newNode -> prev = prevNode;                         //odpowiednio przepinamy wskaźniki
    newNode -> next = current;
    current -> prev = newNode;

    size++;
}

int SortedDLL::findMax() const {
    if(head == nullptr) {                               //przypadek gdy lista jest pusta
        return -1;
    }
    return head -> value;                               //zwracamy wartość head, bo on zawsze jest max-priority
}

int SortedDLL::extractMax() {
    if(head == nullptr) {                               //przypadek gdy lista jest pusta
        return -1;
    }

    int max = head -> value;

    if(head == tail) {                                  //przypadek gdy jest jeden element
        delete head;                                    //usuwamy go
        head = nullptr;                                 //zerujemy parametry
        tail = nullptr;
        size = 0;
        return max;                                     //zwracamy max value
    }

    DLLNode* oldHead = head;                            //przypadek 'standardowy', tworzymy tymczasową zmienną
    head = head -> next;                                //head zmieniamy na jego next
    head -> prev = nullptr;                             //jego prev dajemy na null bo to nowy head
    delete oldHead;                                     //usuwamy stary 'odpięty' od listy head
    size--;                                             //zmniejszamy rozmiar
    return max;                                         //zwracamy max value
}

bool SortedDLL::modifyKey(int value, int newPriority) {
    if(head == nullptr) {                               //przypadek gdy lista jest pusta
        return false;                                   //zwracamy false (nieudana operacja)
    }

    DLLNode* current = head;

    while(current != nullptr && current -> value != value) {
        current = current -> next;                      //iterujemy po wszystkich node'ach
    }                                                   //iteracja taka sama jak w insert ale po value

    //teraz zależnie od tego jaki jest current, kilka przypadków

    if(current == nullptr) {                            //przypadek gdy nie znaleziono elementu z danym value
        return false;                                   //zwracamy false (nieudana operacja)
    }

    if(current == head) {                               //przypadek gdy current jest headem
        head = head -> next;                            //head zmieniamy na jego next
        if(head != nullptr) {                           //jeśli nowy head nie jest nullptr (końcem (tailem))
            head -> prev = nullptr;                     //ustawiamy jego prev na nullptr
        }
        else {                                          //jeśli next heada to nullptr to lista jest pusta
            tail = nullptr;                             //zmieniamy tail na nullptr;
        }                                               //(head już się równa nullptr)
    }

    else if(current == tail) {                          //przypadek gdy current jest tailem
        tail = tail -> prev;                            //tail zmieniamy na jego prev
        tail -> next = nullptr;                         //next nowego taila (niezależnie czym jest) ustawiamy na nullptr
    }

    else {                                              //przypadek 'standardowy'
        current -> prev -> next = current -> next;      //'wypinamy' current z listy
        current -> next -> prev = current -> prev;      //przepinamy wskaźniki w odpowiedni sposób
    }

    delete current;
    size--;

    insertSDLL(value, newPriority);                     //wstawiamy te value ale z nowym priority

    return true;                                        //operacja udana
}

void SortedDLL::clear() {                               //to samo co destruktor
    DLLNode* current = head;
    
    while(current != nullptr) {                         //iterujemy od początku do końca
        DLLNode* nextNode = current -> next;
        delete current;                                 //usuwając kolejno elementy
        current = nextNode;
    }

    head = nullptr;                                     //zerujemy parametry
    tail = nullptr;
    size = 0;
}

void SortedDLL::print() const {
    DLLNode* current = head;

    cout << "[";

    while (current != nullptr) {
        cout << "(" << current -> value << ", " << current -> priority << ")";
        if (current -> next != nullptr) {
            cout << ", ";
        }
        current = current -> next;
    }

    cout << "]" << endl;
}