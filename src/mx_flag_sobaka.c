#include "uls.h"

void my_readlink(char *str, char *filename) {
    char *ayaya = mx_strnew(1024);

    if (str[0] == 'l') {
        readlink(filename, ayaya, 1024);
        if (ayaya[0] != '\0') {
            mx_printstr(" -> ");            
            mx_printstr(ayaya);
        }
        mx_bzero(ayaya, sizeof(ayaya));
        ayaya[0] = '\0';
    }
    free(ayaya);
}

void mx_flag_sobaka(char *str, char *filename, t_flag *flags) {
    char pog_champ[1024];
    size_t size_xat = 0;
    int len = 24;
    int diff = 0;
    int diff2 = 0;

    if (str[10] == '@' && flags->flag_sobaka) {
        if (listxattr(filename, pog_champ, 1024, 1) >= 0)
        size_xat = getxattr(filename, pog_champ, 0, 1024, 0, 1);
        mx_printchar('\n');
        mx_print_spaces(8);
        diff = len - mx_strlen(pog_champ);
        mx_printstr(pog_champ);
        len = 3;
        diff2 = len - mx_intlen(size_xat);
        mx_print_spaces(diff + 1);
        mx_print_spaces(diff2);
        mx_printint(size_xat);
    }
}
