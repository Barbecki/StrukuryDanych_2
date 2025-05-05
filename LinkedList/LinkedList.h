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

    void display() const;
    int returnSize() const;
    void insert(int value, int priority);
    Node findMax() const;
    Node extractMax();
    void modifyKey(int value, int new_priority);

};

#endif
