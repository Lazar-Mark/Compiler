#include "vector.h"

Vector* vector_create(void){
    Vector* new_vector = (Vector*)malloc(sizeof(Vector));
    new_vector->size = 0;
    new_vector->max = 8;
    new_vector->data = (void**)malloc(sizeof(void*)*8);

    return new_vector;
}

void vector_add(Vector* v, void* element){

    if(v->size == v->max){
        v->data= realloc(v->data,sizeof(void*) * v->max*2);
        v->max*=2;
    }

    v->data[v->size]= element;
    v->size++;
}

void vector_free(Vector* v){
    free(v->data);
    free(v);
}
