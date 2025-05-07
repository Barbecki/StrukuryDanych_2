#include "heap2.h"

long long heapPQ::globalOrder = 0; // Inicjalizacja licznika porządku dodania

// Konstruktor kolejki 
heapPQ::heapPQ()
  : heap(new NodePQ[INITIAL_CAPACITY])
  , size(0)
  , capacity(INITIAL_CAPACITY)
{}
// Destruktor kolejki 
heapPQ::~heapPQ() {
    delete[] heap;
}
// Funkcja pomocnicza do przekształcania węzła drzewa w górę
void heapPQ::heapify_up(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].p > heap[parent].p
            || (heap[index].p == heap[parent].p && heap[index].order < heap[parent].order)) {
            std::swap(heap[index], heap[parent]);
            index = parent;
        } else break;
    }
}
// Funkcja pomocnicza do przekształcania węzła drzewa w dół
void heapPQ::heapify_down(int index) {
    while (true) {
        int left = 2*index + 1, right = 2*index + 2, largest = index;
        if (left < size &&
            (heap[left].p > heap[largest].p
             || (heap[left].p == heap[largest].p && heap[left].order < heap[largest].order)))
            largest = left;
        if (right < size &&
            (heap[right].p > heap[largest].p
             || (heap[right].p == heap[largest].p && heap[right].order < heap[largest].order)))
            largest = right;
        if (largest == index) break;
        std::swap(heap[index], heap[largest]);
        index = largest;
    }
}
// Funkcja dodająca nowy element do kolejki
void heapPQ::insert(int e, int p) {
    // Sprawdzenie, czy kolejka jest pełna i zwiększenie pojemności, jeśli to konieczne ( oraz realokacja pamięci)
    if (size == capacity) {
        int newCap = capacity * 2;
        NodePQ* newHeap = new NodePQ[newCap];
        for (int i = 0; i < size; ++i) newHeap[i] = heap[i];
        delete[] heap;
        heap = newHeap;
        capacity = newCap;
    }
    heap[size] = NodePQ{e, p, globalOrder++};
    heapify_up(size);
    ++size;
}
// Funkcja usuwająca i zwracająca element o najwyższym priorytecie (root)
NodePQ heapPQ::extract_max() {
    if (size == 0) throw std::runtime_error("Queue is empty");
    NodePQ maxN = heap[0];
    heap[0] = heap[size-1];
    --size;
    if (size > 0) heapify_down(0); // Przekształcenie w dół elementu z końca 
    return maxN;
}
// Funkcja zwracająca element o najwyższym priorytecie (root) bez usuwania go z kolejki
NodePQ heapPQ::find_max() const {
    if (size == 0) throw std::runtime_error("Queue is empty");
    return heap[0];
}
// Funkcja modyfikująca priorytet elementu w kolejce
// (jeśli nowy priorytet jest większy, przekształca w górę, jeśli mniejszy – w dół)
void heapPQ::modify_key(int e, int new_p) {
    for (int i = 0; i < size; ++i) {
        if (heap[i].e == e) {
            int old = heap[i].p;
            heap[i].p = new_p;
            if (new_p > old) heapify_up(i);
            else             heapify_down(i);
            return;
        }
    }
    throw std::runtime_error("Element not found");
}
// Funkcja wypisująca kolejkę
void heapPQ::print_queue() const {
    for (int i = 0; i < size; ++i)
        std::cout << "(" << heap[i].e << "," << heap[i].p << ") ";
    std::cout << "\n";
}
// Funkcja zwracająca rozmiar kolejki
int heapPQ::return_size() const {
    return size;
}