#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

Array* array_new(size_t unit_size) {
	Array *arr = malloc(sizeof(Array));
	if (!arr) return NULL;
	arr->content = malloc(unit_size);
	if (!arr->content) {
		free(arr);
		return NULL;
	}
	arr->unit_size = unit_size;
	arr->len = 0;
	arr->cap = 1;
	return arr;
}

void array_free(Array *arr) {
	free(arr->content);
	free(arr);
}

void* array_get(Array *arr, size_t index) {
#ifdef SAFE
	if (index >= arr->len) {
		fprintf(stderr, "index %ld out-of-bounds for %ld-element array\n", index, arr->len);
		exit(1);
	}
#endif
	return arr->content + index*arr->unit_size;
}

void array_set(Array *arr, void *value, size_t index) {
	memcpy(array_get(arr, index), value, arr->unit_size);
}

int array_expand(Array *arr) {
	arr->cap *= 2;
	void *realloced = realloc(arr->content, arr->cap*arr->unit_size);
	if (!realloced) {
		// failed to get more memory, so undo what was changed
		arr->cap /= 2;
		// perhaps instead of failing right away this could try to alloc less than
		// double the array's old size, perhaps try 1/4 then 1/8 and so on.
		return -1;
	}
	arr->content = realloced;
	return 0;
}

int array_contract(Array *arr) {
	void *realloced = realloc(arr->content, arr->len*arr->unit_size);
	if (!realloced) {
		return -1;
	}
	arr->content = realloced;
	arr->cap = arr->len;
	return 0;
}

int array_append(Array *arr, void *value) {
	arr->len++;
	if (arr->len > arr->cap && array_expand(arr)) {
		arr->len--;
        	return -1;
	}
	array_set(arr, value, arr->len-1);
	return 0;
}
