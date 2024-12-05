/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:37:42 by lalwafi           #+#    #+#             */
/*   Updated: 2024/12/05 02:37:51 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize_shell(t_shell *shell)
{
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

	temp = malloc(sizeof(t_values));
	temp->envstr = ft_strdup(envline);
	temp->key = ft_strdup(key);
	temp->value = getenv(temp->key);
	temp->next = NULL;
	ft_lstadd_back_values(&shell->environment->vals, temp);
}

// void	change_shlvl(t_shell *shell)
// {
		
// }

void	minishell(t_shell *shell)
{

	while (1)
	{
		shell->input_L = readline("minishell> ");
		if (!shell->input_L)	// ctrl-D
			break ;
		else if (shell->input_L[0] != '\0')
		{
			parse_it();
			// execution();
		}
		else if (shell->input_L[0] == '\0')
			write(1, "empty line\n", 5);
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
	ft_lstclear_values(&shell->environment->vals, free);
	if (shell->environment)
	{
		free(shell->environment->cwd);
		free(shell->environment->owd);
		// free(shell->environment->);
		free(shell->environment);
		// free(shell);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell shell;
	
	(void)av;
	if (ac != 1)
		return (printf("'./minishell' only, no arguments\n"));
	initialize_shell(&shell);
	// change_shlvl();
	get_env(&shell, env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	minishell(&shell);
	free_all(&shell);
}
