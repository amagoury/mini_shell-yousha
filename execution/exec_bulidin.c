/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bulidin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:09:53 by aishamagour       #+#    #+#             */
/*   Updated: 2025/02/21 22:59:46 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
=======
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:09:53 by aishamagour       #+#    #+#             */
/*   Updated: 2025/02/21 14:38:21 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
>>>>>>> e3c04689e87eb0d88ac830579b35e40b4e79eebd

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

<<<<<<< HEAD
// int     exec_bulidin(t_command *is_cmd)
// {
// 	char **env;
// 	char **export_env;
// 	char *head;
// 	if (ft_strcmp(is_cmd->cmd, "echo") == 0)
// 		 my_echo(is_cmd->cmd_args,is_cmd);
// 	else if (ft_strcmp(is_cmd->cmd, "cd") == 0)
// 	{
// 		char *path = NULL;
// 		  if (is_cmd->cmd_args && is_cmd->cmd_args[1]) // Check if there's a path argument
//             path = is_cmd->cmd_args[1];
//         return my_cd(env, path); // Pass the correct arguments
// 	}
// 	else if (ft_strcmp(is_cmd->cmd, "pwd") == 0)
// 		ms_pwd();
// 	else if (ft_strcmp(is_cmd->cmd, "export") == 0)
// 		 return (ft_export(is_cmd, *export_env));
// 	else if (ft_strcmp(is_cmd->cmd, "unset") == 0)
//     	my_unset(&head, is_cmd->cmd); 
// 	else if (ft_strcmp(is_cmd->cmd, "env") == 0)
// 		return (ft_env());
// 	else if (ft_strcmp(is_cmd->cmd, "exit") == 0)
// 		exit_shell(is_cmd);
// 	return (0);
// }
int exec_bulidin(t_command *is_cmd, t_environment *env)
{
    if (ft_strcmp(is_cmd->cmd, "echo") == 0)
       return my_echo(is_cmd->cmd_args, is_cmd);
    else if (ft_strcmp(is_cmd->cmd, "cd") == 0)
    {
        char *path = NULL;
        if (is_cmd->cmd_args && is_cmd->cmd_args[1]) // Check if there's a path argument
            path = is_cmd->cmd_args[1];
        return my_cd(env, path); // Pass the environment and path
    }
    else if (ft_strcmp(is_cmd->cmd, "pwd") == 0)
        return ms_pwd();
    else if (ft_strcmp(is_cmd->cmd, "export") == 0)
        return ft_export(is_cmd, env->export_env); // Pass the environment's export_env
    else if (ft_strcmp(is_cmd->cmd, "unset") == 0)
        return my_unset(&env->head, is_cmd->cmd); // Pass the head of the linked list
    else if (ft_strcmp(is_cmd->cmd, "env") == 0 || ft_strcmp(is_cmd->cmd, "ENV") == 0)
        return ft_env(is_cmd); // Pass the environment
    else if (ft_strcmp(is_cmd->cmd, "exit") == 0)
        exit_shell(is_cmd);
    return 0; // Default return value
}
bool  is_bulidin(t_command *is_cmd)
{
    if (ft_strcmp(is_cmd->cmd, "echo") == 0)
       return true;
    else if (ft_strcmp(is_cmd->cmd, "cd") == 0)
		return true;
    else if (ft_strcmp(is_cmd->cmd, "pwd") == 0)
        return true;
    else if (ft_strcmp(is_cmd->cmd, "export") == 0)
        return true; 
    else if (ft_strcmp(is_cmd->cmd, "unset") == 0)
        return true;
    else if (ft_strcmp(is_cmd->cmd, "env") == 0)
        return true ; // Pass the environment
    else if (ft_strcmp(is_cmd->cmd, "exit") == 0)
        return true;
    return false; // Default return value
}

bool  run_bulidin(t_command *cmd, t_environment *env)
{

	if (exec_bulidin(cmd, env) != 0)
=======
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
>>>>>>> e3c04689e87eb0d88ac830579b35e40b4e79eebd
		return (false);
	return (true);
}