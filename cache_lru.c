#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

#define CACHE_SIZE 100 // Cache Size

typedef struct CacheNode {
    int key, value; // Rod length, Optimized Cutting Value
    struct CacheNode* prev, * next;
} CacheNode;

CacheNode* head = NULL, * tail = NULL;
CacheEntry* cache[CACHE_SIZE];

void cache_init() {
    head = tail = NULL;
}

// A function that searches the vaule in the cache
int cache_get(int rod_length) {
    CacheNode* temp = head;
    while (temp) {
        if (temp->key == rod_length) {
            if (temp != head) {
                // Move to front
                temp->prev->next = temp->next;
                if (temp->next) temp->next->prev = temp->prev;
                if (temp == tail) tail = temp->prev;

                temp->next = head;
                temp->prev = NULL;
                head->prev = temp;
                head = temp;
            }
            return temp->value;
        }
        temp = temp->next;
    }
    return -1;
}

// LRU policy
void cache_put(int rod_length, int max_value) {
    CacheNode* newNode = (CacheNode*)malloc(sizeof(CacheNode));
    newNode->key = rod_length;
    newNode->value = max_value;
    newNode->next = head;
    newNode->prev = NULL;
    if (head) head->prev = newNode;
    head = newNode;
    if (!tail) tail = head;
}
