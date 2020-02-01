#include "libmx.h"

 int mx_quicksort(char **arr, int left, int right) { 
 	int l = left;
 	int r = right;
 	int m = left + (right - left) / 2;
 	int count = 0;

 	if (!arr || *arr == NULL)
 		return -1; 
 	while(l <= r) {
 		for (; mx_strlen(arr[l]) < mx_strlen(arr[m]); l++);
 		for (; mx_strlen(arr[r]) > mx_strlen(arr[m]); r--);

 		if (l <= r) {
 			if (mx_strlen(arr[l]) > mx_strlen(arr[r])) {
 				mx_swap_elem((void**)&arr[l], (void**)&arr[r]);
 				count++;
 			}
 			l++;
 			r--;
 		}
 	}
 	return count += ((l < right) ? mx_quicksort(arr, l, right) : 0)
 	+ ((left < r) ? mx_quicksort(arr, left, r) : 0);
 }
