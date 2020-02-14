#include "uls.h"


int mx_dir_count(char **files_in_dir) {
	struct stat buf;
	int dir_count = 0;

	for (int i = 0; files_in_dir[i]; i++) {
			if (lstat(files_in_dir[i], &buf) >= 0) {
    	 		if (((buf.st_mode & S_IFDIR) == S_IFDIR))
    	                dir_count += 1;
			}
	}
	return dir_count;
}

char **mx_make_mas_of_dirs(int dir_count, char **files_in_dir, int count) {
	struct stat buf;
	int k = 0;

	if (*files_in_dir != NULL) {
		char **dirs = (char **)malloc(sizeof(char *) * (dir_count + 1));
		for (int j = 0; j < count; j++) {
				if (lstat(files_in_dir[j], &buf) >= 0) {
					if (((buf.st_mode & S_IFDIR) == S_IFDIR)) 
						dirs[k++] = mx_strdup(files_in_dir[j]);
				}
			}
		dirs[dir_count] = NULL;
		return dirs;
	}
	return NULL;
}



char **mx_make_path(char **dirs_in, char *dir_name, int dir_count, t_flag *flags) {
	if (flags->flag_a)
		dir_count -= 2;
	char **path = (char **)malloc(sizeof(char *) * (dir_count + 1));
	char *tmp = NULL;
	int j = 0;

	if (mx_strcmp(dir_name, "..") != 0) {
		for (int i = 0; dirs_in[i]; i++) {
			if (mx_strcmp(dirs_in[i], ".") != 0 && mx_strcmp(dirs_in[i], "..") != 0) {
				if (mx_strcmp(dir_name, "/") == 0)
    	    		tmp = mx_strdup(dir_name);
    			else
    	    		tmp = mx_strjoin(dir_name, "/");
				path[j] = mx_strjoin(tmp, dirs_in[i]);
				j++;
				if (tmp != NULL)
					free(tmp);
			}
		}
	}
	path[dir_count] = NULL;
	return path;
}

void mx_print_recursion(char **files_in_dir, int count, t_flag *flags, char *dir_name) {

	mx_bubble_sort(files_in_dir, count);
	if (flags->flag_m) {
		mx_flag_m(files_in_dir, count);
		mx_printstr("\n");
	}
	else if (flags->flag_1)
		mx_flag_1(files_in_dir, count);
	else if (flags->flag_G || flags->flag_F || flags->flag_p)
		mx_flag_G(files_in_dir, count, dir_name, flags);
	else {
		int max_len = mx_count_max_len(files_in_dir);		
		mx_basic_print(files_in_dir, count, max_len);
	}
}


char **mx_dir_in(t_flag *flags, char *dir_name, int *dir_count, bool *k) {
	int count = mx_count_elem_in_dir(flags, dir_name);
	char **path = NULL;
	char **dirs_in = NULL;
	if (count != 0) {
		char **files_in_dir = mx_make_mas_of_elem_in_dir(flags, dir_name, count);
		
		if (*k) {
			mx_printstr("\n");
			mx_printstr(dir_name);
			mx_printstr(":\n");
		}
		*k = true;
		mx_print_recursion(files_in_dir, count, flags, dir_name);
		path = mx_make_path(files_in_dir, dir_name, count, flags);
		*dir_count = mx_dir_count(path);
		if (*dir_count != 0)
			dirs_in = mx_make_mas_of_dirs(*dir_count, path, count);

		mx_del_strarr(&files_in_dir);
		mx_del_strarr(&path);

		return dirs_in; 
	}
	return NULL;
}



void mx_recursion_flag(char **dirs, int dir_count, t_flag *flags) {
	char **dirs_in = NULL;
	static bool k = false;
	int dir_count_in = 0;
	dir_count = 0;

	for (int i = 0; dirs[i]; i++) {
		dirs_in = mx_dir_in(flags, dirs[i], &dir_count_in, &k);
		if (dirs_in != NULL) {
			mx_recursion_flag(dirs_in, dir_count_in, flags);

			mx_del_strarr(&dirs_in);
		}
	}
}
