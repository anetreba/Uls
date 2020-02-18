#include "uls.h"

int mx_link_check(char *file, t_flag *flags, struct stat *buf) {
    int check = 0;

    if (!flags->flag_l) 
        check = stat(file, &(*buf));
    else
        check = lstat(file, &(*buf));
    return check;
}


int mx_count_files(char **file, int *dir_count, t_flag *flags) {
	int file_count = 0;
	struct stat buf;

	for (int i = 0; file[i]; i++) {
		if (mx_link_check(file[i], flags, &buf) >= 0) {
			if ((buf.st_mode & S_IFDIR) != S_IFDIR)
                    file_count += 1;
            else if (((buf.st_mode & S_IFDIR) == S_IFDIR))
                    *dir_count += 1;
		}
		else {
			mx_printerr("uls: ");
			mx_printerr(file[i]);
			mx_printerr(": No such file or directory\n");
		}
	}
	return file_count;
}

int mx_len_starr(char **file) {
	int i = 0;

	while (file[i])
		i++;
	return i;
}

char **mx_make_mas_of_files(char **file, int file_count, t_flag *flags) {
	struct stat buf;
	char **files = (char **)malloc(sizeof(char *) * (file_count + 1));
	int i = 0;

	for (int j = 0; file[j]; j++) {
		if (mx_link_check(file[i], flags, &buf) >= 0) {
			if ((buf.st_mode & S_IFDIR) != S_IFDIR)
				files[i++] = mx_strdup(file[j]); 
		}
	}
	files[file_count] = NULL;
	return files;
}

void mx_sort_flags(t_flag *flags, char **files, int file_count, char *dir_name) {
	if (!flags->flag_f) {
		mx_bubble_sort(files, file_count);
		if (flags->flag_S)
			mx_sort_S(files, file_count, dir_name, flags);		
		else if (flags->flag_t)
			mx_sort_t(files, file_count, dir_name, flags);
	
		if (flags->flag_r)
			mx_sort_r(files, file_count);
	}
}


void mx_print_flags(t_flag *flags, char **files, int file_count, char *dir_name, int dir_count) {
	if (flags->flag_m) {
		mx_flag_m(files, file_count);
		if (dir_count != 0)
			mx_printstr(", ");
		mx_printstr("\n");
	}
	else if (flags->flag_1)
		mx_flag_1(files, file_count);
	else if (flags->flag_G || flags->flag_F || flags->flag_p)
		mx_flag_G(files, file_count, dir_name, flags);
	else if (flags->flag_l)
		mx_flag_l(files, file_count, dir_name, flags);
	else {
		int max_len = mx_count_max_len(files);
		mx_basic_print(files, file_count, max_len);
	}
}

void mx_print_dirs(char **dirs, int dir_count, int file_count, t_flag *flags) {
	if (file_count != 0 && dir_count != 0)
		mx_printstr("\n");
	for (int j = 0; dirs[j]; j++) {
		if (dir_count != 1 || file_count != 0) {
			mx_printstr(dirs[j]);
			mx_printchar(':');
			mx_printstr("\n");
		}
		mx_current_directory(flags, dirs[j]);
		if (j != dir_count - 1)
			mx_printstr("\n");
	}
} 

void mx_files_and_dir(char **file, t_flag *flags) {
	int dir_count = 0;
	int file_count = mx_count_files(file, &dir_count, flags);
	char **dirs = mx_make_mas_of_dirs(dir_count, file, mx_len_starr(file), flags);
	char **files = mx_make_mas_of_files(file, file_count, flags);
	bool buf = false;

	if (file_count > 0) {
		buf = true;
		mx_sort_flags(flags, files, file_count, NULL);
		mx_print_flags(flags, files, file_count, NULL, dir_count);
	}
	mx_del_strarr(&files);
	mx_sort_flags(flags, dirs, dir_count, NULL);
	if (flags->flag_R)
		mx_recursion_flag(dirs, dir_count, flags, buf);
	else 
		mx_print_dirs(dirs, dir_count, file_count, flags);
	mx_del_strarr(&dirs);
}

int main(int ac, char **av) {
	t_flag *flags = (t_flag *)malloc(sizeof(t_flag));
	char **file = NULL;
	mx_memset(flags, 0, sizeof(t_flag));
	file = mx_valid_flag(ac, av, flags); //files in argument
	if (file[0] == NULL)
		mx_current_directory(flags, ".");
	else 
		mx_files_and_dir(file, flags);
	//system("leaks uls");
	return 0;
}
