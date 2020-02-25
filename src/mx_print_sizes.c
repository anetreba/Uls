#include "uls.h"

char *mx_long_to_hex(unsigned long long nbr) {
    unsigned long long n = nbr;
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

char *hex_major_minor(long long n) {
    char str[11] = "0x00000000\0";
    char *tmp;
    char *hex = mx_long_to_hex(n);
    int len = mx_strlen(str) - mx_strlen(hex);
    int i = 0;

    while (str[len])
        str[len++] = hex[i++];
    tmp = mx_strdup(str);
    free(hex);
    return tmp;
}

void print_size(char *s, int n, t_flag *flags) {    
    if (flags->flag_h) {
        int len = mx_strlen(s);
        int diff = 6 - len;

        mx_print_spaces(diff);
        mx_printstr(s);
        mx_print_spaces(1);
    }
    else {
        mx_print_spaces(n + 1);
        mx_printstr(s);
        mx_print_spaces(1);
    }
    free(s);
}

void help_major(t_len_column *lens, int diff_maj, int diff_min) {
    mx_print_spaces(diff_maj);
    mx_printint(lens->maj);
    mx_printchar(',');
    if (lens->min < 256) {
        mx_print_spaces(diff_min);
        mx_printint(lens->min);
        mx_print_spaces(1);
    }
    else {
        char *str = hex_major_minor(lens->min);
        mx_print_spaces(1);
        mx_printstr(str);
        mx_print_spaces(1);
        free(str);
    }
}

void print_major(t_len_column *lens, struct stat buff, int col, char *pr_dost, 
    t_flag *flags) {
    if (pr_dost[0] == 'c' || pr_dost[0] == 'b') {
        lens->min = minor(buff.st_rdev);
        lens->maj = major(buff.st_rdev);
        int len_min = mx_intlen(lens->min);
        int len_maj = mx_intlen(lens->maj);
        int diff_maj = 4 - len_maj;
        int diff_min = 4 - len_min;

        help_major(lens, diff_maj, diff_min);
    }
    else if (lens->bc) {
        mx_print_spaces(7);
        print_size(flag_h_check(buff.st_size, flags), col, flags);
    }
    else
        print_size(flag_h_check(buff.st_size, flags), col, flags);
}
