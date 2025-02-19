/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:35:24 by lalwafi           #+#    #+#             */
/*   Updated: 2025/02/20 01:02:48 by lalwafi          ###   ########.fr       */
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
#define BUFF_SIZE 1024 

typedef struct	s_environment	t_environment;
typedef struct	s_shell			t_shell;
typedef struct	s_values		t_values;
typedef struct	s_command		t_command;
typedef struct	s_direct		t_direct;
typedef enum	e_state			t_state;

typedef struct s_shell
{
	int				exit_code; // exit code i think im not sure
	char			*input_L; // the input line
	char			**pipe_split_L; // input split by pipes
	int				num_of_pipes;
	t_command		*commands;
	t_environment	*environment;
} t_shell;

typedef struct s_command
{
	char				**words_L; // words split
	char				*cmd; // the command
	t_list				**cmd_args; // double array of arguments for command;
	char				*cmd_line_L; // the pipe split line to parse
	int					num_of_redir; // number of redirects in the line
	t_direct			*redir; // redirects
	int					save_statues; // save the statues of the command
	t_command			*next;
} t_command;

typedef struct s_environment
{
	char				*cwd; // current working directory
	char				*owd; // old working directory
	char				**path; // $PATH variable split to double array, probably for execution
	t_values			*vals; // contains all the elements in env
	 t_command    *command;
}	t_environment;

typedef struct s_values
{
	char				*key; // before "=" (eg; USER)
	char				*value; // after "=" (eg; lalwafi)
	// char				*envstr; // the whole line (eg; USER = lalwafi) probably will delete
	t_values			*next;
} t_values;

typedef struct s_direct
{
	char				*file; // file name
	t_state				*direct; // what do to with the files
	t_direct			*next;
}	t_direct;

typedef struct s_token
{
    char *str;             // for normal text aisha
    char *blockers;       // the bolcks withe the text will stop aisha
	char *dupl_block;
	char *s_block;
   	int len;               //  text len aisha
    bool convert;          // if the text need to convert or not aisha
} t_token;

typedef enum e_state
{
	RE_INPUT, // <
	RE_OUTPUT, // >
	HERE_DOC, // <<
	APPEND // >>
}	t_state;

// ================================================================================== //

// functions lyall

void		initialize_shell(t_shell *shell);
void		get_env(t_shell *shell, char **env);
char		*key_time(char *env);
void		make_values_node(char *key, char *envline, t_shell *shell);
void		minishell(t_shell *shell);
char		**split_pipes(char const *s, char c);
char		**make_letters(char **result, char const *s, char c, int count);
int			make_words(char const *s, char c);
char		**one_word(char const *s, char **result);
char		**free_array(char **result);
int			skip_quotes(const char *str, int i);
char		*rmv_extra_spaces(char *str);
void		expand_vars(char *str, t_environment *env);
void		parse_it(t_shell *shell);
int			open_quote_or_no(char *str);
int			count_pipes(char *str);
int			check_pipes(char *input);
char		*rmv_invalid_vars(char *str, t_environment *env);
// char	*rmv_invalid_vars(char *str, char **keys);


char		*ft_remove_chunk(char *str, int start, int len);
// char		*ft_remove_chunk(char *str, size_t start, size_t len);

// utils lyall

char		*ft_strdup(const char *s1);
int			ft_strncmp_lyall(const char *s1, const char *s2, size_t n);
int			ft_lstsize_v(t_values *lst);
t_values	*ft_lstlast_values(t_values *lst);
void		ft_lstadd_back_values(t_values **lst, t_values *new);
void		ft_lstclear_values(t_values *lst);
void		ft_lstdelone_values(t_values *lst);

// ================================================================================== //

//aisha erros 

int print_error(t_shell *shell, const char *cmd, const char *msg, const char *arg);
// aisha utils
bool is_valid_env(const char *env_var);
int env_add(char *content, char ***env);
int is_in_env(char **export_env, char *content);
//aisha bulid_in
t_command *creat_command(char *cmd);
void add_command(t_command **command, t_command *new);
int my_cd(t_environment *env, char *path);
void my_unset(t_command **head, char *args);
void print_list(t_command *head) ;
t_command *create_node(char *cmd);
void add_node(t_command **head, char *cmd);
void my_echo(char **command,t_command *cmd);
void	ms_pwd(void);
char *getcopyenv(char *str, t_command **env);
void    exit_shell(t_command *command);
char  *add_quotes(char *value);
void	print_env(char  **env, bool export);
int env_add(char *value, char ***env);
bool ft_export(t_command *cmd,  char **export_env);
int     exec_bulidin(t_command *cmd);
bool  run_bulidin(t_environment *path);

#endif