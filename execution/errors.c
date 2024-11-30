/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:08:05 by aishamagour       #+#    #+#             */
/*   Updated: 2024/11/30 19:09:17 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void simple_cmd_error(char *cmd, char *msg)
{
    printf( "Error: %s: %s\n", cmd ? cmd : "unknown", msg);
}
