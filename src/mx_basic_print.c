#include "uls.h"

int mx_count_max_len(char **files_in_dir) {
	int max = 0;
	
	if (*files_in_dir != NULL || files_in_dir != NULL) {		
		max = mx_strlen(files_in_dir[0]);
		for (int i = 1; files_in_dir[i]; i++) {
			if (max < mx_strlen(files_in_dir[i]))
				max = mx_strlen(files_in_dir[i]);
		}
	}
	return max;
}

int mx_num_of_cols(char **files_in_dir, int count) {
	struct winsize w;
	int max_len = mx_count_max_len(files_in_dir);
	int cols = 0;
	int lines = 0;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	cols = (w.ws_col / ((8 - (max_len % 8)) + max_len));
	lines = count / cols; //количество елементов вывода
	if (lines == 0 || ((count % cols) != 0))
		lines++;
	return lines;
}

void mx_choose_print_action(char *files_in_dir) {
	// *files_in_dir = *files_in_dir;
	// printf("la\n");
	mx_printstr(files_in_dir);

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

void mx_basic_print(char **files_in_dir, int count, int max_len) {
	int j;
	int sub_r;
	int num_of_lines = mx_num_of_cols(files_in_dir, count);

	for (int i = 0; i < num_of_lines; i++) {
		j = 0;
		sub_r = 0;
		for (int j = 0; files_in_dir[j]; j++) {
			if ((j + num_of_lines - i) % num_of_lines == 0) {
				mx_choose_print_action(files_in_dir[j]);
				if (sub_r + num_of_lines < count)
					basic_tab_print(mx_strlen(files_in_dir[j]), max_len);
			}
			++sub_r;
		}
		mx_printchar('\n');
	}
}
