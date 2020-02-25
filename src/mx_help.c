#include "uls.h"

char **mx_make_path(char **dirs_in, char *dir_name, int dir_count,
	t_flag *flags) {
	if (flags->flag_a)
		dir_count -= 2;
	char **path = (char **)malloc(sizeof(char *) * (dir_count + 1));
	char *tmp = NULL;
	int j = 0;

	for (int i = 0; dirs_in[i]; i++)
		if (mx_strcmp(dirs_in[i], ".") != 0
			&& mx_strcmp(dirs_in[i], "..") != 0) {
			if (mx_strcmp(dir_name, "/") == 0)
        		tmp = mx_strdup(dir_name);
    		else
        		tmp = mx_strjoin(dir_name, "/");
			path[j] = mx_strjoin(tmp, dirs_in[i]);
			j++;
			if (tmp != NULL)
				free(tmp);
		}
	path[dir_count] = NULL;
	return path;
}

char **mx_make_mas_of_dirs(int dir_count, char **files_in_dir, int count,
	t_flag *flags) {
	struct stat buf;
	int k = 0;

	if (*files_in_dir != NULL) {
		char **dirs = (char **)malloc(sizeof(char *) * (dir_count + 1));
		for (int j = 0; j < count; j++) {
			if (mx_link_check(files_in_dir[j], flags, &buf) >= 0) {
					if (((buf.st_mode & S_IFDIR) == S_IFDIR)) 
						dirs[k++] = mx_strdup(files_in_dir[j]);
				}
			}
		dirs[dir_count] = NULL;
		return dirs;
	}
	return NULL;
}

void mx_spacing_print(int sp) {
    char c = ' ';

    while (sp > 0) {
        write(1, &c, 1);
        sp--;
    }
}

void mx_colour_out(char *file, char *file_name) {
    char c = mx_file_mode_check(file, file_name);
    int size = mx_strlen(file);

    write(1, "\33[0m", mx_strlen("\33[0m"));
    mx_color_mode_one(c);
    mx_color_mode_two(c);
    write (1, file, size);
    write(1, "\33[0m", mx_strlen("\33[0m"));
}

int mx_get_ws() {
	struct winsize ws;
	int fd;
	int cols = 0;

	fd = open("/dev/tty", O_RDWR);
	if (fd < 0)
		err(1, "/dev/tty");
	if (ioctl(fd, TIOCGWINSZ, &ws) < 0)
		err(1, "/dev/tty");
	close(fd);
	cols = ws.ws_col;
	return cols;
}
