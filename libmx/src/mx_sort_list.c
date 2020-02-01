#include "libmx.h"

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)) {
	int i = 0;
	int size = mx_list_size(lst);
	t_list *new = lst;

	while (i < size) {
		if (cmp(lst->data, lst->next->data)) {
			mx_swap_elem(&(lst->data), &(lst->next->data));
		}
		lst = lst->next;
		i++;
		if (i == size - 1) {
			lst = new;
			i = 0;
			size--;
		}
	}
	return new;
}
