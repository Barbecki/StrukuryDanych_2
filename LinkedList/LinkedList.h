#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//podstawowy element listy wiązanej dwukierunkowej, ma wskaźniki na poprzedni oraz następny element
struct Node {
    int value;
    int priority;
    Node* next;
    Node* prev;

    Node(int v, int p);
};


class linkedListPQ{
private:
    Node* head;
    int size;

public:
    linkedListPQ();
    ~linkedListPQ();

    void print_queue() const;
    int return_size() const;
    void insert(int value, int priority);
    Node find_max() const;
    Node extract_max();
    void modify_key(int value, int new_priority);

};

#endif
