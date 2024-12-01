/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:50:30 by aishamagour       #+#    #+#             */
/*   Updated: 2024/12/01 00:13:35 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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