/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:30:37 by aishamagour       #+#    #+#             */
/*   Updated: 2025/03/04 19:58:55 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


static char is_n(char *str)
{
	int i;

	i = 1;
	while(str[i])
	{
		if(str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int my_echo(char **command)
{
	int i;
	int j;
	bool flag;
	flag = false;
	i = 1;
	while(command[i] && command[i][0] == '-' && command[i][1] == 'n' && is_n(command[i]) == 0)
	{
		flag = true;
		i++;
	}
	while(command[i])
	{
		j = 0;
		while(command[i][j])
		{
			write(1, &command[i][j], 1);
			j++;
		}
		if(command[i + 1])
			write(1, " ", 1);
		i++;
	}
	if(flag == false)
		write(1, "\n", 1);
	return(0);
}
