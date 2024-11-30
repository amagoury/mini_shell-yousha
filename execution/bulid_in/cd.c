/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:43:01 by amagoury          #+#    #+#             */
/*   Updated: 2024/11/30 19:46:32 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void update_dir(t_bulid *bulid, char *key, char *value)
{
    t_list  *envp;
    t_values  *temp;

    envp = bulid->env_p;

    while (envp != NULL)
    {
        temp = (t_values *)envp->content;

        if (ft_strncmp_lyall(temp->key, key,value) == 0)
        {
            free(temp->value);
            temp->value = value;
            return;
        }

        envp = envp->next;
    }
    get_env(bulid, key);
}

static int change_directory(t_bulid *bulid, char *path)
{
    char *oldpwd;
    char *newpwd;

    if(access(path,F_OK) != 0)
        return(-1);
    oldpwd = getcwd(NULL,0);
    if(!oldpwd)
        return(-1);
    if(chdir(path) != 0)
    {
        free(oldpwd);
        return(-1);
    }
    newpwd = getcwd(NULL,0);
    if(!newpwd)
    {
        free(oldpwd);
        return(-1);
    }
    update_dir(bulid,"PWD",newpwd);
    update_dir(bulid,"OLDPWD",oldpwd);
    free(oldpwd);
    free(newpwd);
    return(0);
}

static int simple_ms_cd_home(t_bulid *bulid, t_command command)
{
    char  *home;

    initialize_command(&command);
    if (home == NULL)
    {
        if (command.cmd_args != NULL)
            simple_cmd_error(command.cmd_args[0], "HOME not set");
        else
            simple_cmd_error("cd", "HOME not set");
        return 1;
    }
    if (ms_chdir(bulid, home) == 0)
        return 0;

    if (access(home, F_OK) == 0)
    {
        if (command.cmd_args != NULL)
            simple_cmd_error(command.cmd_args[0], "Not a directory");
        else
            simple_cmd_error("cd", "Not a directory");
    }
    else
    {
        if (command.cmd_args != NULL)
            simple_cmd_error(command.cmd_args[0], "No such file or directory");
        else
            simple_cmd_error("cd", "No such file or directory");
    }
    return 1;
}


void    initialize_command(t_command *meow)
{
    meow->cmd_args[1][4] = "HOME";
    meow->cmd_line = NULL;
    meow->no_args = 69;
    meow->no_redirs = 0;
    meow->int_temp = 0;
    meow->redir_amount = 0;
    meow->redir = NULL;
}
// dir_mas,
// the mainfunction for the cd