NAME    = minishell
CC      = cc
CFLAGS  = -Wall -Werror -Wextra -g3  -I/Users/$(USER)/.brew/opt/readline/include -fsanitize=address

SRCS    =  $(addprefix parsing/, parsing.c parsing_2.c rdp.c) \
			$(addprefix parsing/utils/, ft_strdup.c \
			ft_strncmp.c list_stuff.c split_pipes.c) \
#			$(addprefix execution/bulid_in/,cd.c \ errors.c \utils.c) 
			
#I commented your files so i can test mine, you can just delete the '#'

OBJ     = $(SRCS:.c=.o)

LIBFT   = aish_libft/libft.a

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(NAME)

$(LIBFT):
	make -C aish_libft

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -L/Users/$(USER)/.brew/opt/readline/lib -o $@ $(LIBFT)

clean: 
	rm -f $(OBJ)
	make -C aish_libft clean

fclean: clean
	rm -f $(NAME)
	make -C aish_libft fclean

re: fclean all

.PHONY : all clean fclean re