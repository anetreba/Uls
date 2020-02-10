#include "uls.h"

void mx_flag_m(char **files_in_dir, int count) {
	for (int i = 0; files_in_dir[i]; i++) {
		mx_printstr(files_in_dir[i]);
		if (i != count - 1) {
			mx_printstr(", ");
		}
	}
}
