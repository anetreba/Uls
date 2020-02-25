#include "uls.h"

int mx_intlen(long long n) {
    int i = 1;

    for (; n > 9; i++)
        n /= 10;
    return i;
}
