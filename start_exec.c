/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:04:52 by lalwafi           #+#    #+#             */
/*   Updated: 2025/02/25 13:05:02 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_execution(t_shell *shell)
{
	int i = 0;
	for (t_command * store = shell->commands; store; store = store->next)
		i++;
	shell->commands->cmd = "pwd";
	final_exec(shell->commands, shell->environment, i);
}