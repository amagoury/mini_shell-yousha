/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:43:01 by amagoury          #+#    #+#             */
/*   Updated: 2025/03/04 21:42:25 by amagoury         ###   ########.fr       */
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
// Search for the key in the existing environment variables
 // Key found, update the value
 void set_env_var(t_environment *env,  char *key, char *value)
{
    t_values *current = env->vals;

    current = env->vals;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            current->value = ft_strdup(value);
            return;
        }
        current = current->next;
    }
    t_values *new_var = (t_values *)malloc(sizeof(t_values));
    if (!new_var)
    {
        ft_putendl_fd("set_env_var: malloc failed", STDERR_FILENO);
        return;
    }
    new_var->key = ft_strdup(key);
    new_var->value = ft_strdup(value);
    new_var->next = env->vals; // Add to the beginning of the list
    env->vals = new_var;
}

  // Get current directory
    // Handle HOME directory
     // Handle previous directory
       // Change directory
          // Update environment variables
          // Update OLDPWD
          // Update PWD
           // Update environment variables in the env list
        // Assuming you have a function to set environment variables
int my_cd(t_environment *env, char *path)
{
    char current_dir[PATH_MAX];
    char *new_path;

    if (getcwd(current_dir, PATH_MAX) == NULL)
    {
        ft_putendl_fd("cd: error getting current directory", STDERR_FILENO);
        return (1);
    }
    if (!path || !*path)
    {
        new_path = ft_get_env("HOME", env->vals);
        if (!new_path)
        {
            ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
            return (1);
        }
    }
    else if (path[0] == '-' && !path[1])
    {
        new_path = ft_get_env("OLDPWD", env->vals);
        if (!new_path)
        {
            ft_putendl_fd("cd: OLDPWD not set", STDERR_FILENO);
            return (1);
        }
        ft_putendl_fd(new_path, STDOUT_FILENO);
    }
    else
        new_path = path;
    if (chdir(new_path) == -1)
    {
        ft_putendl_fd("cd: no such file or directory", STDERR_FILENO);
        return (1);
    }
    if (getcwd(current_dir, PATH_MAX) != NULL)
    {
        free(env->owd);  // Free the old working directory if it exists
        env->owd = ft_strdup(env->cwd);  // Save old directory
        free(env->cwd);  // Free the current working directory if it exists
        env->cwd = ft_strdup(current_dir);  // Update current directory
        set_env_var(env, "OLDPWD", env->owd);
        set_env_var(env, "PWD", env->cwd);
    }
    else
    {
        ft_putendl_fd("cd: error updating directory", STDERR_FILENO);
        return (1);
    }
    return (0);
}
