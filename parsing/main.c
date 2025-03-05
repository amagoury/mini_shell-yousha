/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:37:42 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 02:48:55 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

void	minishell(t_shell *shell)
{
	int	i;

	while (1)
	{
		signal(SIGINT, handle_signal);
		shell->input_L = readline("meowshell> ");
		if (shell->input_L && shell->input_L[0] != '\0')
			add_history(shell->input_L);
		if (!shell->input_L)
			break ;
		else if (shell->input_L[0] != '\0')
		{
			shell->input_L = ft_strtrim_free(shell->input_L, " ");
			if (!shell->input_L || shell->input_L[0] == '\0')
				shell->parse_fail_L = 1;
			else if (open_quote_or_no(shell->input_L) == 1)
				shell->parse_fail_L = 1;
			else if (check_pipes(shell->input_L) == 1)
				shell->parse_fail_L = 1;
			else if (operator_valid(shell->input_L) == FALSE)
				shell->parse_fail_L = 1;
			else
			{
				if (g_sig != 0)
				{
					shell->exit_code = 1;
					g_sig = 0;
				}
				shell->input_L = ft_strtrim_free(expand_them_vars(\
					shell->input_L, shell->environment, shell), " ");
				shell->input_L = rmv_extra_spaces(shell->input_L);
				shell->num_of_cmds = count_pipes(shell->input_L) + 1;
				shell->pipe_split_L = split_pipes(shell->input_L, '|');
				if (!shell->pipe_split_L)
					(free_all(shell), \
					write(2, "\033[0;31mError: malloc fail\033[0m\n", 24), \
					exit(EXIT_FAILURE));
				i = 0;
				while (shell->pipe_split_L[i])
					tokenize_it(shell, shell->pipe_split_L[i++]);
			}
			if (shell->parse_fail_L != 0)
			{
				write(2, "Parse fail\n", 11);
				shell->exit_code = shell->parse_fail_L;
				shell->parse_fail_L = 0;
			}
			else
			{
				print_commands(shell->commands);
				execution(shell, shell->environment);
				if (shell->pipe_split_L)
					shell->pipe_split_L = free_array(shell->pipe_split_L);
				shell->environment->export_env = remake_env(shell->environment);
				shell->environment->path = remake_path(shell->environment);
			}
		}
		else if (shell->input_L[0] == '\0')
			write(2, "empty line\n", 11);
		free(shell->input_L);
		free_cmds(shell);
	}
}

void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		g_sig = SIGINT;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)av;
	if (ac != 1)
		return (printf("'./minishell' only, no arguments\n"));
	ft_bzero(&shell, sizeof(t_shell));
	initialize_shell(&shell);
	get_env(&shell, env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	minishell(&shell);
	write(1, "exit\n", 5);
	free_all(&shell);
}

// { }, { }, { }

//    echo    hello   " my   friend   "
// j = 28  i = 33

// \033[1;31m	               7 (Escape sequence for red)
// 	environment malloc fail	   24 (Plain text)
// 	\033[0m             	   4 (Reset color)
// 	\n	                       1 (Newline)