/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:19:39 by lalwafi           #+#    #+#             */
/*   Updated: 2025/02/27 14:22:51 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_shell *shell)
{
	printf("freeing\n");
	// int	i;
	// i = -1;
	ft_lstclear_values(shell->environment->vals);
	// free(shell->environment->vals);
	if (shell->environment)
	{
		free(shell->environment->cwd);
		free(shell->environment->owd);
		free_array(shell->environment->path);
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
	free_cmds(shell);
	// free(shell);
}



void	free_cmds(t_shell	*shell)
{
	if (shell->commands)
	{
		while (shell->commands)
		{
			printf("free cmds\n");
			free_array(shell->commands->cmd_args);
			free(shell->commands->cmd_line_L);
			shell->commands = shell->commands->next;
		}
		free(shell->commands);
	}
}