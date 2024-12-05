/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:50:30 by aishamagour       #+#    #+#             */
/*   Updated: 2024/12/05 21:20:10 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str)
{
    char  *old_quotes;
    int    nbr_of_quotes;
    int i;
    int j;

    nbr_of_quotes = ft_strlen(str);
    i = 0;
    while(str[i])
    {
        if(str[i] == '"' || str[i] == '\'')
            nbr_of_quotes++;
    }
    i++;
    old_quotes = malloc(sizeof(char) * (nbr_of_quotes + 1));
    j = -1;
    while(str[i])
    {
        if(str[i] == '"' || str[i] == '\'')
            old_quotes[j++] = str[i];
        i++;
    }
    old_quotes[j] = '\0';
    return (old_quotes);
}


