/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:45:07 by aishamagour       #+#    #+#             */
/*   Updated: 2025/03/02 18:24:34 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    exit_shell(t_command *command)
{
	t_command *tmp;

	tmp = command;
	while (tmp)
	{
		// use free_all function
		command = tmp->next;
		free(tmp->cmd_args);
		free(tmp);
		tmp = command;
	}
	// exit(shell.exit_code);
	exit(0);
}

// int main(void)
// {
// 	t_command *command;
// 	t_command *new;

// 	command = NULL;
// 	new = creat_command("exit");
// 	add_command(&command, new);
// 	exit_shell(command);
// 	return (0);
// }