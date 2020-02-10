#include "uls.h"

void mx_files_and_dir(char **file, t_flag *flags, int ac) {
	struct stat buf;
	int dir_count = 0;
	int file_count = 0;

	for (int i = 0; file[i]; i++) {
		if (lstat(file[i], &buf) >= 0) {
			if ((buf.st_mode & S_IFDIR) != S_IFDIR)
                    file_count += 1;
            else if (((buf.st_mode & S_IFDIR) == S_IFDIR))
                    dir_count += 1;
		}
		else {
			mx_printerr("uls: ");
			mx_printerr(file[i]);
			mx_printerr(": No such file or directory\n");
		}
	}

	char **files = (char **)malloc(sizeof(char *) * (file_count + 1));
	char **dirs = (char **)malloc(sizeof(char *) * (dir_count + 1));
	int i = 0;
	int k = 0;

	for (int j = 0; file[j]; j++) {
		if (lstat(file[j], &buf) >= 0) {
			if ((buf.st_mode & S_IFDIR) != S_IFDIR)
				files[i++] = mx_strdup(file[j]);
			else if (((buf.st_mode & S_IFDIR) == S_IFDIR))
				dirs[k++] = mx_strdup(file[j]); 
		}
	}
	files[file_count] = NULL;
	dirs[dir_count] = NULL;

	if (file_count > 0) {
		if (flags->flag_m) {
			mx_flag_m(files, file_count);
			if (dir_count != 0) {
				mx_printstr(", ");
				mx_printstr("\n");
			}
		}
		else {
			mx_bubble_sort(files, file_count);
			int max_len = mx_count_max_len(files);
			mx_basic_print(files, file_count, max_len);
		}
	}

	mx_del_strarr(&files);
	
	mx_bubble_sort(dirs, dir_count);
	
	if (flags->flag_R) {
		mx_recursion_flag(dirs, dir_count, flags);
	}
	
	else {
		if (file_count != 0)
			mx_printstr("\n");
		for (int j = 0; dirs[j]; j++) {
			if (ac != 2) {
				mx_printstr(dirs[j]);
				mx_printchar(':');
				mx_printstr("\n");
			}
			mx_current_directory(flags, dirs[j]);
			if (j != dir_count - 1)
				mx_printstr("\n");
		}
	}
	mx_del_strarr(&dirs);
}

int main(int ac, char **av)
{
	t_flag *flags = (t_flag *)malloc(sizeof(t_flag));
	char **file = NULL;
	mx_memset(flags, 0, sizeof(t_flag));
	file = mx_valid_flag(ac, av, flags); //files in argument
	if (file[0] == NULL) {
		mx_current_directory(flags, ".");
	}
	else {
		mx_files_and_dir(file, flags, ac);
	}
	//system("leaks uls");
	return 0;
}
