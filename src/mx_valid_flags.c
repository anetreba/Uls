#include "uls.h"

void mx_struct_flag(char *av, t_flag *flags, char *flag) {
	for (int j = 1; av[j] ; j++) {
		if (av[j] == flag[0])
			flags->flag_A = true;
		else if (av[j] == flag[1])
			flags->flag_a = true;
		else if (av[j] == flag[3])
			flags->flag_l = true;
		else if (av[j] == flag[2])
			flags->flag_R = true;
		else if (av[j] == flag[4])
			flags->flag_m = true;
		else if (av[j] == flag[6])
			flags->flag_1 = true;
		else if (av[j] == flag[5])
			flags->flag_S = true;
		else if (av[j] == flag[7])
			flags->flag_t = true;
		else if (av[j] == flag[8])
			flags->flag_u = true;
		else if (av[j] == flag[9])
			flags->flag_c = true;
		else if (av[j] == flag[10])
			flags->flag_r = true;
		else if (av[j] == flag[11])
			flags->flag_G = true;
		else if (av[j] == flag[12])
			flags->flag_p = true;
		else if (av[j] == flag[13])
			flags->flag_F = true;
		else if (av[j] == flag[14])
			flags->flag_T = true;
		else if (av[j] == flag[15])
			flags->flag_sobaka = true;
		else if (av[j] == flag[16])
			flags->flag_f = true;
		else {
			mx_printerr("uls: illegal option -- ");
			char c = av[j];
			mx_printerr(&c);
			mx_printerr("\nusage: uls [-ARFGSTacflmprtu1] [file ...]\n");
			exit(1);
		}
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
				file[g] = mx_strdup(av[i]);
				g++;
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
	char flag[] = "AaRlmS1tucrGpFT@f";
	bool flag_priority = true;
	int count_files = 0;
	char **file = NULL;

	for(int i = 1; i < ac; i++) {
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
	}

	file = mx_create_file(av, ac, count_files, file);
	return file;
}
