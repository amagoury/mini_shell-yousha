/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:43:01 by amagoury          #+#    #+#             */
/*   Updated: 2025/01/12 17:56:26 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int my_cd(t_environment *home, char *path)
{
    char curent_dir[PATH_MAX];
    char *new_path;
    
    if(getcwd(curent_dir,PATH_MAX) == NULL)
    {
        ft_putendl_fd("Error getting current directory", STDERR_FILENO);
        return (1);
    }
    if(!path || !*path|| !ft_strncmp(path, "~", 1))
    {
        if(!home->vals)
        {
            ft_putendl_fd("Error getting home directory", STDERR_FILENO);
            return (1);
        }
        new_path = ft_strdup(home->vals->value);
    }
    else if(!ft_strncmp(path, "-", 1))
    {
        new_path = getenv(home->owd);
        if(!new_path)
        {
            ft_putendl_fd("Error getting old directory", STDERR_FILENO);
            return (1);
        }
    }
    else
        new_path = path;
    if(chdir(new_path) == -1)
    {
        ft_putendl_fd("Error changing directory", STDERR_FILENO);
        return (1);
    }
    // update the env
    setenv(home->owd, curent_dir, 1);
    getcwd(curent_dir, PATH_MAX);
    setenv(home->cwd, curent_dir, 1);
    return (0);
}

int main(void)
{
    t_environment home;
    char *path = "cd";
    get_env(&home, NULL);
    my_cd(&home, path);
    return (0);
}