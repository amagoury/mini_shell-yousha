/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:43:01 by amagoury          #+#    #+#             */
/*   Updated: 2025/02/21 22:29:29 by amagoury         ###   ########.fr       */
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

void add_command(t_command **command, t_command *new)
{
    t_command *tmp;
    char *value;
    if (!command || !new)
        return;
    tmp = *command;
    if(!tmp)
    {
        *command = new;
        return ;
    }
    while(tmp)
    {
        if(ft_strncmp(tmp->cmd, new->cmd, ft_strlen(new->cmd)) == 0)
        {
            value = ft_strdup(new->cmd);
            if (!value)
            {
                ft_putendl_fd("Memory allocation failed", STDERR_FILENO);
                return;
            }
            free(new->cmd);
            new->cmd = value;
            new->next = tmp->next;
            free(tmp);
            *command = new;
            return;
        }
        if(!tmp->next)
            break;
        tmp = tmp->next;
    }
    tmp->next = new;
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


// // Main function to test my_cd
// int main(void)
// {
//     t_environment env;
//     char cwd[PATH_MAX];

//     // Initialize environment
//     env.cwd = ft_strdup(getcwd(cwd, PATH_MAX));
//     env.owd = NULL;
//     env.command = NULL;

//     printf("Initial directory: %s\n", env.cwd);

//     // Test 1: Change to HOME directory
//     printf("\nTesting cd to HOME directory...\n");
//     if (my_cd(&env, NULL) == 0)
//         printf("Successfully changed to HOME directory. New directory: %s\n", env.cwd);
//     else
//         printf("Failed to change to HOME directory.\n");

//     // Test 2: Change to a specific directory
//     printf("\nTesting cd to /tmp...\n");
//     if (my_cd(&env, "/tmp") == 0)
//         printf("Successfully changed to /tmp. New directory: %s\n", env.cwd);
//     else
//         printf("Failed to change to /tmp.\n");

//     // Test 3: Change back to the previous directory (OLDPWD)
//     printf("\nTesting cd to OLDPWD...\n");
//     if (my_cd(&env, "-") == 0)
//         printf("Successfully changed back to previous directory. New directory: %s\n", env.cwd);
//     else
//         printf("Failed to change to OLDPWD.\n");

//     // Test 4: Change to a non-existent directory
//     printf("\nTesting cd to a non-existent directory...\n");
//     if (my_cd(&env, "/nonexistent") == 0)
//         printf("Successfully changed to /nonexistent. New directory: %s\n", env.cwd);
//     else
//         printf("Failed to change to /nonexistent (expected).\n");

//     // Clean up
//     free(env.cwd);
//     free(env.owd);
//     while (env.command)
//     {
//         t_command *tmp = env.command;
//         env.command = env.command->next;
//         free(tmp->cmd);
//         free(tmp);
//     }

//     return 0;
// }