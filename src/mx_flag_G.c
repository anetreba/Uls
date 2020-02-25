#include "uls.h"

char *mx_find_path(char *file, char *file_name) {
    char *filepath1 = NULL;
    char *filepath2 = NULL;

    if (file_name == NULL){
        return file;
    }
    filepath1 = mx_strjoin(file_name, "/");
    filepath2 = mx_strjoin(filepath1, file);
    mx_strdel(&filepath1);
    return filepath2;
}

void mx_color_mode_two(char c) {
	if (c == 'x')
		write(1, "\33[0;30;42m", mx_strlen("\33[0;30;42m"));
	else if (c == 'u')
		write(1, "\33[0;30;41m", mx_strlen("\33[0;30;41m"));
	else if (c == 's')
		 write(1, "\33[0;32m", mx_strlen("\33[0;32m"));
	else if (c == 'g')
		write(1, "\33[0;30;46m", mx_strlen("\33[0;30;46m"));
	else if (c == 'n')
		write(1, "\33[0;30;41m", mx_strlen("\33[0;30;41m"));
	else if (c == '-')
		write(1, "\33[0;34m", mx_strlen("\33[0;34m"));
}

void mx_color_mode_one(char c) {
	if (c == 'd')
		write(1, "\33[0;34m", mx_strlen("\33[0;34m"));
	else if (c == 'l')
		write(1, "\33[0;35m", mx_strlen("\33[0;35m"));
	else if (c == 'e')
		write(1, "\33[0;31m", mx_strlen("\33[0;31m"));
	else if (c == 'c')
		write(1, "\33[0;34;43m", mx_strlen("\33[0;34;43m"));
	else if (c == 'b')
		write(1, "\33[0;34;46m", mx_strlen("\33[0;34;46m"));
}

int get_rows(int count, int max_len) {
    int rows;
    int one_line = 0;
    int w_s = mx_get_ws();

    if (w_s <= (max_len + 1))
        return count;
    one_line = w_s / (max_len + 1);
    rows = count / one_line;
    if (count % one_line != 0)
        rows += 1;
    return rows;
}

void mx_flag_G(char **files_in_dir, int count, char *file_name,
    t_flag *flags) {
    int m_l = mx_count_max_len(files_in_dir, flags, file_name);
    int rows = get_rows(count, m_l);
    int spacing = 0;

    if (isatty(1) != 0) {
        for (int j = 0; j < rows; j++) {
            for (int i = j; i < count; i += rows) {
                if (!files_in_dir[i])
                    break;
                spacing = m_l - mx_strlen(files_in_dir[i]) + 1;
                if ((i + rows) >= count)
                    spacing = 0;
                mx_print_G(files_in_dir[i], flags, file_name, spacing);
            }
            write(1, "\n", 1);
    	}
    }
    else
        mx_print_cat(files_in_dir, count, flags, file_name);
}
