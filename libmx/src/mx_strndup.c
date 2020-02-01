#include "libmx.h"

char *mx_strndup(const char *s1, size_t n) {
	char *dst;
	size_t len = mx_strlen(s1);

	if (len > n)
		len = n;
	dst = mx_strnew((int)len);
	dst = mx_memcpy(dst, s1, len);
	return dst;
}
