#include "uls.h"

void mx_flag_F(char *obj, char *file_name) {
    char c;

    c = mx_file_mode_check(obj, file_name);
    if (c == 'l')
        write(1, "@", 1);
    else if (c == 'e')
        write(1, "*", 1);
    else if (c == 'd')
        write(1, "/", 1);
    else if (c == 's')
        write(1, "=", 1);
    else if (c == 'p')
        write(1, "|", 1);
}

int mx_num_of_cols(char **files_in_dir, int count, t_flag *flags,
	char *dir_name) {
	struct winsize w;
	int max_len = mx_count_max_len(files_in_dir);
	int cols = 0;
	int lines = 0;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (isatty(1) == 0 && flags->flag_C) 
            w.ws_col = 79;
    if (isatty(1) != 0 || flags->flag_C) {
		cols = (w.ws_col / ((8 - (max_len % 8)) + max_len));
		if ((cols != 0))
			lines = count / cols;
		if ((lines == 0) || ((cols != 0) && ((count % cols) != 0)))
			lines++;
		return lines;
	}
	else if (isatty(1) == 0 && !(flags->flag_C)) {
		mx_print_cat(files_in_dir, count, flags, dir_name);
	}
	return -1;
}

void mx_choose_print_action(char *files_in_dir, t_flag *flags,
	char *dir_name) {
	mx_printstr(files_in_dir);
	if (flags->flag_F || flags->flag_p)
		mx_flag_p(files_in_dir, flags, dir_name);
}

void basic_tab_print(int arg_len, int max_len) {
	int max_tabs = max_len / 8 + 1;
	int tab_len = arg_len / 8;

	if (tab_len < max_tabs) {
		write(1, "\t", 1);
		tab_len++;
	}
	while (max_tabs > tab_len) {
		write(1, "\t", 1);
		tab_len++;
	}
}

void mx_basic_print(char **files_in_dir, int count, int max_len, t_flag *flags,
 char *dir_name) {
	int j;
	int sub_r;
	int num_of_lines = mx_num_of_cols(files_in_dir, count, flags, dir_name);

	if (num_of_lines != -1) {
		for (int i = 0; i < num_of_lines; i++) {
			j = 0;
			sub_r = 0;
			for (int j = 0; files_in_dir[j]; j++) {
				if ((j + num_of_lines - i) % num_of_lines == 0) {
					mx_choose_print_action(files_in_dir[j], flags, dir_name);
					if (sub_r + num_of_lines < count)
						basic_tab_print(mx_strlen(files_in_dir[j]), max_len);
				}
				++sub_r;
			}
			mx_printchar('\n');
		}
	}
}
