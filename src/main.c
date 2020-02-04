#include "uls.h"


char **mx_valid_flag(int ac, char **av, t_flag *flags) {
	char flag[] = "AaRl";
	bool flag_priority = true;
	int count_files = 0;
	char **file = NULL;
	int g = 0;

	for(int i = 1; i < ac; i++) {
		if (flag_priority == true) {
			if (av[i][0] == '-' && av[i][1] != '-') {
				for (int j = 1; av[i][j] ; j++) {
					if (av[i][j] == flag[0])
						flags->flag_A = true;
					else if (av[i][j] == flag[1])
						flags->flag_a = true;
					else if (av[i][j] == flag[3])
						flags->flag_l = true;
					else if (av[i][j] == flag[2])
						flags->flag_R = true;
					else {
						mx_printerr("uls: illegal option -- ");
						char c = av[i][j];
						mx_printerr(&c);
						mx_printerr("\nusage: ls [-Aal] [file ...]\n");
						exit(1);
					}
				}
			}
			if (av[i][0] != '-') {
				flag_priority = false;
				count_files++;
			}
			if (av[i][0] == '-' && av[i][1] == '-')
				flag_priority = false;
		}
		else if (!flag_priority) {
			count_files++;
		}
	}

	flag_priority = true;
	file = (char **)malloc(sizeof(char *) * (count_files + 1));

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


int mx_count_max_len(char **files_in_dir) {
	int max = mx_strlen(files_in_dir[0]);

	for (int i = 1; files_in_dir[i]; i++) {
		if (max < mx_strlen(files_in_dir[i]))
			max = mx_strlen(files_in_dir[i]);
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

int mx_count_elem_in_dir(t_flag *flags, char *dir_name) {
	DIR *dir = opendir(dir_name);
	struct dirent *entry;
	int count = 0;

	while ((entry = readdir(dir)) != NULL) {
		if (flags->flag_a == true)
			count++;
		else if (flags->flag_A == true) {
			if (entry->d_name[1] != '.' && entry->d_name[1] != '\0')
				count++;
		}
		else if (entry->d_name[0] != '.')
			count++;
	}
	closedir(dir);
	return count;
}

// char *mx_substr(const char *src, int a, int b) {
//   	int len = b - a;
//   	char *dst = (char *)malloc(sizeof(char) * (len + 1));
  	
//   	for (int i = a; i < b && src[i] != '\0'; i++) {
//   	  	*dst = src[i];
//   	  	dst++;
//   	}
//   	*dst = '\0';
//   	return dst - len;
// }

// void *mx_name_of_dir(char *s, int c) {
// 	unsigned char *ptr = (unsigned char *)s + mx_strlen(s);

// 	while (ptr) {
// 		if (*ptr == (unsigned char)c)
// 			return ptr;
// 		ptr--;
// 	}
// 	return NULL;
// }


char **mx_make_mas_of_elem_in_dir(t_flag *flags, char *dir_name, int count) {
	DIR *dir = opendir(dir_name);
	struct dirent *entry;
	char **files_in_dir = (char **)malloc(sizeof(char *) * (count + 1));
	int i = 0;
	
	// if (dir = NULL) {

	//  	perror(заспилтованная папочка) //ошибка Permission denied
	// }
	while ((entry = readdir(dir)) != NULL) {
		if (flags->flag_a == true)
			files_in_dir[i++] = mx_strdup(entry->d_name);
		else if (flags->flag_A == true) {
			if (entry->d_name[1] != '.' && entry->d_name[1] != '\0')
				files_in_dir[i++] = mx_strdup(entry->d_name);
		}
		else if (entry->d_name[0] != '.')
			files_in_dir[i++] = mx_strdup(entry->d_name);
	}
	files_in_dir[i] = NULL;
	closedir(dir);
	return files_in_dir;
}


void mx_current_directory(t_flag *flags, char *dir_name) {
	int count = mx_count_elem_in_dir(flags, dir_name);
	char **files_in_dir = mx_make_mas_of_elem_in_dir(flags, dir_name, count);


	
	mx_bubble_sort(files_in_dir, count);


	int max_len = mx_count_max_len(files_in_dir);
	mx_basic_print(files_in_dir, count, max_len);
}


// void mx_call_recursion(char **dirs, int dir_count, t_flag *flags) {
// 	if (flags->flag_R == true)  {
// 		mx_recusion_flag(dirs, dir_count, flags);
// 	}
// }


void mx_files_and_dir(char **file, t_flag *flags, int ac) {
	struct stat buf;
	int dir_count = 0;
	int file_count = 0;

	for (int i = 0; file[i]; i++) {
		if (lstat(file[i], &buf) >= 0) {
			if ((buf.st_mode & S_IFDIR) != S_IFDIR)
                    file_count += 1;
            else if (((buf.st_mode & S_IFDIR) == S_IFDIR))
                    dir_count += 1;
		}
		else {
			mx_printerr("uls: ");
			mx_printerr(file[i]);
			mx_printerr(": No such file or directory\n");
		}
	}

	char **files = (char **)malloc(sizeof(char *) * (file_count + 1));
	char **dirs = (char **)malloc(sizeof(char *) * (dir_count + 1));
	int i = 0;
	int k = 0;

	for (int j = 0; file[j]; j++) {
		if (lstat(file[j], &buf) >= 0) {
			if ((buf.st_mode & S_IFDIR) != S_IFDIR)
				files[i++] = mx_strdup(file[j]);
			else if (((buf.st_mode & S_IFDIR) == S_IFDIR))
				dirs[k++] = mx_strdup(file[j]); 
		}
	}
	files[file_count] = NULL;
	dirs[dir_count] = NULL;

	if (file_count > 0) {
		mx_bubble_sort(files, file_count);
		int max_len = mx_count_max_len(files);
		mx_basic_print(files, file_count, max_len);
	}

	
	mx_bubble_sort(dirs, dir_count);
	
	if (flags->flag_R) {
		mx_recursion_flag(dirs, dir_count, flags);
	}
	
	else {
		if (file_count != 0)
			mx_printstr("\n");
		for (int j = 0; dirs[j]; j++) {
			if (ac != 2) {
				mx_printstr(dirs[j]);
				mx_printchar(':');
				mx_printstr("\n");
			}
			mx_current_directory(flags, dirs[j]);
			if (j != dir_count - 1)
				mx_printstr("\n");
		}
	}
}

int main(int ac, char **av)
{
	t_flag *flags = (t_flag *)malloc(sizeof(t_flag));
	char **file = NULL;
	mx_memset(flags, 0, sizeof(t_flag));
	file = mx_valid_flag(ac, av, flags); //files in argument
	if (file[0] == NULL) {
		mx_current_directory(flags, ".");
	}
	else {
		mx_files_and_dir(file, flags, ac);
	}
	return 0;
}
