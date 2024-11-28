/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:43:01 by amagoury          #+#    #+#             */
/*   Updated: 2024/11/28 18:35:15 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void update_dir(t_bulid *bulid, char *key, char *value)
{
    t_list  *envp;
    t_values  *temp;

    envp = bulid->envp;

    while (envp != NULL)
    {
        temp = (t_values *)envp->content;

        if (ft_strncmp_lyall(temp->key, key,value) == 0)
        {
            // Free old value and update it
            free(temp->value);
            temp->value = value;
            return; // Exit early since the key was found
        }

        envp = envp->next;
    }

    // If we reach here, the key was not found; add a new variable
    get_env(bulid, key);
}
