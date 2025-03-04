/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:37:59 by aishamagour       #+#    #+#             */
/*   Updated: 2025/03/04 21:42:50 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_env(t_values *env,t_context *text)
{
    if (!env)
        return (1); // Return an error code if the list is empty or invalid
    while (env)
    {
        ft_putstr_fd(env->key, text->outputfd);
        ft_putstr_fd("=", text->outputfd);
        ft_putstr_fd(env->value, text->outputfd);
        write(text->outputfd, "\n", 1);
        env = env->next;
    }
    return (0); // Return success
}
