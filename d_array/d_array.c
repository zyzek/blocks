#include <stdlib.h>
#include "d_array.h"

DArray *new_d_array(size_t elem_size) {
	DArray *new_arr = (DArray *)malloc(sizeof(DArray));

	if (!new_arr) {
		return NULL;
	}

	new_arr->array = calloc(INIT_CAPACITY, elem_size);
	
	if (!new_arr->array) {
		free(new_arr);
		return NULL;
	}
	
	new_arr->capacity = INIT_CAPACITY;
	new_arr->size = 0;
	new_arr->elem_size = elem_size;

	return new_arr;
}

void destroy_d_array(DArray *arr) {
	free(arr->array);
	free(arr);
}

bool expand(DArray *arr) {

}

bool shrink(DArray *arr) {

}

bool insert(void *elem, DArray *arr, size_t index) {
	// shuffle everything after insert point forward.
	// Insert new item
	// resize if necessary.
}

bool remove(DArray *arr, size_t index);
bool push(void *elem, DArray *arr);
bool pop(DArray *arr);