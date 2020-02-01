#include "libmx.h" 

int mx_binary_search(char **arr, int size, const char *s, int *count) {
	int left = 0;
	int right = size - 1;
	int mid;

	*count = 0;
	while (left <= right) {
		mid = left + (right - left) / 2;
		*count += 1;
		if (mx_strcmp(arr[mid], s) > 0)
			right = mid - 1;
		if (mx_strcmp(arr[mid], s) < 0)
			left = mid + 1;
		if (mx_strcmp(arr[mid], s) == 0)
			return mid;
	}
	*count = 0;
	return -1;
}
