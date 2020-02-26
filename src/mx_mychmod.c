#include "uls.h"

static void permissions(int mode, char *str);
static void permissions2(int mode, char *str);

char *mx_mychmod(int mode, char *str, char *dir_mame, t_len_column *lens) {
    acl_t acl = NULL;
    ssize_t xattr = 0;
    char buf[1024];
    char *text_acl;

    mx_strcpy(str, "-----------");
    acl = acl_get_file(dir_mame, ACL_TYPE_EXTENDED);
    xattr = listxattr(dir_mame, buf, 0, XATTR_NOFOLLOW);
    text_acl = acl_to_text(acl, &xattr);
    permissions(mode, str);
    permissions2(mode, str);
    if (xattr > 0)
        str[10] = '@';
    else
        str[10] = (text_acl != NULL) ? '+' : ' ';
    if (str[0] == 'b' || str[0] == 'c')
        lens->bc = true;
    acl_free(acl);
    return str;
}

static void permissions(int mode, char *str) {
    if (S_ISDIR(mode))
        str[0] = 'd';
    if (S_ISCHR(mode))
        str[0] = 'c';
    if (S_ISBLK(mode))
        str[0] = 'b';
    if (S_ISLNK(mode))
        str[0] =  'l';
    if (mode & S_IRUSR)
        str[1] = 'r';
    if (mode & S_IWUSR)
        str[2] = 'w';
    if (mode & S_IXUSR)
        str[3] = 'x';
    if ((mode & S_ISUID) == S_ISUID)
        str[3] = 's';
    if (mode & S_ISUID)
        str[3] = (str[3] == 'x') ? 's' : 'S';
}

static void permissions2(int mode, char *str) {
    if (mode & S_IRGRP)
        str[4] = 'r';
    if (mode & S_IWGRP)
        str[5] = 'w';
    if (mode & S_IXGRP)
        str[6] = 'x';
    if ((mode & S_ISGID) == S_ISGID)
        str[6] = 's';
    if (mode & S_ISGID)
        str[6] = (str[6] == 'x') ? 's' : 'S';
    if (mode & S_IROTH)
        str[7] = 'r';
    if (mode & S_IWOTH)
        str[8] = 'w';
    if (mode & S_IXOTH)
        str[9] = 'x';
    if (mode & S_ISVTX)
        str[9] = (str[9] == 'x') ? 't' : 'T';
}
