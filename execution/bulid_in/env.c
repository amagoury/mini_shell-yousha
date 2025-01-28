/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:37:59 by aishamagour       #+#    #+#             */
/*   Updated: 2025/01/27 16:08:58 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_env(t_command *env)
{
    if (!env)
        return (1); // Return an error code if the list is empty or invalid

    t_command *tmp = env;
    while (tmp)
    {
        if (tmp->cmd) // Check if cmd is not NULL
            printf("%s\n", tmp->cmd);
        else
            printf("(null)\n"); // Handle case where cmd is NULL
        tmp = tmp->next;
    }
    return (0); // Return success
}

// int main()
// {
// 	t_command *env = NULL;

// 	add_node(&env, "PATH=/usr/bin");
// 	add_node(&env, "HOME=/home/user");
// 	add_node(&env, "USER=user");
// 	add_node(&env, "PWD=/home/user");

// 	ft_env(env);

// 	return (0);
// }
