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
		//mx_del_strarr(&files_in_dir);
		return dirs;
	}
	return NULL;
}


char **mx_make_path(char **dirs_in, char *dir_name, int dir_count) {
	char **path = (char **)malloc(sizeof(char *) * (dir_count + 1));
	char *tmp = NULL;

	for (int i = 0; dirs_in[i]; i++) {
		if (mx_strcmp(dir_name, "/") == 0)
        	tmp = mx_strdup(dir_name);
    	else
        	tmp = mx_strjoin(dir_name, "/");
		path[i] = mx_strjoin(tmp, dirs_in[i]);
		//printf("TMP == %s\n", tmp);
		//tmp = NULL;
		// if (i == 1)
		//free(tmp);
	}
	//system("leaks uls");
	// for (int i = 0; path[i]; i++)
	// 	printf("PATH  =  %s,", path[i]);
	// printf("\n");
		//system("leaks -q uls");
	return path;
}

void mx_print_recursion(char **files_in_dir, int count) {

	mx_bubble_sort(files_in_dir, count);
	int max_len = mx_count_max_len(files_in_dir);		
	mx_basic_print(files_in_dir, count, max_len);

}


char **mx_dir_in(t_flag *flags, char *dir_name, int *dir_count) {
	int count = mx_count_elem_in_dir(flags, dir_name);
	char **path = NULL;
	char **dirs_in = NULL;
	//mx_del_strarr(&path);
	if (count != 0) {
		char **files_in_dir = mx_make_mas_of_elem_in_dir(flags, dir_name, count);
		mx_printstr(dir_name);
		mx_printstr(":\n");		
		mx_print_recursion(files_in_dir, count);
		mx_printstr("\n");
		path = mx_make_path(files_in_dir, dir_name, count);
		*dir_count = mx_dir_count(path);
		if (*dir_count != 0)
			dirs_in = mx_make_mas_of_dirs(*dir_count, path, count);
		// if (path && *path) {
		//	mx_del_strarr(&path);
		// }
		// if (vslutiak == 0) {
		// 	mx_del_strarr(&files_in_dir);
		// 	vslutiak++;
		// }

		return dirs_in; 
	}
	return NULL;
}



void mx_recursion_flag(char **dirs, int dir_count, t_flag *flags) {
	char **dirs_in = NULL;
	//static int k = 0;
	int dir_count_in = 0;
	dir_count = 0;
	// printf("<<<%d\n", dir_count);

	for (int i = 0; dirs[i]; i++) {
		dirs_in = mx_dir_in(flags, dirs[i], &dir_count_in);
	// 	printf(">>>%s\n", dirs[i]);
	// 	printf("<<<%s\n", dirs_in[i]);
	// printf("<%d>\n", errno);
	// 	if (++k == 5)
	// 		exit(1);
		if (dirs_in != NULL) {
			mx_recursion_flag(dirs_in, dir_count_in, flags);
		}
	}
}
