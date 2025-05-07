#include "linkedList.h"
#include <iostream>


// Konstruktor węzła – inicjalizacja wartości, priorytetu i wskaźników
Node::Node(int v, int p) : value(v), priority(p), next(nullptr), prev(nullptr) {}

// Konstruktor kolejki – początkowo lista jest pusta
linkedListPQ::linkedListPQ() : head(nullptr), size(0) {}

// Destruktor kolejki – usuwa wszystkie węzły i zwalnia pamięć
linkedListPQ::~linkedListPQ() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}
// Funkcja wstawiająca nowy element do kolejki z priorytetem
void linkedListPQ::insert(int value, int priority) {
    Node* new_node = new Node(value, priority);
    
    // Jeśli lista jest pusta lub nowy priorytet jest większy niż w head – wstawiamy na początek
    if (head == nullptr || priority > head->priority) {
        new_node->next = head;
        if (head != nullptr) {
            head->prev = new_node;
        }
        head = new_node;
    }
    else {
        // Szukamy miejsca, gdzie nowy priorytet pasuje
        Node* current = head;
        while (current->next != nullptr && current->next->priority >= priority) {
            current = current->next;
        }

        new_node->next = current->next;
        new_node->prev = current;
        if (current->next != nullptr) {
            current->next->prev = new_node;
        }
        current->next = new_node;
    }
    size++;
}

// Funkcja usuwająca i zwracająca element o najwyższym priorytecie (head)
Node linkedListPQ::extract_max() {
    if (head == nullptr) {
        throw std::runtime_error("Queue is empty!");
    }
    Node* temp = head;
    Node result = *temp;  

    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    }
    delete temp;
    size--;
    return result;
}

// Funkcja zwracająca element o najwyższym priorytecie bez usuwania
Node linkedListPQ::find_max() const {
    if (head == nullptr) {
        throw std::runtime_error("Queue is empty!");
    }
    return *head; 
}

// Funkcja zmieniająca priorytet danego elementu
void linkedListPQ::modify_key(int value, int new_priority) {
    Node* current = head;
    while (current != nullptr && current->value != value) {
        current = current->next;
    }

    if (current == nullptr) {
        throw std::runtime_error("Element not found");
    }
    
    // Odłączamy znaleziony element z listy
    if (current->prev != nullptr) {
        current->prev->next = current->next;
    }
    else {
        head = current->next;
    }
    if (current->next != nullptr) {
        current->next->prev = current->prev;
    }

    delete current;
    size--;
    // Wstawiamy ten sam element z nowym priorytetem
    insert(value, new_priority);
}
// Funkcja zwracająca aktualny rozmiar kolejki
int linkedListPQ::return_size() const {
    return size;
}

// Funkcja wyświetlająca całą kolejkę (elementy z priorytetami)
void linkedListPQ::print_queue() const {
    Node* current = head;
    std::cout << "Queue: ";
    while (current != nullptr) {
        std::cout << "(" << current->value << ", " << current->priority << ") ";
        current = current->next;
    }
    std::cout << "\n";
}
