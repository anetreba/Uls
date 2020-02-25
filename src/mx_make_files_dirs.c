#include "uls.h"

int mx_link_check(char *file, t_flag *flags, struct stat *buf) {
    int check = 0;

    if (!flags->flag_l) 
        check = stat(file, &(*buf));
    else
        check = lstat(file, &(*buf));
    return check;
}

int mx_count_files(char **file, int *dir_count, t_flag *flags, int *err) {
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
			*err = 1;
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
		if (mx_link_check(file[j], flags, &buf) >= 0) {
			if ((buf.st_mode & S_IFDIR) != S_IFDIR) {
				files[i++] = mx_strdup(file[j]); 
			}
		}
	}
	files[file_count] = NULL;
	return files;
}

void mx_sort_flags(t_flag *flags, char **files, int file_count,
	char *dir_name) {
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
