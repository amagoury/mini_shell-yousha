/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:19:39 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/05 00:13:03 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_shell *shell)
{
	// printf("freeing\n");
	// int	i;
	// i = -1;
	// free(shell->environment->vals);
	if (shell->input_L)
		free(shell->input_L);
	if (shell->pipe_split_L)
		free_array(shell->pipe_split_L);
	if (shell->commands)
		free_cmds(shell);
	if (shell->environment)
		free_env(shell->environment);
	// if (shell)
	// 	free(shell);
}

void	free_env(t_environment *env)
{
	if (env)
	{
		free(env->cwd);
		free(env->owd);
		free_array(env->path);
		if (env->export_env)
			free_array(env->export_env);
		ft_lstclear_values(env->vals);
		free(env);
	}
}

void	free_cmds(t_shell	*shell)
{
	t_command	*temp;
	
	if (shell->commands)
	{
		while (shell->commands)
		{
			temp = shell->commands->next;
			// printf("to be freed ----------------------\n");
			// print_commands(shell->commands);
			// printf("to be freed ----------------------\n");
			// printf("free cmds\n");
			free_array(shell->commands->cmd_args);
			free(shell->commands->cmd_line_L);
			// list clear for redirects
			if (shell->commands->redir)
				ft_lstclear_redir(shell->commands->redir);
			free(shell->commands);
			shell->commands = temp;
		}
		free(shell->commands);
	}
}