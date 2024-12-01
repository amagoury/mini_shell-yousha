/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:35:24 by lalwafi           #+#    #+#             */
/*   Updated: 2024/12/02 23:57:45 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "aish_libft/libft.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <string.h>
# include <dirent.h>
# include <sys/stat.h>
# include <errno.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

typedef struct s_environment	t_environment;
typedef struct s_shell			t_shell;
typedef struct s_values			t_values;
typedef struct s_command		t_command;
typedef struct s_direct			t_direct;
typedef enum e_mini_state		t_state;

typedef struct s_shell
{
	char				*input; // for parsing probably i will use
	char				**pipe_split_L; // array of command lines split into pipes
	int					num_of_cmds; // how many commands there are, also can be used to keep track of how many pipes there are by doing -1
	int					parsing_fail_L; // flag for parsing
	t_command			*commands; // list for commands/tree
	t_environment   	*environment; // contains the env
} t_shell;

typedef struct s_environment
{
	int					exit; // exit code i think im not sure
	char				*cwd; // current working directory
	char				*owd; // old working directory
	char				**path; // $PATH variable split to double array, probably for execution
	t_values			*vals; // contains all the elements in env
}	t_environment;

typedef struct s_command
{
	char				**cmd_args; // double array of commands split by words
	char				*cmd_line_L; // the command line not split by words
	int					num_of_redir; // how many redirects there are
	t_direct			*redir; // redirects
	t_command			*next;
} t_command;

typedef struct s_direct
{
	char				*file; // file name
	t_state				*direct; // what do to with the files
	t_direct			*next;
}	t_direct;

typedef enum e_mini_state
{
	RE_INPUT, // <
	RE_OUTPUT, // >
	HERE_DOC, // <<
	APPEND // >>d
}	t_state;

typedef struct s_values
{
	char		*key; // before "=" (eg; USER)
	char		*value; // after "=" (eg; lalwafi)
	char		*envstr; // the whole line (eg; USER = lalwafi)
	t_values	*next;
} t_values;

// functions lyall

void		initialize_shell(t_shell *shell);
void		get_env(t_shell *shell, char **env);
char		*key_time(char *env);
void		make_values_node(char *key, char *envline, t_shell *shell);
void		minishell(t_shell *shell);

// utils

char		*ft_strdup(const char *s1);
int			ft_strncmp_lyall(const char *s1, const char *s2, size_t n);
int			ft_lstsize_v(t_values *lst);
t_values	*ft_lstlast_values(t_values *lst);
void		ft_lstadd_back_values(t_values **lst, t_values *new);
void		ft_lstclear_values(t_values **lst, void (*del)(void *));
void		ft_lstdelone_values(t_values *lst, void (*del)(void *));

//aisha erros 
int print_error(t_shell *shell, const char *cmd, const char *msg, const char *arg);
//aisha
void    initialize_command(t_command *meow);
int ft_cd(t_shell *shell, int cmd_num);
#endif