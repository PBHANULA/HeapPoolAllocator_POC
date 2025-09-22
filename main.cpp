#include "MemoryPool.h"
#include <iostream>

int main() {
    MemoryPool pool;

    // Initialize a 1KB memory pool
    pool.init(1024);

    // Allocate two blocks
    void* a = pool.allocate(100);
    void* b = pool.allocate(200);

    if (a && b) {
        std::cout << "Allocated block A at: " << a << "\n";
        std::cout << "Allocated block B at: " << b << "\n";
    } else {
        std::cerr << "Allocation failed for A or B.\n";
    }

    // Deallocate both blocks
    pool.deallocate(a);
    pool.deallocate(b);

    // Allocate a larger block after deallocation
    void* c = pool.allocate(250);
    if (c) {
        std::cout << "Allocated block C at: " << c << "\n";
    } else {
        std::cerr << "Allocation failed for C.\n";
    }

    // Clean up the memory pool
    pool.cleanup();

    return 0;
}
