#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//podstawowy element listy wiązanej dwukierunkowej, ma wskaźniki na poprzedni oraz następny element
struct Node {
    int value; //wartość
    int priority; //priorytet
    Node* next; //wskaźnik na następny element
    Node* prev; //wskaźnik na poprzedni element

    Node(int v, int p); //konstruktor, który ustawia wartość oraz priorytet
};


class linkedListPQ{
private:
    Node* head; // wskaźnik na pierwszy element listy
    int size; // rozmiar listy

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
