#include "libmx.h"

int mx_count_digits(long nb) {
    int len = 1;
    int sign = 0;

    if (nb < 0) {
        sign = 1;
        nb = -nb;
    }
    while (nb / 10) {
       len++;
       nb /= 10;
    }
    if (sign)
        len++;
    return len;
}
