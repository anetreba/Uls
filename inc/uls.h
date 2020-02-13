#ifndef ULS_H
#define ULS_H

#include "libmx/inc/libmx.h"

#include <errno.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/acl.h>
#include <sys/types.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <wchar.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>


typedef struct s_flag {
	bool flag_l;
	bool flag_a;
	bool flag_A;
	bool flag_R;
	bool flag_m;
	bool flag_1;
	bool flag_S;
	bool flag_t;
	bool flag_u;
	bool flag_c;
	bool flag_r;
	bool flag_G;
}				t_flag;

typedef struct s_sort {
    char *name;

    long long size;
    long long time_modefied;
    long long time_access;
    long long time_changed;
}               t_sort;

int mx_dir_count(char **files_in_dir);
char **mx_make_mas_of_dirs(int dir_count, char **files_in_dir, int count);
char **mx_make_path(char **dirs_in, char *dir_name, int dir_count, t_flag *flags);
void mx_print_recursion(char **files_in_dir, int count, t_flag *flags);
char **mx_dir_in(t_flag *flags, char *dir_name, int *dir_count, bool *k);
void mx_recursion_flag(char **dirs, int dir_count, t_flag *flags);
char **mx_make_mas_of_elem_in_dir(t_flag *flags, char *dir_name, int count);
int mx_count_elem_in_dir(t_flag *flags, char *dir_name);


int mx_count_max_len(char **files_in_dir);
int mx_num_of_cols(char **files_in_dir, int count);
void mx_choose_print_action(char *files_in_dir);
void basic_tab_print(int arg_len, int max_len);
void mx_basic_print(char **files_in_dir, int count, int max_len);


char **mx_valid_flag(int ac, char **av, t_flag *flags);

void mx_flag_m(char **files_in_dir, int count);
void mx_flag_1(char **files_in_dir, int count);

void *mx_name_of_dir(char *s, int c);
int mx_count_elem_in_dir(t_flag *flags, char *dir_name);
char **mx_make_mas_of_elem_in_dir(t_flag *flags, char *dir_name, int count);
void mx_current_directory(t_flag *flags, char *dir_name);

void mx_sort_S(char **files, int dir_count, char *file_name, t_flag *flags);
void mx_sort_t(char **files, int dir_count, char *file_name, t_flag *flags);
void mx_sort_r(char **files, int count);

#endif
