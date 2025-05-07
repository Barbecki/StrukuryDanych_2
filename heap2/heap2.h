#pragma once
#include <stdexcept>
#include <iostream>


struct NodePQ {
    int e;
    int p;
    long long order;
};

class heapPQ {
private:
    NodePQ* heap;
    int size;
    int capacity;
    static const int INITIAL_CAPACITY = 16;
    static long long globalOrder;

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