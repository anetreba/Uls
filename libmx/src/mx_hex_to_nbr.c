#include "libmx.h" 

unsigned long mx_hex_to_nbr(const char *hex) {
	unsigned long nbr = 0;
	unsigned long base = 1;

	for (int i = mx_strlen(hex) - 1; i >= 0; i--) {
		if (hex[i] >= '0' && hex[i] <= '9') {
			nbr += (hex[i] - 48) * base;
			base *= 16;
		}
		if (hex[i] >= 'A' && hex[i] <= 'F') {
			nbr += (hex[i] - 55) * base;
			base *= 16;
		}
		if (hex[i] >= 'a' && hex[i] <= 'f') {
			nbr += (hex[i] - 87) * base;
			base *= 16;
		}
	}
	return nbr;
}
