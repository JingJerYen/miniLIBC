#include <linux/mman.h>
#include "stdlib.h"
#include "system_calls.h"

typedef struct _my_heap_header
{
    enum
    {
        // magic number due to history
        HEAP_BLOCK_FREE = 0xABABABAB,
        HEAP_BLOCK_USED = 0xCDCDCDCD
    } type;

    size_t size; // include header structure itself
    struct _my_heap_header *prev;
    struct _my_heap_header *next;
} my_heap_header;

#define ADDR_ADD(a, o) ((char *)(a) + o)
#define HEADER_SIZE (sizeof(my_heap_header))

static my_heap_header *list_head = NULL;

void *malloc(size_t size)
{
    if (size == 0)
        return NULL;

    my_heap_header *header = list_head;

    while (header)
    {
        if (header->type == HEAP_BLOCK_USED)
        {
            header = header->next;
            continue;
        }
        if (header->size > size + 2 * HEADER_SIZE)
        {
            // split this large free space
            my_heap_header *new = (my_heap_header *)ADDR_ADD(header, HEADER_SIZE + size);
            new->next = header->next;
            new->prev = header;
            new->type = HEAP_BLOCK_FREE;
            new->size = header->size - (HEADER_SIZE + size);
            if (header->next)
                header->next->prev = new;
            header->next = new;
            header->type = HEAP_BLOCK_USED;
            header->size = HEADER_SIZE + size;
            return ADDR_ADD(header, HEADER_SIZE);
        }
        else if (header->size >= size + HEADER_SIZE)
        {
            // enough space, but not too much, use it but can't split
            header->type = HEAP_BLOCK_USED;
            return ADDR_ADD(header, HEADER_SIZE);
        }
        header = header->next;
    }
    return NULL;
}

void free(void *ptr)
{
    if (!ptr)
        return;

    my_heap_header *header = (my_heap_header *)ADDR_ADD(ptr, -HEADER_SIZE);

    if (header->type == HEAP_BLOCK_FREE)
        return;

    header->type = HEAP_BLOCK_FREE;
    // merge with next free node
    if (header->next && header->next->type == HEAP_BLOCK_FREE)
    {
        header->size += header->next->size;
        header->next = header->next->next;
        if (header->next)
            header->next->prev = header;
        return;
    }
    // merge with last free node
    if (header->prev && header->prev->type == HEAP_BLOCK_FREE)
    {
        header->prev->size += header->size;
        header->prev->next = header->next;
        if (header->next)
            header->next->prev = header->prev;
    }
}

int minicrt_init_heap()
{
    size_t heap_size = 1024 * 1024 * 16; // 16MB
    // list_head = (my_heap_header *)sbrk(heap_size);

    list_head = mmap(0, heap_size, PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (!list_head)
        return -1;

    list_head->type = HEAP_BLOCK_FREE;
    list_head->size = heap_size;
    list_head->next = NULL;
    list_head->prev = NULL;
    return 0;
}

#undef ADDR_ADD
#undef HEADER_SIZE