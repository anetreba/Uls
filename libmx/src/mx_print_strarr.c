#include "libmx.h"

void mx_print_strarr(char **arr, const char *delim) {
	if (arr && delim) {
		for (int i = 0; arr[i] != NULL; i++) {
			if (arr[i + 1] == NULL) {
				mx_printstr(arr[i]);
				mx_printchar('\n');
				return ;
			}
			mx_printstr(arr[i]);
			mx_printstr(delim);
		}
	}
}
