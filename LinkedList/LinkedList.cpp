#include "linkedList.h"
#include <iostream>

Node::Node(int v, int p) : value(v), priority(p), next(nullptr), prev(nullptr) {}

linkedListPQ::linkedListPQ() : head(nullptr), size(0) {}

linkedListPQ::~linkedListPQ() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

void linkedListPQ::insert(int value, int priority) {
    Node* new_node = new Node(value, priority);
    if (head == nullptr || priority > head->priority) {
        new_node->next = head;
        if (head != nullptr) {
            head->prev = new_node;
        }
        head = new_node;
    }
    else {
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

Node linkedListPQ::extractMax() {
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

Node linkedListPQ::findMax() const {
    if (head == nullptr) {
        throw std::runtime_error("Queue is empty!");
    }
    return *head; 
}


void linkedListPQ::modifyKey(int value, int new_priority) {
    Node* current = head;
    while (current != nullptr && current->value != value) {
        current = current->next;
    }

    if (current == nullptr) {
        throw std::runtime_error("Element not found");
    }

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
    insert(value, new_priority);
}

int linkedListPQ::returnSize() const {
    return size;
}

void linkedListPQ::display() const {
    Node* current = head;
    std::cout << "Queue: ";
    while (current != nullptr) {
        std::cout << "(" << current->value << ", " << current->priority << ") ";
        current = current->next;
    }
    std::cout << "\n";
}
