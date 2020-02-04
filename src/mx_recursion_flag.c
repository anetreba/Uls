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

char **mx_make_mas_of_dirs(int dir_count, char **files_in_dir) {
	struct stat buf;
	char **dirs = (char **)malloc(sizeof(char *) * (dir_count + 1));
	int k = 0;

	for (int j = 0; files_in_dir[j]; j++) {
		if (lstat(files_in_dir[j], &buf) >= 0) {
			if (((buf.st_mode & S_IFDIR) == S_IFDIR))
				dirs[k++] = mx_strdup(files_in_dir[j]); 
		}
	}
	dirs[dir_count] = NULL;
	return dirs;
}

char **mx_make_path(char **dirs_in, char *dir_name, int dir_count) {
	char **path = (char **)malloc(sizeof(char *) * (dir_count + 1));

	for (int i = 0; dirs_in[i]; i++) {
		if (mx_strcmp(dirs_in[i], "/") == 0)
        	path[i] = dir_name;
    	else
        	path[i] = mx_strjoin(dir_name, "/");
		path[i] = mx_strjoin(path[i], dirs_in[i]);
	}
	return path;
}

void mx_print_recursion(char **files_in_dir, int count) {

	mx_bubble_sort(files_in_dir, count);
	int max_len = mx_count_max_len(files_in_dir);
	mx_basic_print(files_in_dir, count, max_len);

}

char **mx_dir_in(t_flag *flags, char *dir_name, int *dir_count) {
	int count = mx_count_elem_in_dir(flags, dir_name);
	char **files_in_dir = mx_make_mas_of_elem_in_dir(flags, dir_name, count);

	mx_printstr(dir_name);
	mx_printstr(":\n");

	mx_print_recursion(files_in_dir, count);
	mx_printstr("\n");
	char **path = mx_make_path(files_in_dir, dir_name, count);
	*dir_count = mx_dir_count(path);
	char **dirs_in = mx_make_mas_of_dirs(*dir_count, path);

	mx_del_strarr(&files_in_dir);
	return dirs_in; 
}



void mx_recursion_flag(char **dirs, int dir_count, t_flag *flags) {
	char **dirs_in = NULL;
	int dir_count_in;
	dir_count = 0;

	for (int i = 0; dirs[i]; i++) {
		dirs_in = mx_dir_in(flags, dirs[i], &dir_count_in);
		mx_recursion_flag(dirs_in, dir_count_in, flags);
	}
}
