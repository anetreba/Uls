#include "libmx.h"

int mx_sqrt(int x) {
	unsigned int res = 1;

	if (x > 0) {
		while (res * res <= (unsigned int)x) {
			if (res * res == (unsigned int)x)
				return res;
			res++;
		}
	}
	return 0;
}
