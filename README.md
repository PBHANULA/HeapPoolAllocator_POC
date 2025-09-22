# Heap Pool Allocator

C++ project that implements a custom heap pool allocator. This allocator manages a fixed-size memory pool, allowing efficient allocation and deallocation of memory blocks without relying on the system's `malloc`/`free` for each request.

🚀 Purpose

- Demonstrate custom memory management using a memory pool.
- Provide predictable, fast allocation and deallocation.
- Reduce fragmentation and overhead compared to general-purpose allocators.
- Useful for embedded systems, games, real-time applications, and high-performance servers.

✨ Features

- **Fixed-size memory pool**: Allocated once at initialization.
- **Custom allocation/deallocation**: `allocate(size)` and `deallocate(ptr)` methods.
- **Free list management**: Uses a linked list to track free blocks.
- **Block splitting and coalescing**: Minimizes fragmentation.
- **Safe cleanup**: Frees the entire pool with `cleanup()`.

## 📁 Project Structure

- `MemoryPool.h`: Header file defining the MemoryPool class.
- `MemoryPool.cpp`: Implementation of the MemoryPool methods.
- `main.cpp`: Example usage of the memory pool allocator.
- `test_memory_pool.cpp`: Test suite to validate allocator behavior.

## 🛠️ Build Instructions

To compile the project:

g++ main.cpp MemoryPool.cpp -o heap_allocator
./heap_allocator
