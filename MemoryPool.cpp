
#include "MemoryPool.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

std::size_t MemoryPool::align_up(std::size_t size) {
    return (size + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);
}

void MemoryPool::init(std::size_t size) {
    heap = static_cast<unsigned char*>(std::malloc(size));
    if (!heap) {
        std::cerr << "Heap initialization failed!" << std::endl;
        return;
    }
    heap_size = size;
    head = reinterpret_cast<BlockHeader*>(heap);
    head->size = size - sizeof(BlockHeader);
    head->is_free = true;
    head->next = nullptr;
    head->magic = MAGIC_NUMBER;
}

void* MemoryPool::allocate(std::size_t size) {
    if (size == 0 || size > heap_size - sizeof(BlockHeader)) return nullptr;
    std::size_t aligned_size = align_up(size);
    BlockHeader* current = head;

    while (current) {
        if (current->is_free && current->size >= aligned_size) {
            std::size_t remaining = current->size - aligned_size;
            if (remaining >= sizeof(BlockHeader) + MIN_ALLOC_SIZE) {
                BlockHeader* new_block = reinterpret_cast<BlockHeader*>(
                    reinterpret_cast<unsigned char*>(current) + sizeof(BlockHeader) + aligned_size);
                new_block->size = remaining - sizeof(BlockHeader);
                new_block->is_free = true;
                new_block->next = current->next;
                new_block->magic = MAGIC_NUMBER;
                current->size = aligned_size;
                current->next = new_block;
            }
            current->is_free = false;
            return reinterpret_cast<unsigned char*>(current) + sizeof(BlockHeader);
        }
        current = current->next;
    }
    std::cerr << "Out of memory!" << std::endl;
    return nullptr;
}

void MemoryPool::deallocate(void* ptr) {
    if (!ptr) return;
    BlockHeader* block = reinterpret_cast<BlockHeader*>(
        reinterpret_cast<unsigned char*>(ptr) - sizeof(BlockHeader));
    if (block->magic != MAGIC_NUMBER || block->is_free) {
        std::cerr << "Invalid or double free detected!" << std::endl;
        return;
    }
    block->is_free = true;
    coalesce();
}

void MemoryPool::coalesce() {
    BlockHeader* current = head;
    while (current && current->next) {
        if (current->is_free && current->next->is_free) {
            current->size += sizeof(BlockHeader) + current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}

void MemoryPool::cleanup() {
    std::free(heap);
    heap = nullptr;
    head = nullptr;
    heap_size = 0;
}
