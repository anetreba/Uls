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

static char dir_check(struct stat buf) {
    char c = '-';

    if ((buf.st_mode & S_IFMT) == S_IFDIR)
    {
        c = 'd';
        if ((buf.st_mode & S_ISVTX) == S_ISVTX
            && (buf.st_mode & S_IWOTH) == S_IWOTH)
        {
            c = 'x';
        }
        else if ((buf.st_mode & S_IWOTH) == S_IWOTH)
            c = 'n';
    }
    return c;
}

static char second_mode_unit(struct stat buf) {
    char c = '-';

    switch (buf.st_mode & S_IFMT)
    {
        case (S_IFBLK):
            c = 'b';
            break;
        case (S_IFCHR):
            c = 'c';
            break;
        case (S_IFIFO):
            c = 'p';
            break;
    }
    if (c == '-')
        c = dir_check(buf);
    return c;
}

static char file_check(struct stat buf) {
    char c = '-';

    if ((buf.st_mode & S_IFMT) == S_IFREG)
    {
        c = 'f';
        if ((buf.st_mode & S_IXUSR) == S_IXUSR) {
            c = 'e';
            if ((buf.st_mode & S_ISUID) == S_ISUID)
                c = 'u';
            else if ((buf.st_mode & S_ISGID) == S_ISGID)
                c = 'g';
        }
    }
    return c;
}

static char one_mode_unit(struct stat buf) {
    char c = '-';

    switch (buf.st_mode & S_IFMT)
    {
        case (S_IFSOCK):
            c = 's';
            break;
        case (S_IFLNK):
            c = 'l';
            break;
    }
    if (c == '-')
        c = file_check(buf);
    return c;
}

char mx_file_mode_check(char *file, char *file_name) {
    char c;
    char *filepath = mx_find_path(file, file_name);
    struct stat buf;

    lstat(filepath, &buf);
    c = one_mode_unit(buf);
    if (c == '-')
        c = second_mode_unit(buf);
    if (file_name != NULL)
        mx_strdel(&filepath);
    return c;
}

static void color_mode_two(char c) {
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

static void color_mode_one(char c) {
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

void mx_colour_out(char *file, char *file_name) {
    char c = mx_file_mode_check(file, file_name);
//for (int i = 0; files_in_dir[i]; i++)
    int size = mx_strlen(file);

    write(1, "\33[0m", mx_strlen("\33[0m"));
    color_mode_one(c);
    color_mode_two(c);
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


static int get_rows(int count, int max_len) {
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

static void spacing_print(int sp) {
    char c = ' ';

    while (sp > 0) {
        write(1, &c, 1);
        sp--;
    }
}

static void flag_F(char *obj, char *file_name) {
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

void mx_flag_p(char *obj, t_flag *flags, char *file_name) {
    char c;

    if (flags->flag_F)
        flag_F(obj, file_name);
    else {
        c = mx_file_mode_check(obj, file_name);
        if (c == 'd')
            write(1, "/", 1);
    }
}

void mx_flag_G(char **files_in_dir, int count, char *file_name, t_flag *flags) {
    int m_l = mx_count_max_len(files_in_dir);
    int rows = get_rows(count, m_l);
    int spacing = 0;

    for (int j = 0; j < rows; j++) {
        for (int i = j; i < count; i += rows) {
            if (!files_in_dir[i])
                break;
            spacing = m_l - mx_strlen(files_in_dir[i]) + 1;
            if ((i + rows) >= count)
                spacing = 0;
            mx_colour_out(files_in_dir[i], file_name);
            if (flags->flag_p || flags->flag_F)
                mx_flag_p(files_in_dir[i], flags, file_name);
            spacing_print(spacing);
        }
        write(1, "\n", 1);
	}
}
