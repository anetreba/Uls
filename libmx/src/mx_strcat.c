#include "libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2) {
	int j = 0;
	int size = mx_strlen(s1);
	int i;

	for (i = size; i < size + mx_strlen(s2); i++) {
		s1[i] = s2[j];
		j++;
	}
	s1[i] = '\0';
	return s1;
}
