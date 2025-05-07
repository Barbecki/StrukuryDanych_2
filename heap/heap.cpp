#include "heap.h"

long long heapOPQ::globalOrder = 0; // Inicjalizacja licznika porządku dodania

// Konstruktor kolejki
heapOPQ::heapOPQ()
  : heap(new NodeOPQ[INITIAL_CAPACITY])
  , size(0)
  , capacity(INITIAL_CAPACITY)
{}

// Destruktor kolejki
heapOPQ::~heapOPQ() {
    delete[] heap;
}
// Funkcja pomocnicza do zamiany węzłów w kopcu i modyfikacja mapy indeksów
void heapOPQ::swapNodes(int i, int j) {
    std::swap(heap[i], heap[j]);
    indexMap[heap[i].e] = i;
    indexMap[heap[j].e] = j;
}

// Funkcja pomocnicza do przekształcania węzła drzewa w górę
// (przesuwanie węzła w górę w kopcu)
void heapOPQ::heapify_up(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].p > heap[parent].p
            || (heap[index].p == heap[parent].p && heap[index].order < heap[parent].order)) {
            swapNodes(index, parent);
            index = parent;
        } else break;
    }
}

// Funkcja pomocnicza do przekształcania węzła drzewa w dół
// (przesuwanie węzła w dół w kopcu)
void heapOPQ::heapify_down(int index) {
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
        swapNodes(index, largest);
        index = largest;
    }
}

// funkcja dodająca nowy element do kolejki
// (jeśli kolejka jest pełna, zwiększa pojemność i realokuje pamięć)
void heapOPQ::insert(int e, int p) {
    if (size == capacity) {
        int newCap = capacity * 2;
        NodeOPQ* newHeap = new NodeOPQ[newCap];
        for (int i = 0; i < size; ++i) newHeap[i] = heap[i];
        delete[] heap;
        heap = newHeap;
        capacity = newCap;
    }
    heap[size] = NodeOPQ{e, p, globalOrder++};
    indexMap[e] = size;
    heapify_up(size);
    ++size;
}
// Funkcja usuwająca i zwracająca element o najwyższym priorytecie (root)
NodeOPQ heapOPQ::extract_max() {
    if (size == 0) throw std::runtime_error("Queue is empty");
    NodeOPQ maxN = heap[0];
    indexMap.erase(maxN.e);
    --size;
    // Przesunięcie ostatniego elementu na miejsce root
    // i przekształcenie kopca w dół
    if (size > 0) {
        heap[0] = heap[size];
        indexMap[heap[0].e] = 0;
        heapify_down(0);
    }
    return maxN;
}
// Funkcja zwracająca element o najwyższym priorytecie (root) bez usuwania go z kolejki
NodeOPQ heapOPQ::find_max() const {
    if (size == 0) throw std::runtime_error("Queue is empty");
    return heap[0];
}
// funkcja modyfikująca klucz elementu w kolejce
void heapOPQ::modify_key(int e, int new_p) {
    auto it = indexMap.find(e);
    if (it == indexMap.end()) throw std::runtime_error("Element not found");
    int idx = it->second;
    int old = heap[idx].p;
    heap[idx].p = new_p;
    if (new_p > old) heapify_up(idx);
    else             heapify_down(idx);
}
// Funkcja wypisująca kolejkę
void heapOPQ::print_queue() const {
    for (int i = 0; i < size; ++i)
        std::cout << "(" << heap[i].e << "," << heap[i].p << ") ";
    std::cout << "\n";
}
// Funkcja zwracająca aktualny rozmiar kolejki
int heapOPQ::return_size() const {
    return size;
}