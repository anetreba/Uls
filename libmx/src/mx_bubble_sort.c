#include "libmx.h" 

static void swap(char **s1, char **s2);

int mx_bubble_sort(char **arr, int size) {
	int count = 0;
	int i = 0;

	while (i < size) {
		if (mx_strcmp(arr[i], arr[i + 1]) > 0) {
			swap(&arr[i], &arr[i + 1]);		
			count++;
		}
		i++;
		if (i == size - 1) {
			i = 0;
			size--;
		} 
	}
	return count;
}

static void swap(char **s1, char **s2) {
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}
