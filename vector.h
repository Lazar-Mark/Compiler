#ifndef vector_h
#define vector_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Vector{
    int size;
    int max;
    void** data;
}Vector;
Vector* vector_create(void);
void vector_add(Vector* v, void* element);
void vector_free(Vector* v);
#endif