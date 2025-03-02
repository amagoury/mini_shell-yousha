/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:37:42 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/02 04:46:04 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize_shell(t_shell *shell)
{
	shell->pipe_split_L = NULL;
	shell->input_L = NULL;
	shell->exit_code = 0;
	shell->parse_fail_L = 0;
	// shell->commands = initialize_commands();
}

t_command	*initialize_commands(void)
{
	t_command	*cmd;
	cmd = ft_calloc(sizeof(t_command), 1);
	if (!cmd)
		(write(2, "\033[0;31mError: command malloc fail\033[0m\n", 36), exit(EXIT_FAILURE));
	cmd->cmd_args = NULL;
	cmd->cmd_line_L = NULL;
	cmd->num_of_redir = 0;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	get_env(t_shell *shell, char **env)
{
	int	i;
	int	j;
	char	*key;

	i = -1;
	shell->environment = malloc(sizeof(t_environment));
	if (!shell->environment)
		(write(2, "\033[0;31mError: environment malloc fail\033[0m\n", 36), exit(EXIT_FAILURE));
	// shell->environment->exit = 0;
	shell->environment->cwd = getcwd(NULL, 0);
	shell->environment->owd = getcwd(NULL, 0);
	shell->environment->path = NULL;
	shell->environment->vals = NULL;
	// change shlvl??
	while (env[++i])
	{
		// key = key_time(env[i]);
		key = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		// printf("key = #%s#\n", key);
		if (!key || key == NULL)
			continue;
		if (ft_strlen(key) == 4 && ft_strncmp_lyall(key, "PATH", 4) == 0)
			shell->environment->path = ft_split(getenv(key), ':');
		make_values_node(key, env[i], shell);
		free(key);
	}
	shell->environment->export_env = malloc(sizeof(char *) * (i + 1));
	if (!shell->environment->export_env)
		(write(2, "\033[0;31mError: environment malloc fail\033[0m\n", 36), exit(EXIT_FAILURE));
	i = 0;
	j = 0;
	while (env[i])
		shell->environment->export_env[j++] = ft_strdup(env[i++]);
	shell->environment->export_env[j] = NULL;
	// t_values	*temp = shell->environment->vals;
	// printf("---------PATH---------\n");
	// i = -1;
	// while (shell->environment->path[++i])
	// {
	// 	printf("#%s#\n", shell->environment->path[i]);
	// }
	// printf("---------PATH---------\n");
	// printf("---------export_env--------\n");
	// i = -1;
	// while (shell->environment->export_env[++i])
	// 	printf("#%s#\n", shell->environment->export_env[i]);
	// printf("---------export_env--------\n");
	// printf("---------env---------\n");
	// while (temp->next)
	// {
	// 	printf("#%s=%s#\n", temp->key, temp->value);
	// 	temp = temp->next;
	// }
	// printf("---------env---------\n\n");
}

char *key_time(char *env)
{
	int	i;
	char	*key;
	i = 0;
	while(env[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
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
	if (!temp)
		printf("issue in make values node\n");
	// temp->envstr = ft_strdup(envline);
	temp->key = ft_strdup(key);
	temp->value = getenv(temp->key);
	temp->next = NULL;
	ft_lstadd_back_values(&shell->environment->vals, temp);
}

void	minishell(t_shell *shell)
{
	int	i;

	while (1)
	{
		shell->input_L = readline("meowshell> ");
		if (shell->input_L && shell->input_L[0] != '\0')
			add_history(shell->input_L);
		if (!shell->input_L)	// ctrl-D
			break ;
		else if (shell->input_L[0] != '\0')
		{
			shell->input_L = ft_strtrim_free(shell->input_L, " ");
			if (!shell->input_L || shell->input_L[0] == '\0') // spaces only
			{
				free(shell->input_L);
				continue ;
			}
			else if (open_quote_or_no(shell->input_L) == 1)
			{
				write(2, "Error: open quotes\n", 19);
				free(shell->input_L);
				continue ;
			}
			else if (check_pipes(shell->input_L) == 1)
			{
				write(2, "Error: syntax error near unexpected token '|'\n", 46);
				free(shell->input_L);
				continue ;
			}
			// else if (operators valid) // MAKE SURE YOU CHECK THEM HERE SO IT DOESNT MAKE IT HORRIBLE
			else
			{
				shell->input_L = ft_strtrim_free(expand_them_vars(shell->input_L, shell->environment, shell), " ");
				// shell->input_L = rmv_invalid_vars(shell->input_L, shell->environment);
				shell->input_L = rmv_extra_spaces(shell->input_L);
				shell->num_of_cmds = count_pipes(shell->input_L) + 1; // check if it counts inside quotes
				// printf("num_of_cmd = %d\n", shell->num_of_cmds);
				shell->pipe_split_L = split_pipes(shell->input_L, '|');
				if (!shell->pipe_split_L)
				(free_all(shell), write(2, "\033[0;31mError: malloc fail\033[0m\n", 24), exit(EXIT_FAILURE));
				// else
				// {
					// 	int i = -1;
					// 	while (shell->pipe_split_L[++i] != NULL)
					// 	printf("#%s#\n", shell->pipe_split_L[i]);
				// }
				i = 0;
				while (shell->pipe_split_L[i])
					tokenize_it(shell, shell->pipe_split_L[i++]);
			}
			final_exec(shell->commands, shell->environment, shell->num_of_cmds);
			// start_execution(shell);
			print_commands(shell->commands);
			if (shell->pipe_split_L)
				free_array(shell->pipe_split_L);
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
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// void	free_all(t_shell *shell)
// {
// 	printf("freeing\n");
// 	// int	i;
// 	// i = -1;
// 	ft_lstclear_values(shell->environment->vals);
// 	// free(shell->environment->vals);
// 	if (shell->environment)
// 	{
// 		free(shell->environment->cwd);
// 		free(shell->environment->owd);
// 		free_array(shell->environment->path);
// 		// free(shell->environment->);
// 		free(shell->environment);
// 	}
// 	if (shell->pipe_split_L)
// 	{
// 		// shell->num_of_pipes += 1;
// 		// while (--shell->num_of_pipes >= 0)
// 		// 	free(shell->pipe_split_L[shell->num_of_pipes]);
// 		// free(shell->pipe_split_L);
// 		free_array(shell->pipe_split_L);
// 	}
// 	if (shell->commands)
// 	{
// 		while (shell->commands)
// 		{
// 			printf("free cmds\n");
// 			free_array(shell->commands->cmd_args);
// 			free(shell->commands->cmd_line_L);
// 			shell->commands = shell->commands->next;
// 		}
// 		free(shell->commands);
// 	}
// 	// free(shell);
// }

int	main(int ac, char **av, char **env)
{
	t_shell shell;
	
	(void)av;
	if (ac != 1)
		return (printf("'./minishell' only, no arguments\n"));
	// int i = -1;
	// printf("---------ENV OG--------\n");
	// while (env[++i])
	// 	printf("#%s#\n", env[i]);
	// printf("---------ENV OG--------\n");
	ft_bzero(&shell, sizeof(t_shell)); // why
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

// \033[1;31m	               7 (Escape sequence for red)
// 	environment malloc fail	   24 (Plain text)
// 	\033[0m             	   4 (Reset color)
// 	\n	                       1 (Newline)