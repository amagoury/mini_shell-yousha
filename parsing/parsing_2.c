/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:17:23 by lalwafi           #+#    #+#             */
/*   Updated: 2025/01/17 10:17:48 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_shlvl(t_values *vals, int lvl) // still not working properly dont use
{
	t_values *temp;
	t_values *node;

	temp = vals;
	node = NULL;
	while (temp->next && ft_strncmp_lyall(temp->key, "SHLVL", 5) != 0)
		temp = temp->next;
	if (ft_strncmp_lyall(temp->key, "SHLVL", 5) == 0)
		temp->value = ft_itoa(lvl); 
	else
	{
		node->key = malloc(sizeof(char) * 6);
		node->key = "SHLVL";
		node->value = ft_itoa(lvl);
		node->next = NULL;
		ft_lstadd_back_values(&vals, node);
	}
}

int	count_pipes(char *str)
{
	int	i;
	int	pipes;
	
	i = -1;
	pipes = 0;
	while (str[++i])
	{
		if (str[i] == '|')
			pipes++;
	}
	return (pipes);
}

// int	skip_white(char *str, int i)
// {
// 	if (str[i] == ' ')
// }

char	*rmv_extra_spaces(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		j++;
		if (str[i] == ' ')
			j++;
		while (str[i] == ' ')
			i++;
	}
	result = malloc(sizeof(char) + (j + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		result[j++] = str[i++];
		if (str[i] == ' ')
			result[j++] = str[i];;
		while (str[i] == ' ')
			i++;
	}
	result[j] = '\0';
	free(str);
	return (result);
}

int	open_quote_or_no(char *str)
{
	int	i;
	
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i] != '\0')
				i++;
			if (str[i] != '"')
				return (1);
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\0')
				i++;
			if (str[i] != '\'')
				return (1);
		}
	}
	return (0);
}

