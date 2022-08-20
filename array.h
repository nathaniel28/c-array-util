//#define SAFE

typedef struct {
	char *content;
	size_t unit_size;
	size_t len, cap;
} Array;

extern Array* array_new(size_t unit_size);

extern void array_free(Array *arr);

extern void* array_get(Array *arr, size_t index);
#define ARRAY_GET(arr, index, type) (type) array_get(arr, (size_t) index)

extern void array_set(Array *arr, void *value, size_t index);

extern int array_expand(Array *arr);

extern int array_contract(Array *arr);

extern int array_append(Array *arr, void *value);
