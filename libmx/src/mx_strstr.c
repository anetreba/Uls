#include "libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
	return mx_memmem(haystack, mx_strlen(haystack), needle, mx_strlen(needle));
}
