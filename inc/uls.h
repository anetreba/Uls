#ifndef ULS_H
#define ULS_H

#include "libmx/inc/libmx.h"

#include <errno.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/acl.h>
#include <sys/types.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <wchar.h>
#include <pwd.h>
#include <grp.h>


typedef struct s_flag {
	bool flag_l;
	bool flag_a;
	bool flag_A;	
}				t_flag;

// typedef struct s_all_info {
// 	int ac;
// 	char **av;

// 	bool flags_exist;
// 	bool file_exist;
// 	bool folder_exist;

// }				t_all_info;

// typedef struct s_in_folder{
	
// }				t_in_folder;

// typedef struct s_folder {
// 	char *name;
// 	int num_of_sub;
// 	int max_sub_len;
	
// }				t_folder;




#endif
