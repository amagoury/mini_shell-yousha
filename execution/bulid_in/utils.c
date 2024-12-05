/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:50:30 by aishamagour       #+#    #+#             */
/*   Updated: 2024/12/05 22:31:06 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"


#include <stdio.h>
#include <stdlib.h>
size_t	ft_strlen(const char *str)
{
	size_t	a;

	a = 0;
	while (str[a])
		a++;
	return (a);
}




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
		i++;
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

int	meow(char *str)
{
	int i;
	int yay;
	
	i = -1;
	yay = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i] != '\0')
				i++;
			if (str[i] != '"')
				yay = 1;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\0')
				i++;
			if (str[i] != '\'')
				yay = 1;
		}
	}
	return (yay);
}


int main(void)
{
	char    *a = "wa\"dwa\"\"dawdaae\"ll";
	printf("%d\n", meow(a));
	// printf("%s\n", a);
	// printf("%c\n", '"');
	// printf("%c\n", '\'');
}