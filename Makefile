NAME = uls

INC = uls.h

SRC = main.c \
	mx_recursion_flag.c \
	mx_basic_print.c \
	mx_valid_flags.c \
	mx_print_flag.c \
	mx_elem_in_dir.c \
	mx_sort_flags.c \
	mx_flag_G.c \
	mx_flag_l.c \
	mx_make_files_dirs.c \
	mx_check_file.c \
	mx_help.c \
	mx_sort1.c \
	mx_valid2.c \
	mx_print_sizes.c \
	mx_intlen.c \
	mx_print_spaces.c \
	mx_mychmod.c \
	mx_len_difference.c \
	mx_find_path_l.c \
	mx_substr.c \
	mx_my_time.c \
	mx_my_getuid.c \
	mx_bzero.c \
	mx_my_getgrgid.c \
	mx_flag_sobaka.c \
	flag_h_check.c \

OBJ = main.o \
	mx_recursion_flag.o \
	mx_basic_print.o \
	mx_valid_flags.o \
	mx_print_flag.o \
	mx_elem_in_dir.o \
	mx_sort_flags.o \
	mx_flag_G.o \
	mx_flag_l.o \
	mx_make_files_dirs.o \
	mx_check_file.o \
	mx_help.o \
	mx_sort1.o \
	mx_valid2.o \
	mx_print_sizes.o \
	mx_intlen.o \
	mx_print_spaces.o \
	mx_mychmod.o \
	mx_len_difference.o \
	mx_find_path_l.o \
	mx_substr.o \
	mx_my_time.o \
	mx_my_getuid.o \
	mx_bzero.o \
	mx_my_getgrgid.o \
	mx_flag_sobaka.o \
	flag_h_check.o \


CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install clean

install:
	@make install -sC libmx
	@cp $(addprefix src/, $(SRC)) .
	@cp $(addprefix inc/, $(INC)) .
	@clang $(CFLAGS) -c $(SRC) -I $(INC)
	@clang $(CFLAGS) libmx/libmx.a $(OBJ) -o $(NAME)
	@mkdir -p obj
	@mv $(OBJ) ./obj

uninstall: clean
	@make uninstall -sC libmx
	@rm -rf $(NAME)

clean:
	@make clean -sC libmx
	@rm -rf $(INC) $(SRC) ./obj

reinstall: uninstall install
