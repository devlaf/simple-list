#include<stdlib.h>
#include "list.h"

list* list_init() 
{
     return (struct list*)calloc(1, sizeof(struct list));
}

void list_append(list* collection, void *data)
{
     if (NULL == collection)
          return;

     struct element_t* to_append = (struct element_t*)malloc(sizeof(struct element_t));
     to_append->data = data;
     to_append->next = NULL;

     if (NULL == collection->tail) {
          collection->tail = to_append;
          collection->head = to_append;
     } else {
          collection->tail->next = to_append;
          collection->tail = to_append;
     }
}

void list_free(list* collection) {
     element_t* current = collection->head;
     while (current != NULL) {
          element_t* to_free = current;
          current = current->next;
          free(to_free);
          to_free = NULL;
     }

     free(collection);
     collection = NULL;
}

void list_foreach(list* collection, void (*fptr)(void*))
{
     if(NULL == collection)
          return;

     element_t* node = collection->head;
     while (node != NULL) {
          (*fptr)(node->data);
          node = node->next;
     }
}

bool list_contains(list* collection, bool (*fptr)(void*, void*), void* args)
{
     if(NULL == collection)
          return false;

     element_t* node = collection->head;
     while (node != NULL) {
          if ((*fptr)(node->data, args))
               return true;
          node = node->next;
     }

     return false;
}

list* list_map_mutable(list* collection, void* (*fptr)(void*, void*), void* args)
{
     if(NULL == collection)
          return collection;

     element_t* node = collection->head;
     while (node != NULL) {
          node->data = ((*fptr)(node->data, args));
          node = node->next;
     }

     return collection;
}

list* list_map_immutable(list* collection, void* (*copy_fptr)(void*), void* (*map_fptr)(void*, void*), void* args)
{
     if(NULL == collection)
          return NULL;

     list* copy = list_init();
     element_t* node = collection->head;
     while (node != NULL) {
          void* element_data_copy = ((*copy_fptr)(node->data));
          void* modified = ((*map_fptr)(element_data_copy, args));
          list_append(copy, modified);
          node = node->next;
     }

     return copy;
}

list* list_filter_mutable(list* collection, void (*free_fptr)(void*), bool (*filter_fptr)(void*, void*), void* args)
{
     if(NULL == collection)
          return collection;

     element_t* node = collection->head;
     while (node != NULL && !((*filter_fptr)(node->data, args))) {
          collection->head = node->next;
          ((*free_fptr)(node->data));
          free(node);
          node = collection->head;
     }

     if (NULL == node)
          return NULL;

     while (node->next != NULL) {
          if ((*filter_fptr)(node->next->data, args)) {
               node = node->next;
          } else {
               element_t* temp = node->next;
               ((*free_fptr)(node->next->data));
               node->next = node->next->next;
               free(temp);
          }
     }
     collection->tail = node;

     return collection;
}

list* list_filter_immutable(list* collection, void* (*copy_fptr)(void*), bool (*filter_fptr)(void*, void*), void* args)
{
     if(NULL == collection)
          return NULL;

     list* copy = list_init();

     element_t* node = collection->head;
     while (node != NULL) {
          if((*filter_fptr)(node->data, args))
               list_append(copy, ((*copy_fptr)(node->data)));
          node = node->next;
     }
     return copy;
}

void* list_reduce(list* collection, void (*fptr)(void*, void*), void* result)
{
     if(NULL == collection)
          return;

     element_t* node = collection->head;
     while (node != NULL) {
          (*fptr)(node->data, result);
          node = node->next;
     }
    
     return result;
}

