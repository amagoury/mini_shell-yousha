/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:37:59 by aishamagour       #+#    #+#             */
/*   Updated: 2025/03/03 15:35:45 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_env(t_values *env)
{
    // printf("meow\n");
    if (!env)
        return (1); // Return an error code if the list is empty or invalid
    while (env)
    {
        printf("%s=%s\n", env->key, env->value); // should use write and put the OUTPUT_STD
        env = env->next;
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
