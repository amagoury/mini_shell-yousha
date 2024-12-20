/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:43:01 by amagoury          #+#    #+#             */
/*   Updated: 2024/12/03 11:55:38 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int my_cd(t_environment *home, char *path)
{
    if (!path || strcmp(path, "") == 0)
    {
        if (!home->path)
        {
            return 1;
        }
        path = home->path;
    }
    if (chdir(path) != 0) 
        return 1;

    return 0; 
}