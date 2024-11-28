/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 01:54:16 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/28 02:03:47 by lalwafi          ###   ########.fr       */
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

typedef struct s_shell
{
	char	*input;
	int     fd;
	pid_t   child;
	pid_t   lastpid;
	char    *str;
	t_environment   *environment;
	
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

// // functions lyall

// void		initialize_shell(t_shell *shell);
// void		get_env(t_shell *shell, char **env);
// char		*key_time(char *env);
// void		make_values_node(char *key, char *envline, t_shell *shell);
// void		minishell(t_shell *shell);

// // utils

// char		*ft_strdup(const char *s1);
// int			ft_strncmp_lyall(const char *s1, const char *s2, size_t n);
// int			ft_lstsize(t_values *lst);
// t_values	*ft_lstlast_values(t_values *lst);
// void		ft_lstadd_back_values(t_values **lst, t_values *new);
// void		ft_lstclear_values(t_values **lst, void (*del)(void *));
// void		ft_lstdelone_values(t_values *lst, void (*del)(void *));


#endif