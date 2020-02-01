#include "libmx.h"

void *mx_realloc(void *ptr, size_t size) {
	size_t len;
	void *new_ptr = NULL;

	if (size <= 0 && ptr) {
		free(ptr);
		return NULL;
	}
	if (!ptr && size)
		return malloc(size);
	len = malloc_size(ptr);
	if (len > size)
		new_ptr = (void *)malloc(len);
	else
		new_ptr = (void *)malloc(size);
	if (!new_ptr)
		return NULL;
	new_ptr = mx_memcpy(new_ptr, ptr, len);
	free(ptr);
	return new_ptr;
}
