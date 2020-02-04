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


typedef struct s_flag {
	bool flag_l;
	bool flag_a;
	bool flag_A;
	bool flag_R;
}				t_flag;

int mx_dir_count(char **files_in_dir);
char **mx_make_mas_of_dirs(int dir_count, char **files_in_dir);
char **mx_make_path(char **dirs_in, char *dir_name, int dir_count);
void mx_print_recursion(char **files_in_dir, int count);
char **mx_dir_in(t_flag *flags, char *dir_name, int *dir_count);
void mx_recursion_flag(char **dirs, int dir_count, t_flag *flags);
int mx_count_max_len(char **files_in_dir);
char **mx_make_mas_of_elem_in_dir(t_flag *flags, char *dir_name, int count);
void mx_basic_print(char **files_in_dir, int count, int max_len);
int mx_count_elem_in_dir(t_flag *flags, char *dir_name);

// typedef struct s_all_info {
// 	int ac;
// 	char **av;

// 	bool flags_exist;
// 	bool file_exist;
// 	bool folder_exist;

// }				t_all_info;

// typedef struct s_in_folder{
	
// }				t_in_folder;

// typedef struct s_folder {
// 	char *name;
// 	int num_of_sub;
// 	int max_sub_len;
	
// }				t_folder;




#endif
