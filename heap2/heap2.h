#pragma once
#include <stdexcept>
#include <iostream>


struct NodePQ {
    int e; // element
    int p; // priorytet
    long long order; // porządek dodania
};

class heapPQ {
private:
    NodePQ* heap; 
    int size; // aktualny rozmiar kolejki
    int capacity; // maksymalny rozmiar kolejki
    static const int INITIAL_CAPACITY = 16; // początkowa pojemność kolejki
    static long long globalOrder; //    licznik porządku dodania

    void heapify_up(int index);
    void heapify_down(int index);

public:
    heapPQ();
    ~heapPQ();
    void insert(int e, int p);
    NodePQ extract_max();
    NodePQ find_max() const;
    void modify_key(int e, int new_p);
    void print_queue() const;
    int return_size() const;
};