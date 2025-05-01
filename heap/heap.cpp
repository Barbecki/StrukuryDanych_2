#include "heap.h"


long long PriorityQueue::globalOrder = 0;

void PriorityQueue::heapify_up(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].p > heap[parent].p
            || (heap[index].p == heap[parent].p && heap[index].order < heap[parent].order)) {

            Node temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;

            index = parent;
        } else {
            break;
        }
    }
}

void PriorityQueue::heapify_down(int index) {
    int size = static_cast<int>(heap.size());
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if ((left < size) &&
            ((heap[left].p > heap[largest].p)
             || (heap[left].p == heap[largest].p && heap[left].order < heap[largest].order))) {
            largest = left;
        }
        if ((right < size) &&
            ((heap[right].p > heap[largest].p)
             || (heap[right].p == heap[largest].p && heap[right].order < heap[largest].order))) {
            largest = right;
        }
        if (largest != index) {
        
            Node temp = heap[index];
            heap[index] = heap[largest];
            heap[largest] = temp;

            index = largest;
        } else {
            break;
        }
    }
}

void PriorityQueue::insert(int e, int p) {
    Node node{e, p, globalOrder++}; 
    heap.push_back(node);
    heapify_up(static_cast<int>(heap.size()) - 1);
}

Node PriorityQueue::extract_max() {
    if (heap.empty()) {
        throw std::runtime_error("Queue is empty");
    }
    Node maxNode = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty()) {
        heapify_down(0);
    }
    return maxNode;
}

Node PriorityQueue::find_max() const {
    if (heap.empty()) {
        throw std::runtime_error("Queue is empty");
    }
    return heap[0];
}

void PriorityQueue::modify_key(int e, int new_p) {

    for (int i = 0; i < static_cast<int>(heap.size()); i++) {
        if (heap[i].e == e) {
            int old_p = heap[i].p;
            heap[i].p = new_p;
            if (new_p > old_p) {
                heapify_up(i);
            } else {
                heapify_down(i);
            }
            return;
        }
    }
    throw std::runtime_error("Element not found");
}

void PriorityQueue::print_queue() const {
    for (const auto& node : heap) {
        std::cout << "(" << node.e << ", " << node.p << ") ";
    }
    std::cout << std::endl;
}

int PriorityQueue::return_size() const {
    return static_cast<int>(heap.size());
}