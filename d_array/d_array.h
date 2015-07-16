#ifndef D_ARRAY_H
#define D_ARRAY_H

#define INIT_CAPACITY 50

typedef struct DArray DArray;

struct DArray {
	void *array;
	size_t capacity;
	size_t size;
	size_t elem_size;
};

DArray *new_d_array(size_t elem_size);
void destroy_d_array(DArray *arr);
bool expand(DArray *arr);
bool shrink(DArray *arr);
bool insert(void *elem, DArray *arr, size_t index);
bool remove(DArray *arr, size_t index);
bool push(void *elem, DArray *arr);
bool pop(DArray *arr);
#endif