#pragma once
#include <vector>
#include <stdexcept>
#include <iostream>

struct Node {
    int e;  // element
    int p;  // priorytet
    long long order;
};

class PriorityQueue {
private:
    std::vector<Node> heap;
    static long long globalOrder; 
    void heapify_up(int index);
    void heapify_down(int index);

public:
    PriorityQueue() = default;
    void insert(int e, int p);
    Node extract_max();
    Node find_max() const;
    void modify_key(int e, int new_p);
    void print_queue() const;
    int return_size() const;
};