#include "libmx.h"

 char *mx_itoa(unsigned int number) {
     char *str;
     long nb = number;
     int len = mx_count_digits(nb);

     if (nb < 0) 
        nb = -nb;
     str = mx_strnew(len);
     while(len--) {
         str[len] = nb % 10 + 48;
         nb /= 10;
     }
     if (number < 0)
        str[0] = '-';
     return str;
 }
