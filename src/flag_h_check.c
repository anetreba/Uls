#include "uls.h"

char *flag_h_check(double size, t_flag *flags) {
    char *str = NULL;
    char *tmp = NULL;
    const char *format[] = {"B", "K", "M", "G", "T"};
    int i = 0;
    
    if (flags->flag_h) {
        while (size > 1024) {
            size /= 1024.0;
            i++;
        }
        str = mx_itoa(size);
        tmp = mx_strjoin(str, format[i]);
        free(str);
    }
    else
        tmp = mx_itoa(size);
    return tmp;   
}
