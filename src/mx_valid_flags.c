#include "uls.h"

void mx_struct_flag3(char *av, t_flag *flags, char *flag, bool *fl) {
	for (int j = 1; av[j]; j++) {
		if (av[j] == flag[5]) {
			flags->flag_S = true;
			*fl = true;
		}
		if (av[j] == flag[7]) {
			flags->flag_t = true;
			*fl = true;
		}
		if (av[j] == flag[8]) {
			mx_valid_sort(flags);
			flags->flag_u = true;
			*fl = true;
		}
		if (av[j] == flag[9]) {
			mx_valid_sort(flags);
			flags->flag_c = true;
			*fl = true;
		}
	}
}

void mx_struct_flag5(char *av, t_flag *flags, char *flag, bool *fl) {
	for (int j = 1; av[j]; j++) {
		if (av[j] == flag[13]) {
			flags->flag_F = true;
			*fl = true;
		}
		else if (av[j] == flag[14]) {
			flags->flag_T = true;
			*fl = true;
		}
		else if (av[j] == flag[15]){
			flags->flag_sobaka = true;
			*fl = true;
		}
		else if (av[j] == flag[16]) {
			flags->flag_f = true;
			*fl = true;
		}
	}
}

void mx_struct_flag(char *av, t_flag *flags, char *flag) {
	bool fl = false;

	for (int j = 1; av[j]; j++) {
		mx_struct_flag1(av, flags, flag, &fl);
		mx_struct_flag2(av, flags, flag, &fl);
		mx_struct_flag3(av, flags, flag, &fl);
		mx_struct_flag4(av, flags, flag, &fl);
		mx_struct_flag5(av, flags, flag, &fl);
		if (av[j] == flag[18])
			flags->flag_h = true;
		else if (av[j] == flag[19])
			flags->flag_U = true;
		else if (av[j] == flag[2])
			flags->flag_R = true;
		else if (!fl || mx_error_case(av[j], flag))
			mx_print_error_flag(av[j]);
	}
}

char **mx_create_file(char **av, int ac, int count_files, char **file) {
	bool flag_priority = true;
	file = (char **)malloc(sizeof(char *) * (count_files + 1));
	int g = 0;

	for(int i = 1; i < ac; i++) {
		if (flag_priority == true) {			
			if (av[i][0] != '-') {
				flag_priority = false;
				file[g++] = mx_strdup(av[i]);
			}
			if (av[i][0] == '-' && av[i][1] == '-')
				flag_priority = false;
		}
		else if (!flag_priority) {
			file[g++] = mx_strdup(av[i]);
			flag_priority = false;
		}
	}
	file[count_files] = NULL;
	return file;
}

char **mx_valid_flag(int ac, char **av, t_flag *flags) {
	char flag[] = "AaRlmS1tucrGpFT@fChU";
	bool flag_priority = true;
	int count_files = 0;
	char **file = NULL;

	for(int i = 1; i < ac; i++)
		if (flag_priority == true) {
			if (av[i][0] == '-' && av[i][1] != '-')
				mx_struct_flag(av[i], flags, flag);
			if (av[i][0] != '-') {
				flag_priority = false;
				count_files++;
			}
			if (av[i][0] == '-' && av[i][1] == '-')
				flag_priority = false;
		}
		else if (!flag_priority)
			count_files++;
	file = mx_create_file(av, ac, count_files, file);
	return file;
}
