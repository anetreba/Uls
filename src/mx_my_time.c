#include "uls.h"

static char *time_T(time_t time, t_flag *flags) {
    char *str;

    if (flags->flag_T)
        str = mx_substr(ctime(&(time)), 4, 24);
    else
       str = mx_substr(ctime(&(time)), 4, 16);
    return str;
}

void time_help(time_t *time, t_flag *flags, struct stat *file_info) {
    if (flags->flag_u) 
        *time = file_info->st_atime;
    else if (flags->flag_c)
        *time = file_info->st_ctime;
    else if (flags->flag_U)
        *time = file_info->st_birthtime;
    else 
        *time = file_info->st_mtime;
}

static void time_else(struct stat *file_info, char *sub, time_t time,
    t_flag *flags) {
    sub = time_T(time, flags);
    mx_printstr(sub);
    mx_print_spaces(1);
    free(file_info);
    free(sub);
}

void mx_my_time(char *filename, t_flag *flags) {
    struct stat *file_info = malloc(sizeof(struct stat));
    char *sub = NULL;
    time_t sec = time(NULL);
    time_t time = 0;

    lstat(filename, file_info);
    time_help(&time, flags, file_info);
    if (((sec - (time)) > 15552000 || sec < 0 ) && !(flags->flag_T)) {
        sub = mx_substr(ctime(&(time)), 4, 10);
    	mx_printstr(sub);
    	free(sub);
    	mx_print_spaces(2);
    	sub = mx_substr(ctime(&(time)), 20, 24);
    	mx_printstr(sub);
    	mx_print_spaces(1);
    	free(file_info);
    }
    else
        time_else(file_info, sub, time, flags); 
    free(sub);
}
