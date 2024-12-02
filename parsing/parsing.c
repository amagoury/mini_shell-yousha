/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:37:42 by lalwafi           #+#    #+#             */
/*   Updated: 2024/12/02 21:32:34 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell shell;
	
	(void)av;
	if (ac != 1)
		return (printf("'./minishell' only, no arguments\n"));
	init_all(&shell);
	// change_shlvl();
	get_env(&shell, env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	minishell(&shell);
	free_all(&shell);
}

void	init_all(t_shell *shell)
{
	
}

void	initialize_shell(t_shell *shell)
{
	shell->input = NULL;
	shell->fd = -1;
	shell->child = -1;
	shell->lastpid = -1;
	shell->str = NULL;
	shell->environment = NULL;
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
	shell->environment->environ = NULL;
	shell->environment->vals = NULL;
	// change shlvl
	shell->environment->shlvl = 1;
	while (env[++i])
	{
		key = key_time(env[i]);
		make_values_node(key, env[i], shell);
		free(key);
	}
}

// void	change_shlvl(t_shell *shell)
// {
		
// }

void	minishell(t_shell *shell)
{

	while (1)
	{
		shell->input = readline("minishell> ");
		if (!shell->input)					//why, ctrl d i think
			break ;
		else if (shell->input[0] != '\0')
		{
			printf("got the input = %s\n", shell->input);
			if (ft_strncmp_lyall(shell->input, "exit", 4) == 0)
				break ;
			if (ft_strncmp_lyall(shell->input, "env", 3) == 0)
			{
				while (shell->environment->vals->next)
				{
					ft_putstr_fd(shell->environment->vals->envstr, 1);
					write(1, "\n", 1);
					shell->environment->vals = shell->environment->vals->next;
				}
			}
			if (ft_strncmp("pwd", shell->input, 3) == 0)
				printf("\n%s\n", shell->environment->cwd);
		}
		else if (shell->input[0] == '\0')
			printf("???\n");
		// else
		// {
		// 	if (ft_strncmp("pwd", shell->input, 3) == 0)
		// 		printf("\n%s\n", shell->environment->cwd);
		// }
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
