#include "uls.h"

void mx_my_getgrgid(char *filename, int n) {
    struct group *groupinfo;
    struct stat buff;
    char *str = NULL;

    lstat(filename, &buff);
    groupinfo = getgrgid(buff.st_gid);
    if (groupinfo != NULL) {
        mx_printstr(groupinfo->gr_name);
        mx_print_spaces(n + 1);
    }
    else {
        str = mx_itoa(buff.st_gid);
        mx_printstr(str);
        mx_print_spaces(n + 1);
        free(str);
    }
}
