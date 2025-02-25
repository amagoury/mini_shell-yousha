/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bulidin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:09:53 by aishamagour       #+#    #+#             */
/*   Updated: 2025/02/25 20:11:53 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
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

// int main(void)
// {
//     char *a = "hi";
//     char *b = "hello";

//     printf("%d\n", ft_strcmp())
// }

// int     exec_bulidin(t_command *is_cmd)
// {
// 	char **env;
// 	char **export_env;
// 	char *head;
// 	if (ft_strcmp(is_cmd->cmd_args[0], "echo") == 0)
// 		 my_echo(is_cmd->cmd_args,is_cmd);
// 	else if (ft_strcmp(is_cmd->cmd_args[0], "cd") == 0)
// 	{
// 		char *path = NULL;
// 		  if (is_cmd->cmd_args && is_cmd->cmd_args[1]) // Check if there's a path argument
//             path = is_cmd->cmd_args[1];
//         return my_cd(env, path); // Pass the correct arguments
// 	}
// 	else if (ft_strcmp(is_cmd->cmd_args[0], "pwd") == 0)
// 		ms_pwd();
// 	else if (ft_strcmp(is_cmd->cmd_args[0], "export") == 0)
// 		 return (ft_export(is_cmd, *export_env));
// 	else if (ft_strcmp(is_cmd->cmd_args[0], "unset") == 0)
//     	my_unset(&head, is_cmd->cmd_args[0]); 
// 	else if (ft_strcmp(is_cmd->cmd_args[0], "env") == 0)
// 		return (ft_env());
// 	else if (ft_strcmp(is_cmd->cmd_args[0], "exit") == 0)
// 		exit_shell(is_cmd);
// 	return (0);
// }
int exec_bulidin(t_command *is_cmd, t_environment *env)
{
    if (ft_strcmp(is_cmd->cmd_args[0], "echo") == 0)
       return my_echo(is_cmd->cmd_args, is_cmd);
    else if (ft_strcmp(is_cmd->cmd_args[0], "cd") == 0)
    {
        char *path = NULL;
        if (is_cmd->cmd_args && is_cmd->cmd_args[1]) // Check if there's a path argument
            path = is_cmd->cmd_args[1];
        return my_cd(env, path); // Pass the environment and path
    }
    else if (ft_strcmp(is_cmd->cmd_args[0], "pwd") == 0)
        return ms_pwd();
    else if (ft_strcmp(is_cmd->cmd_args[0], "export") == 0)
        return ft_export(is_cmd, env->export_env); // Pass the environment's export_env
    else if (ft_strcmp(is_cmd->cmd_args[0], "unset") == 0)
        return my_unset(&env->head, is_cmd->cmd_args[0]); // Pass the head of the linked list
    else if (ft_strcmp(is_cmd->cmd_args[0], "env") == 0 || ft_strcmp(is_cmd->cmd_args[0], "ENV") == 0)
        return ft_env(env->vals); // Pass the environment
    else if (ft_strcmp(is_cmd->cmd_args[0], "exit") == 0)
        exit_shell(is_cmd);
    return 0; // Default return value
}
bool  is_bulidin(t_command *is_cmd)
{
    if (ft_strcmp(is_cmd->cmd_args[0], "echo") == 0)
       return true;
    else if (ft_strcmp(is_cmd->cmd_args[0], "cd") == 0)
		return true;
    else if (ft_strcmp(is_cmd->cmd_args[0], "pwd") == 0)
        return true;
    else if (ft_strcmp(is_cmd->cmd_args[0], "export") == 0)
        return true; 
    else if (ft_strcmp(is_cmd->cmd_args[0], "unset") == 0)
        return true;
    else if (ft_strcmp(is_cmd->cmd_args[0], "env") == 0)
        return true ; // Pass the environment
    else if (ft_strcmp(is_cmd->cmd_args[0], "exit") == 0)
        return true;
    return false; // Default return value
}

bool  run_bulidin(t_command *cmd, t_environment *env)
{

    // printf("her is the issue\n");
	if (exec_bulidin(cmd, env) != 0)
		return (false);
	return (true);
}