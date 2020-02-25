#include "uls.h"

void mx_flag_p(char *obj, t_flag *flags, char *file_name) {
    char c;

    if (flags->flag_F)
        mx_flag_F(obj, file_name);
    else {
        c = mx_file_mode_check(obj, file_name);
        if (c == 'd')
            write(1, "/", 1);
    }
}

void mx_print_G(char *files_in_dir, t_flag *flags, char *file_name,
	int spacing) {
    mx_colour_out(files_in_dir, file_name);
    if (flags->flag_p || flags->flag_F)
        mx_flag_p(files_in_dir, flags, file_name);
    mx_spacing_print(spacing);
}

void mx_print_cat(char **files_in_dir, int count, t_flag *flags, char *dir_name) {
	for (int i = 0; i < count; i++) {
		mx_printstr(files_in_dir[i]);
		if (flags->flag_p || flags->flag_F) 
			mx_flag_p(files_in_dir[i], flags, dir_name);
		mx_printchar('\n');
	}
}

void mx_flag_m(char **files_in_dir, int count) {
	for (int i = 0; files_in_dir[i]; i++) {
		mx_printstr(files_in_dir[i]);
		if (i != count - 1) {
			mx_printstr(", ");
		}
	}
}


void mx_flag_1(char **files_in_dir, int count) {
	for (int i = 0; i < count; i++) {
		mx_printstr(files_in_dir[i]);
		mx_printchar('\n');
	}
}
