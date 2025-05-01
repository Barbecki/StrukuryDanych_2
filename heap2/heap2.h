#pragma once
#include <stdexcept>
#include <iostream>

// zmieniona nazwa, już nie koliduje z heap::Node
struct NodeOPQ {
    int e;
    int p;
    long long order;
};

class heapOPQ {
private:
    NodeOPQ* heap;
    int size;
    int capacity;
    static const int INITIAL_CAPACITY = 16;
    static long long globalOrder;

    void heapify_up(int index);
    void heapify_down(int index);

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