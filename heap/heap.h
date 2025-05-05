#pragma once
#include <stdexcept>
#include <iostream>
#include <unordered_map>

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
    std::unordered_map<int,int> indexMap;

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