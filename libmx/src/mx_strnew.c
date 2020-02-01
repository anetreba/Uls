#include "libmx.h" 

char *mx_strnew(const int size) {
	char *new;

	if (size < 0)
		return NULL;
	new = (char *)malloc(sizeof(char) * (size + 1));
	if (new == NULL)
		return NULL;
	for (int i = 0; i <= size; i++) {
		new[i] = '\0';
	}
	return new;
}
