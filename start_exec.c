/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:04:52 by lalwafi           #+#    #+#             */
/*   Updated: 2025/02/25 19:27:35 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_execution(t_shell *shell)
{
	// int i = 0;
	// for (t_command * store = shell->commands; store; store = store->next)
	// 	i++;
	// shell->commands->cmd = ms_pwd();
	
	final_exec(shell->commands, shell->environment, shell->num_of_cmds);
}