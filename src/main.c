#include "uls.h"

int mx_count_max_len(char **files_in_dir, t_flag *flags, char *dir_name) {
	int max = 0;

	if (*files_in_dir != NULL || files_in_dir != NULL) {		
		max = mx_strlen(files_in_dir[0]);
		for (int i = 1; files_in_dir[i]; i++) {
			if (max < mx_strlen(files_in_dir[i])) {
				max = mx_strlen(files_in_dir[i]);
				char c = mx_file_mode_check(files_in_dir[i], dir_name);
				if (flags->flag_F) {
        			if ((c == 'd') || (c == 'l') || (c == 'e') || (c == 's') || (c == 'p'))
        				max++;
				}
        		else if (flags->flag_p)
        			if (c == 'd')
        				max++;

			}
		}
	}
	return max;
}

void mx_print_flags(t_flag *flags, char **files, int file_count, char *dir_name
	, int dir_count) {
	if (flags->flag_m) {
		mx_flag_m(files, file_count);
		if (dir_count != 0)
			mx_printstr(", ");
		mx_printstr("\n");
	}
	else if (flags->flag_1)
		mx_flag_1(files, file_count);
	else if (flags->flag_G)
		mx_flag_G(files, file_count, dir_name, flags);
	else if (flags->flag_l)
		mx_flag_l(files, file_count, dir_name, flags);
	else {
		int max_len = mx_count_max_len(files, flags, dir_name);
		mx_basic_print(files, file_count, max_len, flags, dir_name);
	}
}

void mx_print_dirs(char **dirs, int dir_count, int file_count,
	t_flag *flags, int *err) {
	if (file_count != 0 && dir_count != 0)
		mx_printstr("\n");
	for (int j = 0; dirs[j]; j++) {
		if (dir_count != 1 || file_count != 0) {
			mx_printstr(dirs[j]);
			mx_printchar(':');
			mx_printstr("\n");
		}
		mx_current_directory(flags, dirs[j], err);
		if (j != dir_count - 1)
			mx_printstr("\n");
	}
} 

void mx_files_and_dir(char **file, t_flag *flags, int *err) {
	int dir_count = 0;
	int file_count = mx_count_files(file, &dir_count, flags, err);
	char **files = mx_make_mas_of_files(file, file_count, flags);
	char **dirs = mx_make_mas_of_dirs(dir_count, file, mx_len_starr(file),
	 flags);
	bool buf = false;

	if (file_count > 0) {
		buf = true;
		mx_sort_flags(flags, files, file_count, NULL);
		mx_print_flags(flags, files, file_count, NULL, dir_count);
	}
	mx_del_strarr(&files);
	mx_sort_flags(flags, dirs, dir_count, NULL);
	if (flags->flag_R)
		mx_recursion_flag(dirs, dir_count, flags, buf, err);
	else 
		mx_print_dirs(dirs, dir_count, file_count, flags, err);
	mx_del_strarr(&dirs);
}

int main(int ac, char **av) {
	t_flag *flags = (t_flag *)malloc(sizeof(t_flag));
	char **file = NULL;
	int err = 0;


	mx_memset(flags, 0, sizeof(t_flag));
	file = mx_valid_flag(ac, av, flags);
	if (file[0] == NULL)
		mx_current_directory(flags, ".", &err);
	else 
		mx_files_and_dir(file, flags, &err);
	return err;
}
