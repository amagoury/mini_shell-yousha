NAME    = minishell
CC      = cc

#CFLAGS  = -Wall -Werror -Wextra -g3  -I /Users/$(USER)/.brew/opt/readline/include -fsanitize=address
CFLAGS  = -Wall -Werror -Wextra 
CFLAGS	+= -I/opt/vagrant/embedded/include/readline -I/opt/vagrant/embedded/include
CFLAGS  += -g3 -fsanitize=address
#CFLAGS  += -L/opt/vagrant/embedded/lib/ -lreadline -I/opt/vagrant/embedded/include/readline -I/opt/vagrant/embedded/include

#SRCS    =  $(addprefix parsing/, main.c) $(addprefix parsing/utils/, ft_strdup.c \
			ft_strncmp.c list_stuff.c) $(addprefix execution/bulid_in/,cd.c \ errors.c \utils.c)

#i saw ur srcs were different so i just made SRCS_L for what i use
SRCS_L    =  $(addprefix parsing/, main.c parsing_2.c syntax_stuff.c \
			variable_stuff_v2.c tokenize.c operators.c) \
			$(addprefix parsing/utils/, ft_strdup.c remove_quotes.c\
			ft_strncmp.c list_stuff_values.c list_stuff_cmds.c list_stuff_redir.c split_pipes.c) \
			start_exec.c \
			$(addprefix execution/utils/, utils.c env_utils.c) \
			$(addprefix execution/, exec_bulidin.c final_exec.c) \
			$(addprefix execution/bulid_in/, cd.c   echo.c env.c  exit.c  export.c  pwd.c  unset.c)\

OBJ     = $(SRCS_L:.c=.o)

LIBFT   = aish_libft/libft.a

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(NAME)

$(LIBFT):
	make -C aish_libft

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -L/opt/vagrant/embedded/lib/ -lreadline $(OBJ) -o $@ $(LIBFT)

clean: 
	rm -f $(OBJ)
	make -C aish_libft clean

fclean: clean
	rm -f $(NAME)
	make -C aish_libft fclean

re: fclean all

.PHONY : all clean fclean re