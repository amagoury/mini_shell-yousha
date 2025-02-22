/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:15:38 by aishamagour       #+#    #+#             */
/*   Updated: 2025/02/21 22:53:52 by amagoury         ###   ########.fr       */
=======
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:15:38 by aishamagour       #+#    #+#             */
/*   Updated: 2025/02/08 17:32:58 by aishamagour      ###   ########.fr       */
>>>>>>> e3c04689e87eb0d88ac830579b35e40b4e79eebd
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *get_env_name(char *dest, const char *src)
{
    int i;

    if (!src) // Check if the source string is NULL
        return NULL;

    i = 0;
    // Copy characters from src to dest until '=' or end of string is reached
    while (src[i] != '\0' && src[i] != '=' && i < BUFF_SIZE - 1)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0'; // Null-terminate the destination string
    return dest; // Return the destination buffer
}

bool is_valid_env(const char *env_var)
{
    int i = 0;

<<<<<<< HEAD
    if (!*env_var)
=======
    if (!env_var || !*env_var)
>>>>>>> e3c04689e87eb0d88ac830579b35e40b4e79eebd
        return false;

    if (!ft_isalpha(env_var[0]) && env_var[0] != '_')
        return false;

    while (env_var[i] && env_var[i] != '=')
    {
        if (!ft_isalnum(env_var[i]) && env_var[i] != '_')
            return false;
        i++;
    }
    return true;
}