#include <iostream>
#include "heap.h"

int main() {
    heapPQ pq;

    pq.insert(10, 1);
    pq.insert(20, 5);
    pq.insert(5, 3);
    std::cout << "Queue after inserts:\n";
    pq.print_queue();
    std::cout << "Current max: " << pq.find_max().e << " (priority " << pq.find_max().p << ")\n";

    pq.modify_key(10, 5);
    std::cout << "After modifying key of 10 to priority 9, new max: "
              << pq.find_max().e << " (priority " << pq.find_max().p << ")\n";

    auto extracted = pq.extract_max();
    std::cout << "Extracted max: " << extracted.e << " (priority " << extracted.p << ")\n";

    std::cout << "Size after extraction: " << pq.return_size() << "\n";
    pq.print_queue();
    return 0;
}