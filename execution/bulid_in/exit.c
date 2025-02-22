/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:45:07 by aishamagour       #+#    #+#             */
/*   Updated: 2025/01/28 15:48:18 by aishamagour      ###   ########.fr       */
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
		free(tmp->cmd);
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