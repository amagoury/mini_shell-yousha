/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:17:23 by lalwafi           #+#    #+#             */
/*   Updated: 2025/01/10 00:16:54 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_shlvl(t_values *vals, int lvl)
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

int	check_syntax_errors(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(input) - 1;
	while (input[i] == ' ')
		i++;
	while (input[j] == ' ')
		j--;
	if (input[i] == '|' || input[j] == '|')
		return (1);
	return (0);
}