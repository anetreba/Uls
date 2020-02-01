#include "libmx.h" 

void mx_printint(int n) {
	long nb = n;

	if (nb < 0) {
		mx_printchar('-');
		nb = -nb;
	}
	if (nb / 10 != 0)
		mx_printint(nb / 10);
	mx_printchar(nb % 10 + 48);
}
