/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:45:07 by aishamagour       #+#    #+#             */
/*   Updated: 2025/02/28 20:10:28 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    exit_shell(t_command *command)
{
	t_command *tmp;

	tmp = command;
	while (tmp)
	{
		command = tmp->next;
		free(tmp->cmd_args);
		free(tmp);
		tmp = command;
	}
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