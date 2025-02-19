/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bulidin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:09:53 by aishamagour       #+#    #+#             */
/*   Updated: 2025/02/19 23:22:52 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static  int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
	{
		return (1);
	}
	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
		{
			i++;
		}
		else
		{
			return (1);
		}
	}
	return (0);
}

int     exec_bulidin(t_command *cmd)
{
	// char **env;
	char **export_env;
	if (ft_strcmp(cmd->cmd_args[0], "echo") == 0)
		return (ft_echo(cmd));
	else if (ft_strcmp(cmd->cmd_args[0], "cd") == 0)
		return (ft_cd(cmd));
	else if (ft_strcmp(cmd->cmd_args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd->cmd_args[0], "export") == 0)
		 return (ft_export(cmd, *export_env));
	else if (ft_strcmp(cmd->cmd_args[0], "unset") == 0)
		return (ft_unset(cmd));
	else if (ft_strcmp(cmd->cmd_args[0], "env") == 0)
		return (ft_env());
	else if (ft_strcmp(cmd->cmd_args[0], "exit") == 0)
		return (ft_exit(cmd));
	return (0);
}


bool  run_bulidin(t_environment *path)
{
	if (exec_bulidin(path) != 0)
		return (false);
	return (true);
}