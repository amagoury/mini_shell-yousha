/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_v2.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:28:47 by lalwafi           #+#    #+#             */
/*   Updated: 2024/12/04 22:21:57 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_V2_H
# define HEADER_V2_H

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

typedef struct s_shell
{
	char			**pipe_split_L;
	t_command		*commands;
	t_environment	*environment;
} t_shell;

typedef struct s_command
{
	char				**cmd_args; // double array of commands why
	char				*cmd_line_L; // just a temp that i will be using for parsing, you can use it if you want
	int					num_of_redir;
	char				*var;
	t_direct			*redir; // redirects
	t_command			*next;
} t_command;

typedef struct s_environment
{
	int					exit; // exit code i think im not sure
	char				*cwd; // current working directory
	char				*owd; // old working directory
	char				**path; // $PATH variable split to double array, probably for execution
	t_values			*vals; // contains all the elements in env
}	t_environment;

typedef struct s_values
{
	char				*key; // before "=" (eg; USER)
	char				*value; // after "=" (eg; lalwafi)
	char				*envstr; // the whole line (eg; USER = lalwafi)
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

#endif

// echo hello world > meow.txt | ls -la | wc -l
// echo "hello" > out.txt | cat -e < in.txt >> out2.txt | grep hello >> final.txt
// echo hello | echo world
// bash ececutes from the end to the start (world hello)
// echo hello | meow world (nope)
// pipe changes fd from output to input
// echo hello | wc

// echo "hello \' world\'" \> out.txt | cat -e < in.txt >> out2.txt | grep hello >> final.txt