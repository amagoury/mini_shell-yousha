/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bulidin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:09:53 by aishamagour       #+#    #+#             */
/*   Updated: 2025/03/04 20:45:17 by amagoury         ###   ########.fr       */
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

int exec_bulidin( t_shell *shell,t_context *cntx, t_environment *env)
{
    
    if (ft_strcmp(cntx->args[0], "echo") == 0)
       return my_echo(cntx->args);
    else if (ft_strcmp(cntx->args[0], "cd") == 0)
    {
        char *path = NULL;
        if (cntx->args && cntx->args[1]) // Check if there's a path argument
            path = cntx->args[1];
        return my_cd(env, path); // Pass the environment and path
    }
    else if (ft_strcmp(cntx->args[0], "pwd") == 0)
        return ms_pwd();
    else if (ft_strcmp(cntx->args[0], "export") == 0)
        return ft_export(cntx, env->vals);//env->export_env); // Pass the environment's export_env
    else if (ft_strcmp(cntx->args[0], "unset") == 0)
        return my_unset(&env->vals, cntx->args[1]); // Pass the head of the linked list
    else if (ft_strcmp(cntx->args[0], "ENV") == 0 || ft_strcmp(cntx->args[0], "env") == 0)
        return ft_env(env->vals,cntx); // Pass the environment
    else if (ft_strcmp(cntx->args[0], "exit") == 0)
        exit_shell(shell,cntx);
    return (1); // Default return value
}
bool  is_bulidin(char *str)
{
    if (str == NULL)
        return (false);
    if (ft_strcmp(str, "echo") == 0)
       return true;
    else if (ft_strcmp(str, "cd") == 0)
		return true;
    else if (ft_strcmp(str, "pwd") == 0)
        return true;
    else if (ft_strcmp(str, "export") == 0)
        return true; 
    else if (ft_strcmp(str, "unset") == 0)
        return true;
    else if (ft_strcmp(str, "env") == 0 || ft_strcmp(str, "ENV") == 0)
        return true ; // Pass the environment
    else if (ft_strcmp(str, "exit") == 0)
        return true;
    return false; // Default return value
}

bool  run_bulidin( t_shell *shell,t_context *context, t_environment *env)
{

    // printf("her is the issue\n");
	if (exec_bulidin(shell,context, env) != 0)
		return (false);
	return (true);
}