/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:35:24 by lalwafi           #+#    #+#             */
/*   Updated: 2024/12/02 17:42:13 by lalwafi          ###   ########.fr       */
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
	char	*input;
	char	**pipe_split;
	char	**cmd_argv;
	int     fd;
	int		exit_code;
	int		num_of_cmds;
	pid_t   child;
	pid_t   lastpid;
	char    *str;
	t_environment   *environment;
	t_command	*command;
	
} t_shell;

typedef struct s_environment
{
	int			exit;
	int			shlvl;
	char		*cwd;
	char		*owd;
	char		**path;
	char		**environ;
	t_values	*vals;
	t_shell		*shell;
}	t_environment;

typedef struct s_values
{
	char		*key;
	char		*value;
	char		*envstr;
	t_values	*next;
} t_values;


typedef struct s_command
{
	char				**cmd_args; // the command, flag and command line
	char				*cmd_line_L; // just a temp that i will be using for parsing, you can use it if you want
	int					no_args;
	int					no_redirs;
	int					int_temp; // just like the char temp
	int					redir_amount; // the amount of redirects there are in this command
	t_direct			*redir; // redirects
} t_command;

typedef struct s_direct
{
	char				*file; // file name
	t_state				*direct; // what do to with the files
}	t_direct;

typedef enum e_mini_state
{
	RE_INPUT, // <
	RE_OUTPUT, // >
	HERE_DOC, // <<
	APPEND // >>
}	t_state;

typedef struct s_bulid
{
	t_list *env_p;
}t_bulid;

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