/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:43:01 by amagoury          #+#    #+#             */
/*   Updated: 2025/03/03 17:04:14 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

 char *ft_get_env(char * key,t_values *env)
 {
    while(env)
    {
        if (ft_strcmp(key, env->key) == 0)
            return (env->value);
        env = env->next;
    }
    return (NULL);
 }
int my_cd(t_environment *env, char *path)
{
    char current_dir[PATH_MAX];
    char *new_path;
    // t_command *new_cmd;

    // Get current directory
    if (getcwd(current_dir, PATH_MAX) == NULL)
    {
        ft_putendl_fd("cd: error getting current directory", STDERR_FILENO);
        return (1);
    }

    // Handle HOME directory
    if (!path || !*path)
    {
        new_path = ft_get_env("HOME",env->vals);
        if (!new_path)
        {
            ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
            return (1);
        }
    }
    // Handle previous directory
    else if (path[0] == '-' && !path[1])
    {
        new_path = ft_get_env("OLDPWD",env->vals);
        if (!new_path)
        {
            ft_putendl_fd("cd: OLDPWD not set", STDERR_FILENO);
            return (1);
        }
        ft_putendl_fd(new_path, STDOUT_FILENO);
    }
    else
        new_path = path;
    // Change directory
    if (chdir(new_path) == -1)
    {
        ft_putendl_fd("cd: no such file or directory", STDERR_FILENO);
        return (1);
    }
    // Update environment
   printf("before:  %s\n", new_path);
   new_path = ft_get_env("PWD",env->vals);
   printf("after:  %s\n", new_path);
   if(!new_path)
   {
        ft_putendl_fd("cd :PWD not set",STDERR_FILENO);
        return(1);
   }
    // Update current and old working directories
    if (getcwd(current_dir, PATH_MAX) != NULL)
    {
        free(env->owd);  // Free the old working directory if it exists
        env->owd = ft_strdup(env->cwd);  // Save old directory
        free(env->cwd);  // Free the current working directory if it exists
        env->cwd = ft_strdup(current_dir);  // Update current directory
        // update env for the keys
    }
    else
    {
        ft_putendl_fd("cd: error updating directory", STDERR_FILENO);
        return (1);
    }

    return (0);
}
