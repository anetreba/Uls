#include "uls.h"

int mx_dir_count(char **files_in_dir, t_flag *flags) {
	struct stat buf;
	int dir_count = 0;

	for (int i = 0; files_in_dir[i]; i++) {
			if (mx_link_check(files_in_dir[i], flags, &buf) >= 0) {
    	 		if (((buf.st_mode & S_IFDIR) == S_IFDIR))
    	                dir_count += 1;
			}
	}
	return dir_count;
}

void mx_print_recursion(char **files_in_dir, int count, t_flag *flags,
	char *dir_name) {
	mx_sort_flags(flags, files_in_dir, count, dir_name);
	if (flags->flag_m) {
		mx_flag_m(files_in_dir, count);
		mx_printstr("\n");
	}
	else if (flags->flag_l)
		mx_flag_l(files_in_dir, count, dir_name, flags);
	else if (flags->flag_1)
		mx_flag_1(files_in_dir, count);
	else if (flags->flag_G)
		mx_flag_G(files_in_dir, count, dir_name, flags);
	else {
		int max_len = mx_count_max_len(files_in_dir);		
		mx_basic_print(files_in_dir, count, max_len, flags, dir_name);
	}
}

void mx_print_dir_name(char *dir_name) {
	mx_printstr("\n");
	mx_printstr(dir_name);
	mx_printstr(":\n");
}

char **mx_dir_in(t_flag *flags, char *dir_name, int *dir_count, bool *k,
	bool buf, int *err) {
	int cou = mx_count_elem_in_dir(flags, dir_name, err);
	char **path = NULL;
	char **dirs_in = NULL;

	if (cou != 0) {
		char **files_in_dir = mx_make_mas_of_elem_in_dir(flags, dir_name, cou);
		
		if (buf || *k) 
			mx_print_dir_name(dir_name);
		*k = true;
		mx_print_recursion(files_in_dir, cou, flags, dir_name);
		path = mx_make_path(files_in_dir, dir_name, cou, flags);
		*dir_count = mx_dir_count(path, flags);
		if (*dir_count != 0)
			dirs_in = mx_make_mas_of_dirs(*dir_count, path, cou, flags);
		mx_del_strarr(&files_in_dir);
		mx_del_strarr(&path);
		return dirs_in; 
	}
	return NULL;
}

void mx_recursion_flag(char **dirs, int dir_count, t_flag *flags,
	bool buf, int *err) {
	char **dirs_in = NULL;
	static bool k = false;
	int dir_count_in = 0;
	dir_count = 0;

	for (int i = 0; dirs[i]; i++) {
		dirs_in = mx_dir_in(flags, dirs[i], &dir_count_in, &k, buf, err);
		if (dirs_in != NULL) {
			mx_recursion_flag(dirs_in, dir_count_in, flags, buf, err);
			mx_del_strarr(&dirs_in);
		}
	}
}
