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

int mx_print_error(char *dir_name, int *err) {
	*err = 1;
	mx_printerr("uls: ");
	perror(mx_name_of_dir(dir_name, '/'));
	return 0;
}

int mx_count_elem_in_dir(t_flag *flags, char *dir_name, int *err) {
	DIR *dir = opendir(dir_name);
	struct dirent *entry;
	int count = 0;

	if (dir == NULL)
		return mx_print_error(dir_name, err);
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
	char **files_in_dir = (char **)malloc(sizeof(char *) * (count + 1));
	
	while ((entry = readdir(dir)) != NULL) 
		if (flags->flag_a == true || flags->flag_f)
			files_in_dir[i++] = mx_strdup(entry->d_name);
		else if (flags->flag_A == true) {
			if (entry->d_name[1] != '.' && entry->d_name[1] != '\0')
				files_in_dir[i++] = mx_strdup(entry->d_name);
		}
		else if (entry->d_name[0] != '.')
			files_in_dir[i++] = mx_strdup(entry->d_name);
	files_in_dir[i] = NULL;
	closedir(dir);
	return files_in_dir;
}

void mx_current_directory(t_flag *flags, char *dir_name, int *err) {
	int count = mx_count_elem_in_dir(flags, dir_name, err);
	bool buf = true;

	if (count != 0) {
		char **files_in_dir = mx_make_mas_of_elem_in_dir(flags, dir_name,
		count);
		
		mx_sort_flags(flags, files_in_dir, count, dir_name);
		mx_print_flags(flags, files_in_dir, count, dir_name, 0);
		if (flags->flag_R && !(flags->flag_f)) {
			char **path = mx_make_path(files_in_dir, dir_name, &count, flags);
			int dir_count = mx_dir_count(path, flags);
			char **dirs_in = mx_make_mas_of_dirs(dir_count, path, count,
				flags);
			
			mx_del_strarr(&path);
			mx_recursion_flag(dirs_in, dir_count, flags, buf, err);
			mx_del_strarr(&dirs_in);
		}
		mx_del_strarr(&files_in_dir);
	}
}
