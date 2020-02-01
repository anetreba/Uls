#include "libmx.h"

char *mx_strtrim(const char *str) {
	if (str) {
		int i = 0;
		int len = mx_strlen(str) - 1;
		char *new;
		int size;

		while (mx_is_space(str[i]))
			i++;
		while (mx_is_space(str[len]))
			len--;
		new = mx_strnew(len - i + 1);
		size = len - i + 1;
		for (int j = 0; j < size; j++)
			new[j] = str[i++];
		if (new == NULL)
			return mx_strnew(0);
		return new;
	}
	return NULL;
}
