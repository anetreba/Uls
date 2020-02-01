#include "libmx.h" 

char *mx_strdup(const char *str) {
	char *dst;

	dst = mx_strnew(mx_strlen(str));
	if (dst == NULL)
		return NULL;
	return mx_strcpy(dst, str);
}
