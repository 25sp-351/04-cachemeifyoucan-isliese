#ifndef CACHE_H
#define CACHE_H

typedef struct CacheEntry {
    int rod_length;
    int max_value;
    struct CacheEntry* next;
} CacheEntry;

void cache_init();
int cache_get(int rod_length);
void cache_put(int rod_length, int max_value);

#endif
