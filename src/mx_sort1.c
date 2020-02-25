#include "uls.h"

void mx_struct_flag4(char *av, t_flag *flags, char *flag, bool *fl) {
	for (int j = 1; av[j]; j++) {
		if (av[j] == flag[4]) {
		 	flags->flag_m = true;
		 	*fl = true;
		}
		else if (av[j] == flag[10]) {
			flags->flag_r = true;
			*fl = true;
		}
		else if (av[j] == flag[11]) {
			flags->flag_G = true;
			*fl = true;
		}
		else if (av[j] == flag[12]) {
			flags->flag_p = true;
			*fl = true;
		}
	}
}

bool mx_error_case(char av, char *flag) {
	if (mx_memchr(flag, av, mx_strlen(flag)) == NULL)
		return true;
	return false;
}

void mx_swap_struct(t_sort *info_file_1, t_sort *info_file_2) {
	t_sort tmp = *info_file_1;
	*info_file_1 = *info_file_2;
	*info_file_2 = tmp;
}

void mx_swap(char **s1, char **s2) {
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void mx_sort_S(char **files, int dir_count, char *file_name, t_flag *flags) {
	int i = 0;
	int size = dir_count;
	if (size > 1) {
		t_sort *info_file = mx_pasre_struct(files, file_name, dir_count,
			flags);
	
		while (i < size) {
			if (info_file[i].size < info_file[i + 1].size) {
				mx_swap(&files[i], &files[i + 1]);
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
}
