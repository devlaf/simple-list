#include <stdbool.h>

typedef struct element_t {
    void* data;
    struct element_t* next;
} element_t;

typedef struct list {
    element_t* head;
    element_t* tail;
} list;

list* list_init();

// Caller responsible for freeing individual data fields.
void list_free(list* collection);

void list_append(list* collection, void *data);

void list_foreach(list* collection, void (*fptr)(void*));

bool list_contains(list* collection, bool (*fptr)(void*, void*), void* args);

list* list_map_mutable(list* collection, void* (*fptr)(void*, void*), void* args);

list* list_map_immutable(list* collection, void* (*copy_fptr)(void*), void* (*map_fptr)(void*, void*), void* args);

list* list_filter_mutable(list* collection, void (*free_fptr)(void*), bool (*filter_fptr)(void*, void*), void* args);

list* list_filter_immutable(list* collection, void* (*copy_fptr)(void*), bool (*filter_fptr)(void*, void*), void* args);

void* list_reduce(list* collection, void (*fptr)(void*, void*), void* result);
