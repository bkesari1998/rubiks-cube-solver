#ifndef VECTORS_H
#define VECTORS_H

typedef void* VECTOR;

VECTOR vector_init(void);
void vector_destroy(VECTOR* phVector);
void vector_append_item(VECTOR hVector, char item);
void vector_replace_item(VECTOR hVector, unsigned int index, char item);
void vector_insert_item(VECTOR hVector, unsigned int index, char item);
char vector_pop_item(VECTOR hVector, unsigned int index);
int vector_get_size(VECTOR hVector);
int vector_get_capacity(VECTOR hVector);
void vector_remove_item(VECTOR hVector, unsigned int index);
void vector_print_data(VECTOR hVector, FILE* fp);

#endif 
