#include "libmx.h"

void mx_swap_elem(void **s1, void **s2) {
	void *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}
