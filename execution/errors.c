/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:08:05 by aishamagour       #+#    #+#             */
/*   Updated: 2025/01/27 15:29:09 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void cmd_error(char *cmd, char *msg)
// {
//     printf( "Error: %s: %s\n", cmd ? cmd : "unknown", msg);
// }

// int print_error(t_shell *shell, const char *cmd, const char *msg, const char *arg)
// {
//     shell->exit_code = 1;
//     ft_putstr_fd("minishell: ", STDERR_FILENO);
//     ft_putstr_fd(cmd, STDERR_FILENO);
//     ft_putstr_fd(": ", STDERR_FILENO);
//     if (arg)
//     {
//         ft_putstr_fd(arg, STDERR_FILENO);
//         ft_putstr_fd(": ", STDERR_FILENO);
//     }
//     ft_putstr_fd(msg, STDERR_FILENO);
//     return (1);
// }
