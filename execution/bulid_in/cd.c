/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:43:01 by amagoury          #+#    #+#             */
/*   Updated: 2024/11/30 19:27:47 by aishamagour      ###   ########.fr       */
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

static int simple_ms_cd_home(t_bulid *bulid,t_environment )
{
    char  *home;

    home = get_env(bulid, "HOME");
    if (home == NULL)
    {
        if (cmdblock->cmd_argv != NULL)
            simple_cmd_error(cmdblock->cmd_argv[0], "HOME not set");
        else
            simple_cmd_error("cd", "HOME not set");
        return 1;
    }
    if (ms_chdir(bulid, home) == 0)
        return 0;

    if (access(home, F_OK) == 0)
    {
        if (cmdblock->cmd_argv != NULL)
            simple_cmd_error(cmdblock->cmd_argv[0], "Not a directory");
        else
            simple_cmd_error("cd", "Not a directory");
    }
    else
    {
        if (cmdblock->cmd_argv != NULL)
            simple_cmd_error(cmdblock->cmd_argv[0], "No such file or directory");
        else
            simple_cmd_error("cd", "No such file or directory");
    }
    return 1;
}

// dir_mas,
// the mainfunction for the cd