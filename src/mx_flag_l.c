#include "uls.h"

static void print_link(unsigned int number, int otstup) {
	char *str = mx_itoa(number);

    mx_print_spaces(otstup + 1);
	mx_printstr(str);
	mx_print_spaces(1);
	free(str);
}

static void total_blocks(char **path, t_len_column *lens, char *dir_name) {
    struct stat buff;
    long long total = 0;
    int i = 0;

    mx_memset(lens, 0, sizeof(t_len_column));
    for (; path[i]; i++) {
        lstat(path[i], &buff);
        filling_struct(lens, buff);
       	total += buff.st_blocks;
    }
   if (dir_name != NULL) {
        mx_printstr("total ");
        mx_printint(total);
        mx_printchar('\n');
   }
}

static void help_flag_l(char *path, t_flag *flags, char *files_in_dir, 
    char *pr_dost) {
        mx_my_time(path, flags);
        mx_printstr(files_in_dir);
        my_readlink(pr_dost, path);
        mx_flag_sobaka(pr_dost, path, flags);
        mx_printchar('\n');
}

static void rofl(char *dir_name, char **path) {
    if (dir_name != NULL)
        mx_del_strarr(&path);
}

void mx_flag_l(char **files_in_dir, int count, char *dir_name, t_flag *flags) {
    char pr_dost[12];
    struct stat buff;
    t_len_column *lens = (t_len_column *)malloc(sizeof(t_len_column));
    t_diff_len *l = (t_diff_len *)malloc(sizeof(t_diff_len));
    char **path = mx_find_path_l(files_in_dir, dir_name, count, flags);;

    total_blocks(path, lens, dir_name);
    for (int i = 0; path[i]; i++) {
        lstat(path[i], &buff);
        len_difference(l, lens, buff);
        mx_printstr(mx_mychmod(buff.st_mode, pr_dost, path[i], lens));
        print_link(buff.st_nlink, l->diff_link);
        mx_my_getuid(path[i], l->diff_user);
        mx_my_getgrgid(path[i], l->diff_gid);
        print_major(lens, buff, l->diff_size, pr_dost, flags);
        help_flag_l(path[i], flags, files_in_dir[i], pr_dost);
    }
    free(lens);
    free(l);
    rofl(dir_name, path);
}
