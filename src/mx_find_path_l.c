#include "uls.h"

static void help_find_path(char **dirs_in, char *dir_name, char **path,
    char *tmp, int dir_count);

char **mx_find_path_l(char **dirs_in, char *dir_name, int dir_count) {
    if (dir_name == NULL)
        return dirs_in;
    char **path = (char **)malloc(sizeof(char *) * (dir_count + 1));
    char *tmp = NULL;

    help_find_path(dirs_in, dir_name, path, tmp, dir_count);
    return path;
}

static void help_find_path(char **dirs_in, char *dir_name, char **path, 
    char *tmp, int dir_count) {
    int j = 0;

    for (int i = 0; dirs_in[i]; i++) {
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
}
