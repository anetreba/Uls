#include "libmx.h"

int mx_arrlen(char **arr) {
	int i = 0;
	int j = 0;
	
	while (arr[i]) {
		while (arr[j])
			j++;
		i++;
	}
	return i;
}
