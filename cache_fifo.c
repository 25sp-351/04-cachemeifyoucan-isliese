#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

#define CACHE_SIZE 10  // Cache Size

typedef struct CacheNode {
    int key;               // Rod length
    int value;             // Optimized Cutting Value
    struct CacheNode* next;
} CacheNode;

CacheNode* head = NULL;  
CacheNode* tail = NULL;  
int cache_count = 0;


void cache_init() {
    head = tail = NULL;
    cache_count = 0;
}

// A function that searches the vaule in the cache
int cache_get(int rod_length) {
    CacheNode* current = head;
    while (current) {
        if (current->key == rod_length) {
            return current->value;  // If there's a value in the cache, return it 
        }
        current = current->next;
    }
    return -1;  // If there's no value in the cache, return -1 
}

// A function that adds a new vaule to the cache (FIFO policy)
void cache_put(int rod_length, int max_value) {
    CacheNode* new_node = (CacheNode*)malloc(sizeof(CacheNode));
    new_node->key = rod_length;
    new_node->value = max_value;
    new_node->next = NULL;

    if (cache_count >= CACHE_SIZE) {
        // Removes the oldest node
        CacheNode* temp = head;
        head = head->next;
        free(temp);
        cache_count--;
    }

    // Adds a new node at the end of queue
    if (!tail) {
        head = tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
    
    cache_count++;
}
