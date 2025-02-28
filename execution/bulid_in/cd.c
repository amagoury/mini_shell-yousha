/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:43:01 by amagoury          #+#    #+#             */
/*   Updated: 2025/02/28 20:08:47 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// t_command *creat_command(char *cmd)
// {
//     t_command *new;

//     new = malloc(sizeof(t_command));
//     if (!new)
//         return (NULL);
//     new->cmd = ft_strdup(cmd);
//     new->next = NULL;
//     return (new);
// }

// void add_command(t_environment **env ,t_command *new)
// {
//     t_command *tmp;
//     char *value;
//     if (!command || !new)
//         return;
//     tmp = *command;
//     if(!tmp)
//     {
//         *command = new;
//         return ;
//     }
//     while(tmp)
//     {
//         if(ft_strncmp(tmp->cmd, new->cmd, ft_strlen(new->cmd)) == 0)
//         {
//             value = ft_strdup(new->cmd);
//             if (!value)
//             {
//                 ft_putendl_fd("Memory allocation failed", STDERR_FILENO);
//                 return;
//             }
//             free(new->cmd);
//             new->cmd = value;
//             new->next = tmp->next;
//             free(tmp);
//             *command = new;
//             return;
//         }
//         if(!tmp->next)
//             break;
//         tmp = tmp->next;
//     }
//     tmp->next = new;
// }

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
        new_path = getenv("HOME");
        if (!new_path)
        {
            ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
            return (1);
        }
    }
    // Handle previous directory
    else if (path[0] == '-' && !path[1])
    {
        new_path = getenv("OLDPWD");
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
    // new_cmd = creat_command(current_dir);
    // if (new_cmd)
    //     add_command(&env->command, new_cmd);

    // Update current and old working directories
    if (getcwd(current_dir, PATH_MAX) != NULL)
    {
        free(env->owd);  // Free the old working directory if it exists
        env->owd = ft_strdup(env->cwd);  // Save old directory
        free(env->cwd);  // Free the current working directory if it exists
        env->cwd = ft_strdup(current_dir);  // Update current directory
    }
    else
    {
        ft_putendl_fd("cd: error updating directory", STDERR_FILENO);
        return (1);
    }

    return (0);
}
