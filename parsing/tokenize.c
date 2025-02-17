/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:56:21 by aishamagour       #+#    #+#             */
/*   Updated: 2025/02/16 19:17:03 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    tokenize_it(t_shell *shell)
{
	
}

int set_token(t_token *token, char **input, char *quote) {
	token->str = NULL;
	token->blockers = " \n\t\f\v\r<>|$";
	token->s_block = '\'';
	token->dupl_block = "\"$";
	token->len = 0;
	token->convert = 0;
	token->quote = '\0';
	if (**input == '\'')
	{
		token->quote = '\'';
		token->blockers = token->s_block;
	}
	else if (**input == '\"')
	{
		token->quote = '\"';
		token->blockers = token->dupl_block;
	}
	if (token->quote != '\0')
	{
		(*input)++;
		if (**input == token->quote)
		{
			(*input)++;
			return 1;
		}
	}
	return 0;
}

char	*expand_vars(char *str)
{
	char	*result;
	char	*cmp = " \n\t\f\v\r<>|$";
	int		i;
	int		j;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			j = i;
			while (ft_strchr(cmp, str[j]) == NULL)
				j++;
			
		}
	}
}

