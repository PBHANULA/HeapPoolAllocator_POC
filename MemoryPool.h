
#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <cstddef>
#include <cstdint>

class MemoryPool {
public:
    void init(std::size_t size);
    void* allocate(std::size_t size);
    void deallocate(void* ptr);
    void cleanup();

private:
    struct BlockHeader {
        std::size_t size;
        bool is_free;
        BlockHeader* next;
        uint32_t magic;
    };

    static constexpr std::size_t ALIGNMENT = alignof(std::max_align_t);
    static constexpr std::size_t MIN_ALLOC_SIZE = 16;
    static constexpr uint32_t MAGIC_NUMBER = 0xDEADBEEF;

    unsigned char* heap = nullptr;
    std::size_t heap_size = 0;
    BlockHeader* head = nullptr;

    std::size_t align_up(std::size_t size);
    void coalesce();
};

#endif // MEMORY_POOL_H
