#include "libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
	char *s = (char *)str;

	if (!str || !sub)
		return -2;
	if (mx_strlen(str) >= mx_strlen(sub)) {
	   	while (*str) {
	     	if (mx_memcmp(str, sub, mx_strlen(sub)) == 0) {
	       		return str - s;
	     	}
	     	str++;
	   	}
 	}
 	return -1;
}
