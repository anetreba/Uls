#include "libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
	unsigned long n = nbr;
	int len = 1;
	char *res;

	while (n / 16) {
		len++;
		n /= 16;
	}
	res = mx_strnew(len);
	while (len--) {
		res[len] = (nbr % 16 < 10) ? nbr % 16 + 48 : nbr % 16 + 87;
		nbr /= 16;
	}
	return res;
}
