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

OBJ = main.o \
	mx_recursion_flag.o \
	mx_basic_print.o \
	mx_valid_flags.o \
	mx_print_flag.o \
	mx_elem_in_dir.o \
	mx_sort_flags.o \
	mx_flag_G.o \


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
