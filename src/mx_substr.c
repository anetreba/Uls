#include "uls.h"

char* mx_substr(const char *src, int a, int b) {
    int len = b - a;
    char *dst = (char *)malloc(sizeof(char) * (len + 1));
    
    for (int i = a; i < b && src[i] != '\0'; i++) {
        *dst = src[i];
        dst++;
    }
    *dst = '\0';
    return dst - len;
}
