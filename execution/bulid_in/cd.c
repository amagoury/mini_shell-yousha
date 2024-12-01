/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:43:01 by amagoury          #+#    #+#             */
/*   Updated: 2024/12/01 12:24:01 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 static void pathcase(t_shell *shell, int cmd_num)
{
    char *home = getenv("HOME");
    if (chdir(home) < 0)
    {
        shell->exit_code = 1;
    }
}
static int ft_cd0(t_shell *shell, int cmd_num)
{
    if (ft_strcmp(shell->command[cmd_num].cmd_args[1], "~") == 0)
    {
        char *home = getenv("HOME");
        if (home == NULL)
            return 1;
        if (chdir(home) < 0)
            return 1;
    }
    else if (ft_strcmp(shell->command[cmd_num].cmd_args[1], "-") == 0)
    {
        char *oldpwd = getenv("OLDPWD");
        if (oldpwd == NULL) 
            return 1;
        if (chdir(oldpwd) < 0)
            return 1;
        printf("%s\n", oldpwd);
    }
    else {
        if (chdir(shell->command[cmd_num].cmd_args[1]) < 0)
            return 1;
    }
    return 0;
}

int ft_cd(t_shell *shell, int cmd_num)
{
    if (shell->command[cmd_num].cmd_args[1] == NULL)
    {   
        char *home = getenv("HOME");
        if (home != NULL)
            chdir(home);
    }
    else
    {
        return ft_cd0(shell, cmd_num);
    }
    return 0;
}
