#include "MemoryPool.h"
#include <iostream>
#include <cassert>

void test_basic_allocation() {
    MemoryPool pool;
    pool.init(512);
    void* a = pool.allocate(100);
    void* b = pool.allocate(50);
    assert(a != nullptr);
    assert(b != nullptr);
    pool.deallocate(a);
    pool.deallocate(b);
    pool.cleanup();
    std::cout << "test_basic_allocation passed\n";
}

void test_reuse_after_deallocation() {
    MemoryPool pool;
    pool.init(256);
    void* a = pool.allocate(100);
    pool.deallocate(a);
    void* b = pool.allocate(100);
    assert(b != nullptr);
    pool.cleanup();
    std::cout << "test_reuse_after_deallocation passed\n";
}

void test_zero_size_allocation() {
    MemoryPool pool;
    pool.init(128);
    void* a = pool.allocate(0);
    assert(a == nullptr);
    pool.cleanup();
    std::cout << "test_zero_size_allocation passed\n";
}

void test_out_of_memory() {
    MemoryPool pool;
    pool.init(128);
    void* a = pool.allocate(200); // Too large
    assert(a == nullptr);
    pool.cleanup();
    std::cout << "test_out_of_memory passed\n";
}

void test_double_free_protection() {
    MemoryPool pool;
    pool.init(256);
    void* a = pool.allocate(100);
    pool.deallocate(a);
    pool.deallocate(a); // Should be safely ignored or reported
    pool.cleanup();
    std::cout << "test_double_free_protection passed\n";
}

int main() {
    test_basic_allocation();
    test_reuse_after_deallocation();
    test_zero_size_allocation();
    test_out_of_memory();
    test_double_free_protection();
    std::cout << "All tests passed successfully.\n";
    return 0;
}
