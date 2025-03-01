/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:19:39 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/01 17:33:42 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_shell *shell)
{
	printf("freeing\n");
	// int	i;
	// i = -1;
	// free(shell->environment->vals);
	free_env(shell->environment);
	if (shell->pipe_split_L)
	{
		printf("free pipe_split\n");
		// shell->num_of_pipes += 1;
		// while (--shell->num_of_pipes >= 0)
		// 	free(shell->pipe_split_L[shell->num_of_pipes]);
		// free(shell->pipe_split_L);
		free_array(shell->pipe_split_L);
	}
	free_cmds(shell);
	// free(shell);
}

void	free_env(t_environment *env)
{
	if (env)
	{
		ft_lstclear_values(env->vals);
		free(env->cwd);
		free(env->owd);
		free_array(env->path);
		if (env->export_env)
			free_arrray(env->export_env);
		free(env);
	}
}

void	free_cmds(t_shell	*shell)
{
	if (shell->commands)
	{
		while (shell->commands)
		{
			// printf("to be freed ----------------------\n");
			// print_commands(shell->commands);
			// printf("to be freed ----------------------\n");
			printf("free cmds\n");
			free_array(shell->commands->cmd_args);
			free(shell->commands->cmd_line_L);
			// list clear for redirects
			ft_lstclear_redir(shell->commands->redir);
			shell->commands = shell->commands->next;
		}
		free(shell->commands);
	}
}