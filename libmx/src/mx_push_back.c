#include "libmx.h"

void mx_push_back(t_list **list, void *data) {
	if (list) {
		t_list *new = mx_create_node(data);

		if (*list) { 
			t_list *current = *list;

			while(current->next != NULL) {
				current = current->next;
			}
			current->next = new;
		}
		else 
			*list = new;
	}
}
