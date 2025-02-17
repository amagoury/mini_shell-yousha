/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:37:42 by lalwafi           #+#    #+#             */
/*   Updated: 2025/02/17 20:26:41 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize_shell(t_shell *shell)
{
	shell->commands = malloc(sizeof(t_command));
	if (!shell->commands)
		(printf("command malloc fail\n"), exit(EXIT_FAILURE));
	shell->pipe_split_L = NULL;
	shell->input_L = NULL;
	shell->commands->cmd_args = NULL;
	shell->commands->cmd_line_L = NULL;
	shell->commands->num_of_redir = -1;
	shell->commands->redir = NULL;
	shell->commands->next = NULL;
}

void	get_env(t_shell *shell, char **env)
{
	int	i;
	char	*key;

	i = -1;
	shell->environment = malloc(sizeof(t_environment));
	shell->environment->exit = 0;
	shell->environment->cwd = getcwd(NULL, 0);
	shell->environment->owd = getcwd(NULL, 0);
	shell->environment->path = NULL;
	shell->environment->vals = NULL;
	// change shlvl??
	while (env[++i])
	{
		key = key_time(env[i]);
		make_values_node(key, env[i], shell);
		free(key);
	}
}

char *key_time(char *env)
{
	int	i;
	char	*key;
	i = 0;
	while(env[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	i = -1;
	while(env[++i] != '=')
		key[i] = env[i];
	key[i] = '\0';
	return (key);
}

void	make_values_node(char *key, char *envline, t_shell *shell)
{
	t_values	*temp;

	(void)envline;
	temp = malloc(sizeof(t_values));
	// temp->envstr = ft_strdup(envline);
	temp->key = ft_strdup(key);
	temp->value = getenv(temp->key);
	temp->next = NULL;
	ft_lstadd_back_values(&shell->environment->vals, temp);
}

void	minishell(t_shell *shell)
{
	while (1)
	{
		shell->input_L = readline("minishell> ");
		if (shell->input_L && shell->input_L[0] != '\0')
			add_history(shell->input_L);
		if (!shell->input_L)	// ctrl-D
			break ;
		else if (shell->input_L[0] != '\0')
		{
			// parse_it(shell);
			shell->input_L = ft_strtrim(shell->input_L, " ");
			if (!shell->input_L || shell->input_L[0] == '\0')
				write(1, "only spaces\n", 12);
			else if (open_quote_or_no(shell->input_L) == 1)
				write(1, "open quotes :(\n", 15);
			else if (check_pipes(shell->input_L) == 1)
				write(2, "syntax error\n", 13);
			else
			{
				// shell->input_L = rmv_extra_spaces(shell->input_L);
				// if (shell->pipe_split_L)
				// 	free_array(shell->pipe_split_L);
				// shell->num_of_pipes = count_pipes(shell->input_L); // check if it counts inside quotes
				shell->pipe_split_L = split_pipes(shell->input_L, '|');
				if (!shell->pipe_split_L)
					printf("pipe oopsie\n");
				else
				{
					int i = -1;
					while (shell->pipe_split_L[++i] != NULL)
						printf("#%s#\n", shell->pipe_split_L[i]);
				}
			}
			// execution(shell); this is where you start execution aisha - lyall
		}
		else if (shell->input_L[0] == '\0')
			write(1, "empty line\n", 11);
		free(shell->input_L);
	}
}

void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		// rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	free_all(t_shell *shell)
{
	// int	i;
	// i = -1;
	ft_lstclear_values(shell->environment->vals);
	// free(shell->environment->vals);
	if (shell->environment)
	{
		free(shell->environment->cwd);
		free(shell->environment->owd);
		// free(shell->environment->);
		free(shell->environment);
	}
	if (shell->pipe_split_L)
	{
		// shell->num_of_pipes += 1;
		// while (--shell->num_of_pipes >= 0)
		// 	free(shell->pipe_split_L[shell->num_of_pipes]);
		// free(shell->pipe_split_L);
		free_array(shell->pipe_split_L);
	}
	free(shell->commands);
	// free(shell);
}

int	main(int ac, char **av, char **env)
{
	t_shell shell;
	
	(void)av;
	if (ac != 1)
		return (printf("'./minishell' only, no arguments\n"));
	ft_bzero(&shell, sizeof(t_shell));
	initialize_shell(&shell);
	// change_shlvl();
	get_env(&shell, env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	minishell(&shell);
	free_all(&shell);
}

// { }, { }, { }

//    echo    hello   " my   friend   "
// j = 28  i = 33