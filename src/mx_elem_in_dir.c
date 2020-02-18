#include "uls.h"

void *mx_name_of_dir(char *s, int c) {
	char *ptr = s + mx_strlen(s);

	while (ptr) {
		if (*ptr == (unsigned char)c)
			return ptr + 1;
		ptr--;
	}
	return s;
}

int mx_count_elem_in_dir(t_flag *flags, char *dir_name) {
	DIR *dir = opendir(dir_name);
	struct dirent *entry;
	int count = 0;

	if (dir == NULL) {
		mx_printerr("uls: ");
	 	perror(mx_name_of_dir(dir_name, '/')); //ошибка Permission denied
	 	return 0;
	}
	else {
		while ((entry = readdir(dir)) != NULL) {
			if (flags->flag_a == true || flags->flag_f)
				count++;
			else if (flags->flag_A == true) {
				if (entry->d_name[1] != '.' && entry->d_name[1] != '\0')
					count++;
			}
			else if (entry->d_name[0] != '.')
				count++;
		}
	}	
	closedir(dir);

	return count;
}

char **mx_make_mas_of_elem_in_dir(t_flag *flags, char *dir_name, int count) {
	DIR *dir = opendir(dir_name);
	struct dirent *entry;
	int i = 0;
	
	if (dir == NULL)
		return NULL;
	else {
		char **files_in_dir = (char **)malloc(sizeof(char *) * (count + 1));
		while ((entry = readdir(dir)) != NULL) {
			if (flags->flag_a == true || flags->flag_f)
				files_in_dir[i++] = mx_strdup(entry->d_name);
			else if (flags->flag_A == true) {
				if (entry->d_name[1] != '.' && entry->d_name[1] != '\0')
					files_in_dir[i++] = mx_strdup(entry->d_name);
			}
			else if (entry->d_name[0] != '.')
				files_in_dir[i++] = mx_strdup(entry->d_name);
		}
		files_in_dir[i] = NULL;
		closedir(dir);
		return files_in_dir;
	}
	return NULL;
}


void mx_current_directory(t_flag *flags, char *dir_name) {
	int count = mx_count_elem_in_dir(flags, dir_name);
	char **files_in_dir = mx_make_mas_of_elem_in_dir(flags, dir_name, count);

	if (!flags->flag_f) {
		mx_bubble_sort(files_in_dir, count);
	
		if (flags->flag_S)
			mx_sort_S(files_in_dir, count, dir_name, flags);
		else if (flags->flag_t)
			mx_sort_t(files_in_dir, count, dir_name, flags);
		
		if (flags->flag_r)
			mx_sort_r(files_in_dir, count);
	}
	if (flags->flag_m) {
		mx_flag_m(files_in_dir, count);
		mx_printchar('\n');
	}
	else if (flags->flag_1) {
		mx_flag_1(files_in_dir, count);
	}
	else if (flags->flag_G)
		mx_flag_G(files_in_dir, count, dir_name, flags);
	else if (flags->flag_l)
		mx_flag_l(files_in_dir, count, dir_name, flags);
	else {
		int max_len = mx_count_max_len(files_in_dir);
		mx_basic_print(files_in_dir, count, max_len);
	}
	bool buf = true;
	if (flags->flag_R) {
		// mx_printchar('\n');
		char **path = mx_make_path(files_in_dir, dir_name, count, flags);
		int dir_count = mx_dir_count(path, flags);
		char **dirs_in = mx_make_mas_of_dirs(dir_count, path, count, flags);
		mx_recursion_flag(dirs_in, dir_count, flags, buf);
	}
	mx_del_strarr(&files_in_dir);

}
