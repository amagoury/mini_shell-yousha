/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:15:38 by aishamagour       #+#    #+#             */
/*   Updated: 2025/01/28 15:32:48 by aishamagour      ###   ########.fr       */
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

// bool is_valid_env(const char *env_var)
// {
//     int index = 0;

//     // Check if the first character is a digit (invalid for env vars)
//     if (ft_isdigit(env_var[index]) == 1)
//     {
//         return false;
//     }

//     // Iterate through the string until '=' or the end of the string
//     while (env_var[index] != '\0' && env_var[index] != '=')
//     {
//         // Check if the current character is alphanumeric
//         if (ft_isalnum(env_var[index]) == 0)
//         {
//             return false;
//         }
//         index++;
//     }

//     // If we reach here, the environment variable name is valid
//     return true;
// }
bool is_valid_env(const char *env_var)
{
    int i = 0;

    if (!env_var || !*env_var)
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