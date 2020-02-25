#include "uls.h"

static void diff_help(t_diff_len *l, t_len_column *lens);

void filling_struct(t_len_column *lens, struct stat buff) {
    struct passwd *userinfo = NULL;
    struct group *groupinfo;

    if (lens->len_link < mx_intlen(buff.st_nlink))
        lens->len_link = mx_intlen(buff.st_nlink);
    userinfo = getpwuid(buff.st_uid);
    if (lens->len_user < mx_strlen(userinfo->pw_name))
        lens->len_user = mx_strlen(userinfo->pw_name);
    groupinfo = getgrgid(buff.st_gid);
    if (groupinfo != NULL) {
        if (lens->len_gid < mx_strlen(groupinfo->gr_name))
            lens->len_gid = mx_strlen(groupinfo->gr_name);
    }
    else { 
        if (lens->len_gid < mx_intlen(userinfo->pw_gid))
            lens->len_gid = mx_intlen(userinfo->pw_gid);
    }
    if (lens->len_size < mx_intlen(buff.st_size))
       lens->len_size = mx_intlen(buff.st_size);
}


void len_difference(t_diff_len *l, t_len_column *lens, struct stat buff) {   
    struct passwd *userinfo = NULL;
    struct group *groupinfo = NULL;

    diff_help(l, lens);
    if (lens->len_link >= mx_intlen(buff.st_nlink))
        l->diff_link -= mx_intlen(buff.st_nlink);
    if (lens->len_size >= mx_intlen(buff.st_size))
        l->diff_size -= mx_intlen(buff.st_size);
    userinfo = getpwuid(buff.st_uid);
    if (lens->len_user >= mx_strlen(userinfo->pw_name))
        l->diff_user -= mx_strlen(userinfo->pw_name);
    groupinfo = getgrgid(buff.st_gid);
    if (groupinfo != NULL) {
        if (lens->len_gid >= mx_strlen(groupinfo->gr_name))
            l->diff_gid -= mx_strlen(groupinfo->gr_name);
    }
    else {
        if (lens->len_gid >= mx_intlen(userinfo->pw_gid))
           l->diff_gid -= mx_intlen(userinfo->pw_gid);
    }
}

static void diff_help(t_diff_len *l, t_len_column *lens) {
    l->diff_link = lens->len_link;
    l->diff_size = lens->len_size;
    l->diff_user = lens->len_user;
    l->diff_gid = lens->len_gid;
}
