#include "uls.h"

// int mx_num_of_cols(t_info *info) {
// 	struct winsize w;
// 	int max_len = 0;
// 	int cols = 0;
// 	int lines = 0;

// 	for (t_uni_list *tmp = info->sub_args; tmp; tmp = tmp->next)
// 		if (max_len < mx_strlen(tmp->data))
// 			max_len = mx_strlen(tmp->data);
// 	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
// 	cols = (w.ws_col / ((8 - (max_len % 8)) + max_len));
// 	lines = info->num_of_sub / cols; //количество елементов вывода
// 	if (lines == 0 || ((info->num_of_sub % cols) != 0))
// 		lines++;
// 	info->max_sub_len = max_len;
// 	return lines;
// }


// int mx_count_elem_in_dir(char *av) {
// 	DIR *dir = opendir(av);
// 	struct dirent *entry;
// 	int count_elem = 0;

// 	while ((entry = readdir(dir)) != NULL)
// 		if (entry->d_name[0] != '.')
// 			count_elem++;
// 	return count_elem;
// }

// int mx_count_max_len(t_folder *folder, int ac) {
// 	int max = 0;
// 	DIR *dir = opendir(av);
// 	struct dirent *entry;

// 	while ((entry = readdir(dir))->next != NULL) {
// 		if (mx_strlen(entry->d_name) < mx_strlen(entry->next)) 
// 			mx_printstr(entry->d_name);
// 		}
// 	return max;
// }

// // bool mx_file_exist(int ac, char **av) {
// // 	if (ac != 1) {
// // 		if
// // 	}
// // }

// // bool mx_folder_exist(int ac, char **av) {

// // }

// // bool mx_flag_exist(int ac, char **av) {

// // }



// void mx_get_info(int ac, char **av, t_all_info *info, t_folder *folder) {
// 	info->ac = ac;
// 	info->av = av;

// 	for (int i = 0; i < ac - 1; i++) {
// 		folder[i].name = av[i + 1];
// 		folder[i].num_of_sub = mx_count_elem_in_dir(av[i + 1]);

// 	}
// }

// int main(int ac, char const **av) {
// 	// DIR *dir;
// 	// struct dirent *entry;
// 	// t_all_info *info = (t_all_info *)malloc(sizeof(t_all_info));
// 	// t_folder *folder = (t_folder *)malloc(sizeof(t_folder) * (ac - 1));

// 	// if (ac == 1) {
		
// 	// 	// dir = opendir(".");
// 	// 	// if (!dir) {
// 	// 	// 	perror("diropen");
// 	// 	// 	exit(1);
// 	// 	// }
// 	// 	// while ((entry = readdir(dir)) != NULL) {
// 	// 	// 	if (entry->d_name[0] != '.')
// 	// 	// 		mx_printstr(entry->d_name);
// 	// 	// }
// 	// }
// 	// else {
// 	// 	for (int i = 1; i < ac; i++) {
// 	// 		dir = opendir(av[i]);
// 	// 		if (!dir) {
// 	// 			perror("diropen");
// 	// 			exit(1);
// 	// 		}
// 	// 		mx_printstr(av[i]);
// 	// 		mx_printstr(": \n");
// 	// 		while ((entry = readdir(dir)) != NULL) {
// 	// 			if (entry->d_name[0] != '.') 
// 	// 				mx_printstr(entry->d_name);
// 	// 		}
// 	// 		mx_printchar('\n');
// 	// 		if (i != ac - 1) {
// 	// 			mx_printchar('\n');
// 	// 		}
// 	// 	}
// 	// }
// 	return 0;
// }

char **mx_valid_flag(int ac, char **av, t_flag *flags) {
	char flag[] = "Aal";
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
					else if (av[i][j] == flag[2])
						flags->flag_l = true;
					else {
						mx_printerr("uls: illegal option -- ");
						mx_printerr(&av[i][j]);
						mx_printerr("\nusage: ls [-Aal] [file ...]");
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
	printf("COUNT FILES = %d\n", count_files);

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

int mx_num_of_cols(char **files_in_dir, int count) {
	struct winsize w;
	int max_len = mx_count_max_len(char **files_in_dir);
	int cols = 0;
	int lines = 0;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	cols = (w.ws_col / ((8 - (max_len % 8)) + max_len));
	lines = count / cols; //количество елементов вывода
	if (lines == 0 || ((count % cols) != 0))
		lines++;
	return lines;
}



int mx_count_max_len(char **files_in_dir) {
	int max = mx_strlen(files_in_dir[0]);

	for (int i = 0; files_in_dir[i + 1]; i++) {
		if (mx_strlen(files_in_dir[i]) < mx_strlen(files_in_dir[i + 1]))
			max = mx_strlen(files_in_dir[i + 1]);
	}
	return max;
}

void mx_current_directory(t_flag *flags, char *dir_name) {
	DIR *dir = opendir(dir_name);
	struct dirent *entry;
	char **files_in_dir;
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

	int i = 0;
	dir = opendir(dir_name);
	files_in_dir = (char **)malloc(sizeof(char *) * (count + 1));

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

	for (int j = 0; files_in_dir[j]; j++) {
		printf("FILES IN DIR = %s\n", files_in_dir[j]);
	}
	printf("MAX LEN IN DIR = %d\n", mx_count_max_len(files_in_dir));
}

int main(int ac, char **av)
{
	t_flag *flags = (t_flag *)malloc(sizeof(t_flag));
	char **file = NULL;
	mx_memset(flags, 0, sizeof(t_flag));
	file = mx_valid_flag(ac, av, flags);
	for (int i = 0; file[i]; i++)
		printf("FILE = %s ", file[i]);
	printf("\n");
	if (file[0] == NULL) {
		mx_current_directory(flags, ".");
	}
	// else {

	// }
	return 0;
}
