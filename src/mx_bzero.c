#include "uls.h"

void mx_bzero(void *s, size_t size) {
    char *str = (char *)s;
  
    for (size_t i = 0; i < size; ++i)
        str[i] = '\0';
    str = NULL;
}
