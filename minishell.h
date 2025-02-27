/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:35:24 by lalwafi           #+#    #+#             */
/*   Updated: 2025/02/27 14:37:39 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "aish_libft/libft.h"

# include "readline/readline.h"
# include "readline/history.h"
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
typedef enum	e_state			t_state;
typedef struct	s_direct		t_direct;

typedef struct s_shell
{
	int				exit_code; // exit code i think im not sure
	char			*input_L; // the input line
	char			**pipe_split_L; // input split by pipes
	int				parse_fail_L; // 0 for pass, -1 for fail
	int				num_of_cmds;
	t_command		*commands;
	t_environment	*environment;
} t_shell;

typedef struct s_command
{
	// char				**words_L; // words split
	// char				*cmd; // the command (dont use anymore i will keep the command in cmd_args[0])
	char				**cmd_args; // double array of arguments in command line including cmd;
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
	 char 				**export_env;      // Environment variables for export
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

typedef enum e_state
{
	RE_INPUT, // <
	RE_OUTPUT, // >
	HERE_DOC, // <<
	APPEND // >>
}	t_state;

typedef struct s_direct
{
	char				*file; // file name
	t_state				direct; // what do to with the files
	t_direct			*next;
}	t_direct;

// typedef struct s_token
// {
//     char *str;             // for normal text aisha
//     char *blockers;       // the bolcks withe the text will stop aisha
// 	char *dupl_block;
// 	char *s_block;
//    	int len;               //  text len aisha
//     bool convert;          // if the text need to convert or not aisha
// } t_token;


// ================================================================================== //

// functions lyall

void		initialize_shell(t_shell *shell);
t_command	*initialize_commands(void);
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
// void		parse_it(t_shell *shell);
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
void		ft_lstdelone_values(t_values *prev, t_values *del, t_values *nxt);
int			ft_lstsize_cmds(t_command *lst);
t_command	*ft_lstlast_cmds(t_command *lst);
void		ft_lstadd_back_cmds(t_command **lst, t_command *new);
int			ft_lstsize_redir(t_direct *lst);
t_direct	*ft_lstlast_redir(t_direct *lst);
void		ft_lstadd_back_redir(t_direct **lst, t_direct *new);
char		*rmv_quotes(char *str);
int			count_rmv_quotes(char *str , int i, int len);
void		free_all(t_shell *shell);
void		free_cmds(t_shell	*shell);

// tokenize lyall

void    tokenize_it(t_shell *shell, char *str);
char	*expand_them_vars(char *str, t_environment *env, t_shell *shell);
char	*string_but_string(char *pushed, char *pusher, int start, int rmv);
char	*return_var(char *str, int start, int len, t_environment *env);
int		return_var_length_temp(char *str, int start, int len, t_environment *env);
void	operator_tokens(t_command *cmds , int i);
char	*copy_file(char *str, int i, t_command *cmds, int start);
t_state	operators_check(char *str, int i);
void	print_commands(t_command *cmds);
void	print_enum(t_state en);

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
int my_unset(t_values **head, char *args);
void print_list(t_command *head) ;
t_command *create_node(char *cmd);
void add_node(t_command **head, char *cmd);
int my_echo(char **command,t_command *cmd);
int 	ms_pwd(void);
char *getcopyenv(char *str, t_command **env);
void    exit_shell(t_command *command);
char  *add_quotes(char *value);
void	print_env(char  **env, bool export);
int env_add(char *value, char ***env);
bool ft_export(t_command *cmd,  char **export_env);
int     exec_bulidin(t_command *cmd,t_environment *env);
int ft_env(t_values *env);
bool  run_bulidin(t_command *cmd, t_environment *env);
bool  is_bulidin(t_command *is_cmd);
void final_exec(t_command *cmd,t_environment *path, int cmd_cnt);
int	ft_strcmp(char *s1, char *s2);


// void	start_execution(t_shell *shell); //start execution here





#endif