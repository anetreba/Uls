#include "uls.h"

void mx_bzero(void *s, size_t size) {
  char *str = (char *)s;
  for (size_t i = 0; i < size; ++i)
    str[i] = '\0';
  str = NULL;
}

void mx_print_spaces(int n) {
    for (; n > 0; n--)
        mx_printchar(' ');
}

int mx_intlen(long long n) {
    int i = 1;

    for (; n > 9; i++)
        n /= 10;
    return i;
}



char *mx_mychmod(int mode, char *str, char *dir_mame) {
    acl_t acl = NULL;
    ssize_t xattr = 0;
    char buf[1024];

    mx_strcpy(str,"-----------");
    acl = acl_get_link_np(dir_mame, 256);
    xattr = listxattr(dir_mame, buf, 0, XATTR_NOFOLLOW);
    if (S_ISDIR(mode))str[0] = 'd';
    if (S_ISCHR(mode))str[0] = 'c';
    if (S_ISBLK(mode))str[0] = 'b';
    if (S_ISLNK(mode))str[0] =  'l';
    if (mode & S_IRUSR)str[1] = 'r';
    if (mode & S_IWUSR)str[2] = 'w';
    if (mode & S_IXUSR)str[3] = 'x';
    if (mode & S_IRGRP)str[4] = 'r';
    if (mode & S_IWGRP)str[5] = 'w';
    if (mode & S_IXGRP)str[6] = 'x';
    if (mode & S_IROTH)str[7] = 'r';
    if (mode & S_IWOTH)str[8] = 'w';
    if (mode & S_IXOTH)str[9] = 'x';
    if (xattr > 0)
        str[10] = '@';
    else
        str[10] = (acl != NULL) ? '+' : ' ';
    return str;
}


char* mx_substr(const char *src, int a, int b) {
    int len = b - a;
    char *dst = (char *)malloc(sizeof(char) * (len + 1));
    
    for (int i = a; i < b && src[i] != '\0'; i++) {
        *dst = src[i];
        dst++;
    }
    *dst = '\0';
    return dst - len;
}


static void mx_itoa_to_string(unsigned int number, int n);

void filling_struct(t_len_column *lens, struct stat buff) {
    struct passwd *userinfo = NULL;
    struct group *groupinfo;

    if (lens->len_link < mx_intlen(buff.st_nlink))
        lens->len_link = mx_intlen(buff.st_nlink);
    userinfo = getpwuid(buff.st_uid);
    if (lens->len_user < mx_strlen(userinfo->pw_name))
        lens->len_user = mx_strlen(userinfo->pw_name);
    groupinfo = getgrgid(buff.st_gid);
    if (groupinfo != NULL) {
        if (lens->len_gid < mx_strlen(groupinfo->gr_name))
            lens->len_gid = mx_strlen(groupinfo->gr_name);
        else if (lens->len_gid < mx_intlen(userinfo->pw_gid))
                lens->len_gid = mx_intlen(userinfo->pw_gid);
    }

    if (lens->len_size < mx_intlen(buff.st_size))
       lens->len_size = mx_intlen(buff.st_size);
}

void len_difference(t_diff_len *l, t_len_column *lens, struct stat buff) {   
    struct passwd *userinfo = NULL;
    struct group *groupinfo = NULL;
    
    l->diff_link = lens->len_link;
    l->diff_size = lens->len_size;
    l->diff_user = lens->len_user;
    l->diff_gid = lens->len_gid;
    if (lens->len_link >= mx_intlen(buff.st_nlink))
        l->diff_link -= mx_intlen(buff.st_nlink);
    if (lens->len_size >= mx_intlen(buff.st_size))
        l->diff_size -= mx_intlen(buff.st_size);
    userinfo = getpwuid(buff.st_uid);
    if (lens->len_user >= mx_strlen(userinfo->pw_name))
        l->diff_user -= mx_strlen(userinfo->pw_name);
    groupinfo = getgrgid(buff.st_gid);
    if (groupinfo != NULL) {
        if (lens->len_gid >= mx_strlen(groupinfo->gr_name))
            l->diff_gid -= mx_strlen(groupinfo->gr_name);
        else if (lens->len_gid >= mx_intlen(userinfo->pw_gid))
            l->diff_gid -= mx_intlen(userinfo->pw_gid);
    }
}

char **mx_find_path1(char **dirs_in, char *dir_name, int dir_count, t_flag *flags) {
    if (flags->flag_a)
        dir_count -= 2;
    if (mx_strcmp(dir_name, ".") == 0)
        return dirs_in;
    char **path = (char **)malloc(sizeof(char *) * (dir_count + 1));
    char *tmp = NULL;
    int j = 0;

    if (mx_strcmp(dir_name, "..") != 0) {
        for (int i = 0; dirs_in[i]; i++) {
            if (mx_strcmp(dirs_in[i], ".") != 0 && mx_strcmp(dirs_in[i], "..") != 0) {
                if (mx_strcmp(dir_name, "/") == 0)
                    tmp = mx_strdup(dir_name);
                else
                    tmp = mx_strjoin(dir_name, "/");
                path[j] = mx_strjoin(tmp, dirs_in[i]);
                j++;
                if (tmp != NULL)
                    free(tmp);
            }
        }
    }
    path[dir_count] = NULL;
    return path;
}

void total_blocks(char **files_in_dir, t_len_column *lens, char *dir_name, int count, t_flag *flags) {
    struct stat buff;
    long long total = 0;
    char **path = NULL;

    mx_memset(lens, 0, sizeof(t_len_column));
    path = mx_find_path1(files_in_dir, dir_name, count, flags);
    for (int i = 0; path[i]; i++) {
        if (dir_name != NULL) 
            lstat(path[i], &buff); 
        else
            lstat(files_in_dir[i], &buff);
        filling_struct(lens, buff);
       	total += buff.st_blocks;

    }
    mx_printstr("total ");
    mx_printint(total);
    mx_printchar('\n');
}

void my_getgrgid(char *filename, int n) {
    struct group *groupinfo;
    struct stat buff;

    lstat(filename, &buff);
    groupinfo = getgrgid(buff.st_gid);
    if (groupinfo != NULL) {
        mx_printstr(groupinfo->gr_name);
        mx_print_spaces(n);
        mx_print_spaces(1);
    }
    else
        mx_itoa_to_string(buff.st_gid, n);
}

void my_getuid(char *filename, int n) {
    struct passwd *userinfo = NULL;
    uid_t userid;
    struct stat buff;

    lstat(filename, &buff);
    userid = buff.st_uid;
    userinfo = getpwuid(userid);
    if (userinfo != NULL) {
        mx_printstr(userinfo->pw_name);
        mx_print_spaces(n);
        mx_print_spaces(2);
    }
}

static void mx_itoa_to_string(unsigned int number, int n) {
	char *str = mx_itoa(number);

    mx_print_spaces(n);
	mx_printstr(str);
	mx_print_spaces(1);
	free(str);
}

char *time_T(time_t time, t_flag *flags) { //                     функцию ниже добавишь
    char *str;
    //time_t sec = time(NULL);
    if (flags->flag_T)
        str = mx_substr(ctime(&(time)), 4, 24);
    else
       str = mx_substr(ctime(&(time)), 4, 16);
    return str;
}

void my_time(char *filename, t_flag *flags) {
    struct stat *file_info = malloc(sizeof(struct stat));
    char *sub;
    time_t sec = time(NULL);
    time_t time = 0;

    lstat(filename, file_info);
    if (flags->flag_u) 
        time = file_info->st_atime;
    else if (flags->flag_c)
        time = file_info->st_ctime;
    else 
        time = file_info->st_mtime;

    if ((sec - (time)) > 15552000 || sec < 0) {
        sub = mx_substr(ctime(&(file_info->st_mtime)), 4, 10);
    	mx_printstr(sub);
    	free(sub);
    	mx_print_spaces(2);
    	sub = mx_substr(ctime(&(time)), 20, 24);
    	mx_printstr(sub);
    	mx_print_spaces(1);
    	free(file_info);
    }
    else { 
    	sub = time_T(time, flags);//mx_substr(ctime(&(time)), 4, 16);//                                 <- time_T(time);
    	mx_printstr(sub);
    	mx_print_spaces(1);
    	free(file_info);
    }
    free(sub);
}

void my_readlink(char *str, char *filename) {
    char ayaya[1024];

    if (str[0] == 'l') {
        readlink(filename, ayaya, 1024);
        if (ayaya[0] != '\0') {
            mx_printstr(" -> ");            
            mx_printstr(ayaya);
        }
        mx_bzero(ayaya, sizeof(ayaya));
        ayaya[0] = '\0';
    }
}

void mx_flag_sobaka(char *str, char *filename, t_flag *flags) { // <<<<<подключишь флажок
    char pog_champ[1024];
    size_t size_xat = 0;
    if (str[10] == '@' && flags->flag_sobaka ) {
        if (listxattr(filename, pog_champ, 1024, 1) >= 0)
        size_xat = getxattr(filename, pog_champ, 0, 1024, 0, 1);
        mx_printchar('\n');
        mx_print_spaces(8);
        mx_printstr(pog_champ);
        mx_print_spaces(6);
        mx_printint(size_xat);
    }
}

// void flag_h(long long n, t_flag *flags) {   //                       не успел доделать
//     if (flags->flag_h) {
//         n /= 1024;
//         str = mx_itoa(n);
//     }
// }

void mx_flag_l(char **files_in_dir, int count, char *dir_name, t_flag *flags) {
    char pr_dost[12];
    struct stat buff;
    t_len_column *lens = (t_len_column *)malloc(sizeof(t_len_column));
    t_diff_len *l = (t_diff_len *)malloc(sizeof(t_diff_len));
    char **path = NULL;

    path = mx_find_path1(files_in_dir, dir_name, count, flags);
    total_blocks(files_in_dir, lens, dir_name, count, flags);
    for (int i = 0; path[i]; i++) {
        lstat(path[i], &buff);
        len_difference(l, lens, buff);
        mx_printstr(mx_mychmod(buff.st_mode, pr_dost, path[i]));
        mx_print_spaces(1);
        mx_itoa_to_string(buff.st_nlink, l->diff_link);
        my_getuid(path[i], l->diff_user);
        my_getgrgid(path[i], l->diff_gid);
        mx_itoa_to_string(buff.st_size, l->diff_size + 1);
        my_time(path[i], flags);
        mx_printstr(files_in_dir[i]);
        my_readlink(pr_dost, path[i]);
        mx_flag_sobaka(pr_dost, path[i], flags);
        mx_printchar('\n');
    }
    // system("leaks uls");
}
