#include <iostream>
#include "heap/heap.h"
#include "heap2/heap2.h"
#include "LinkedList/LinkedList.h"

int main() {
    // Testowanie heapOPQ
    std::cout << "Testing heapOPQ:\n";
    heapOPQ pq;

    pq.insert(10, 1);
    pq.insert(20, 5);
    pq.insert(5, 3);
    std::cout << "Queue after inserts:\n";
    pq.print_queue();
    std::cout << "Current max: " << pq.find_max().e << " (priority " << pq.find_max().p << ")\n";

    pq.modify_key(10, 9);
    std::cout << "After modifying key of 10 to priority 9, new max: "
              << pq.find_max().e << " (priority " << pq.find_max().p << ")\n";

    auto extracted = pq.extract_max();
    std::cout << "Extracted max: " << extracted.e << " (priority " << extracted.p << ")\n";

    std::cout << "Size after extraction: " << pq.return_size() << "\n";
    pq.print_queue();

    // Testowanie linkedListPQ
    std::cout << "\nTesting linkedListPQ:\n";
    linkedListPQ ll;

    ll.insert(10, 1);
    ll.insert(20, 5);
    ll.insert(5, 3);
    std::cout << "Queue after inserts:\n";
    ll.print_queue();
    std::cout << "Current max: " << ll.find_max().value << " (priority " << ll.find_max().priority << ")\n";

    ll.modify_key(10, 9);
    std::cout << "After modifying key of 10 to priority 9, new max: "
              << ll.find_max().value << " (priority " << ll.find_max().priority << ")\n";

    auto extracted_ll = ll.extract_max();
    std::cout << "Extracted max: " << extracted_ll.value << " (priority " << extracted_ll.priority << ")\n";

    std::cout << "Size after extraction: " << ll.return_size() << "\n";
    ll.print_queue();

    return 0;
}