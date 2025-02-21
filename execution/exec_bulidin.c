/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bulidin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:09:53 by aishamagour       #+#    #+#             */
/*   Updated: 2025/02/21 14:38:21 by lalwafi          ###   ########.fr       */
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

int     exec_bulidin(t_command *is_cmd)
{
	// char **env;
	char **export_env;
	if (ft_strcmp(is_cmd->cmd, "echo") == 0)
		return (my_echo(is_cmd));
	else if (ft_strcmp(is_cmd->cmd, "cd") == 0)
		return (ft_cd(is_cmd));
	else if (ft_strcmp(is_cmd->cmd, "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(is_cmd->cmd, "export") == 0)
		 return (ft_export(is_cmd, *export_env));
	else if (ft_strcmp(is_cmd->cmd, "unset") == 0)
		return (ft_unset(is_cmd));
	else if (ft_strcmp(is_cmd->cmd, "env") == 0)
		return (ft_env());
	else if (ft_strcmp(is_cmd->cmd, "exit") == 0)
		return (ft_exit(is_cmd));
	return (0);
}


bool  run_bulidin(t_environment *env)
{
	if (exec_bulidin(env->path) != 0)
		return (false);
	return (true);
}