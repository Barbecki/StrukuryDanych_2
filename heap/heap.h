#pragma once
#include <stdexcept>
#include <iostream>
#include <unordered_map>

struct NodeOPQ {
    int e; // element
    int p; // priorytet
    long long order; // porządek dodania
};

class heapOPQ {
private:
    NodeOPQ* heap;
    int size; // aktualny rozmiar kolejki
    int capacity; // maksymalny rozmiar kolejki
    static const int INITIAL_CAPACITY = 16; // początkowa pojemność kolejki
    static long long globalOrder; // licznik porządku dodania
    std::unordered_map<int,int> indexMap; // mapa do szybkiego dostępu do indeksu węzła w kopcu

    void heapify_up(int index);
    void heapify_down(int index);
    void swapNodes(int i, int j); 
public:
    heapOPQ();
    ~heapOPQ();
    void insert(int e, int p);
    NodeOPQ extract_max();
    NodeOPQ find_max() const;
    void modify_key(int e, int new_p);
    void print_queue() const;
    int return_size() const;
};