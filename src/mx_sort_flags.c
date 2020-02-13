#include "uls.h"

t_sort *mx_pasre_struct(char **files, char *file_name, int dir_count, t_flag *flags) {
	t_sort *info_file = (t_sort *)malloc(sizeof(t_sort) * (dir_count));
	struct stat sb;
	char **path_name = NULL;

	mx_memset(info_file, 0, sizeof(t_sort));
	if (file_name != NULL) {
		path_name = mx_make_path(files, file_name, dir_count, flags);
	}
	for (int i = 0; i < dir_count; i++) {

		info_file[i].name = mx_strdup(files[i]);
		if (file_name != NULL)
			lstat(path_name[i], &sb);
		else
			lstat(files[i], &sb);
		info_file[i].size = sb.st_size;
		info_file[i].time_modefied = sb.st_mtime;
		info_file[i].time_access = sb.st_atime;
		info_file[i].time_changed = sb.st_ctime;
	}
	if (path_name != NULL)
		mx_del_strarr(&path_name);
	return info_file;
}

void mx_swap_struct(t_sort *info_file_1, t_sort *info_file_2) {
	t_sort tmp = *info_file_1;
	*info_file_1 = *info_file_2;
	*info_file_2 = tmp;
}

static void swap(char **s1, char **s2) {
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void mx_dell_stuct(t_sort **info_file, int dir_count) {
    if (info_file && *info_file) {
        for (int i = 0; i < dir_count; i++) {
        	mx_strdel(&(*info_file)[i].name);
        }
        free(*info_file);
        *info_file = NULL;
    }
}

void mx_sort_S(char **files, int dir_count, char *file_name, t_flag *flags) {
	int i = 0;
	int size = dir_count;
	t_sort *info_file = mx_pasre_struct(files, file_name, dir_count, flags);

		while (i < size) {
			if (info_file[i].size < info_file[i + 1].size) {
				swap(&files[i], &files[i + 1]);
				mx_swap_struct(&info_file[i], &info_file[i + 1]);		
			}
			i++;
			if (i == size - 1) {
				i = 0;
				size--;
			} 
		}
	mx_dell_stuct(&info_file, dir_count);
}

void mx_sort_t(char **files, int dir_count, char *file_name, t_flag *flags) {
	int i = 0;
	int size = dir_count;
	t_sort *info_file = mx_pasre_struct(files, file_name, dir_count, flags);

	while (i < size) {
		if ((info_file[i].time_access < info_file[i + 1].time_access) && flags->flag_u) {
			swap(&files[i], &files[i + 1]);
			mx_swap_struct(&info_file[i], &info_file[i + 1]);
		}
		else if ((info_file[i].time_changed < info_file[i + 1].time_changed) && flags->flag_c) {
			swap(&files[i], &files[i + 1]);
			mx_swap_struct(&info_file[i], &info_file[i + 1]);
		}
		else if ((info_file[i].time_modefied < info_file[i + 1].time_modefied)) {
			swap(&files[i], &files[i + 1]);
			mx_swap_struct(&info_file[i], &info_file[i + 1]);		
		}
		i++;
		if (i == size - 1) {
			i = 0;
			size--;
		} 
	}
	mx_dell_stuct(&info_file, dir_count);
}

void mx_sort_r(char **files, int count) {
	for (int i = 0; i <= (count - 1) / 2; i++) {
		swap(&files[i], &files[(count - 1) - i]);
	}
}
