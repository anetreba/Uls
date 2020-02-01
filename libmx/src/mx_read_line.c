#include "libmx.h"

int mx_read_line(char **lineptr, int buf_size, char delim, const int fd) {
	char *ptr = mx_strnew(0);
	char *buf = mx_strnew(buf_size);
	char *tmp;
	int r;

	if (fd > 0 && lineptr && buf_size > 0 && delim) {
		while ((r = read(fd, buf, buf_size)) > 0) {
			tmp = ptr;
			ptr = mx_strjoin(ptr, buf);
			free(tmp);
			if (mx_memchr(buf, delim, buf_size) != NULL)
				break ;
		}
		free(buf);
		if (r == 0) {
			free(ptr);
			return 0;
		}
		*lineptr = mx_strndup(ptr, mx_get_char_index(ptr, delim));
		free(ptr);
		return mx_strlen(*lineptr);
	}
	return -1;
}
