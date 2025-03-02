NAME    = minishell
CC      = cc

#CFLAGS  = -Wall -Werror -Wextra -g3  -I /Users/$(USER)/.brew/opt/readline/include -fsanitize=address
CFLAGS  = -Wall -Werror -Wextra 
CFLAGS	+= -I/opt/vagrant/embedded/include/readline -I/opt/vagrant/embedded/include
CFLAGS	+= -I.
CFLAGS	+= -g3
CFLAGS	+= -fsanitize=address
# CFLAGS  += -L/opt/vagrant/embedded/lib/ -lreadline -I/opt/vagrant/embedded/include/readline -I/opt/vagrant/embedded/include

SRCS    =  $(addprefix parsing/, main.c parsing_2.c syntax_stuff.c free_all.c \
			variable_stuff_v2.c tokenize.c operators.c) \
			$(addprefix parsing/utils/, ft_strdup.c remove_quotes.c ft_strtrim_free.c ft_substr_free.c \
			ft_strjoin_free.c \
			ft_strncmp.c list_stuff_values.c list_stuff_cmds.c list_stuff_redir.c split_pipes.c) \
			start_exec.c \
			execution/new/execution.c\
			$(addprefix execution/utils/, utils.c env_utils.c) \
			$(addprefix execution/, exec_bulidin.c final_exec.c) \
			$(addprefix execution/bulid_in/, cd.c   echo.c env.c  exit.c  export.c  pwd.c  unset.c)\

OBJ     = $(SRCS:.c=.o)

LIBFT   = aish_libft/libft.a


READLINE	=	-L/opt/vagrant/embedded/lib/ -lreadline 

CFLAGS		=
# CFLAGS		=	-Wall -Wextra -Werror
CFLAGS		+=	-Ilibft -I./ -I/opt/vagrant/embedded/include/readline -I/opt/vagrant/embedded/include
CFLAGS		+=	-g3 
NAME		=	minishell

all			:	${NAME}

%.o			:	%.c
		cc ${CFLAGS} -c $< -o $@

${LIBFT}	:
		make -C aish_libft

${NAME}		:	${LIBFT} ${OBJ}
		cc ${CFLAGS} ${OBJ} ${READLINE} ${LIBFT} -o ${NAME}

clean		:
		make -C aish_libft clean
		rm -f ${OBJ}

fclean		:	clean
		rm -f ${LIBFT}
		rm -f ${NAME}

re			: fclean all

.PHONY		:	all clean fclean re

# %.o : %.c
# 	$(CC) -c $(CFLAGS) $< -o $@

# all: $(NAME)

# $(LIBFT):
# 	make -C aish_libft

# $(NAME): $(OBJ) $(LIBFT)
# 	$(CC) $(CFLAGS) -L/opt/vagrant/embedded/lib/ -lreadline $(OBJ) -o $@ $(LIBFT)

# clean: 
# 	rm -f $(OBJ)
# 	make -C aish_libft clean

# fclean: clean
# 	rm -f $(NAME)
# 	make -C aish_libft fclean

# re: fclean all

# .PHONY : all clean fclean re