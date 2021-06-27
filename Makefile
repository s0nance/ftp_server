##
## EPITECH PROJECT, 2021
## B-NWP-400-NCE-4-1-myftp-marius.contoli-legay
## File description:
## Makefile
##

NAME        =       myftp

SRC         =       src/main.c\
					src/program.c\
					src/parser.c\
					src/program_start.c\
					src/program_error.c\
					src/program_data.c\
					src/parse_arguments.c\
					src/parse_flag.c\
					src/server_start.c\
					src/commands.c\
					src/login_commands.c\
					src/quit_help_commands.c\
					src/dele_command.c\
					src/noop_command.c\
					src/directory_commands.c\
					src/init_client.c\
					src/kill_client.c\
					src/pasv_command.c\
					src/list_command.c\
					src/retr_command.c\

OBJ         =       $(SRC:.c=.o)

CFLAGS    	=      -g -g3 -Wall -Wextra -Wimplicit-fallthrough=0 -fPIC -I./include

all         :       $(NAME)

$(NAME)     :       $(OBJ)
					gcc -o $(NAME) $(OBJ) -I./include

clean       :
					rm -rf $(OBJ)

fclean      :       clean
					rm -f $(NAME)

re          :       fclean all

launch      :       re clean
					./$(NAME)

vg          :       re clean
					valgrind ./$(NAME)