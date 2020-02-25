#include "uls.h"

void mx_my_getuid(char *filename, int n) {
    struct passwd *userinfo = NULL;
    uid_t userid;
    struct stat buff;

    lstat(filename, &buff);
    userid = buff.st_uid;
    userinfo = getpwuid(userid);
    if (userinfo != NULL) {
        mx_printstr(userinfo->pw_name);
        mx_print_spaces(n);
        mx_print_spaces(2);
    }
}
