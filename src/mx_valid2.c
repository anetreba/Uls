#include "uls.h"

void mx_print_error_flag(char av) {
	char *error = mx_strnew(1);
	error[0] = av;
	mx_printerr("uls: illegal option -- ");
	mx_printerr(error);
	mx_printerr("\nusage: uls [-ACRFGSTUacfhlmprtu1] [file ...]\n");
	exit(1);
}

void mx_struct_flag1(char *av, t_flag *flags, char *flag, bool *fl) {
	for (int j = 1; av[j]; j++) {
	 	if (av[j] == flag[0]) {
	 		*fl = true;
		 	flags->flag_A = true;
	 	}
		else if (av[j] == flag[1]) {
			*fl = true;
			flags->flag_a = true;
		}
	}
}

void mx_valid_print(t_flag *flags) {
	if (flags->flag_l)
		flags->flag_l = false;
	if (flags->flag_C)
		flags->flag_C = false;
	if (flags->flag_1)
		flags->flag_1 = false;
}

void mx_struct_flag2(char *av, t_flag *flags, char *flag, bool *fl) {
	for (int j = 1; av[j]; j++) {
		if (av[j] == flag[3]) {
			*fl = true;
			mx_valid_print(flags);
			flags->flag_l = true;
		}
		else if (av[j] == flag[17]) {
			*fl = true;
			mx_valid_print(flags);
			flags->flag_C = true;
		}
		else if (av[j] == flag[6]) {
			*fl = true;
			mx_valid_print(flags);
			flags->flag_1 = true;
		}
	}
}

void mx_valid_sort(t_flag *flags) {
	if (flags->flag_c)
		flags->flag_c = false;
	if (flags->flag_u)
		flags->flag_u = false;
} 
