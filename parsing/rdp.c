/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 02:32:53 by lalwafi           #+#    #+#             */
/*   Updated: 2024/12/06 18:19:49 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_it(t_shell *shell)
{
	pipe_split();
	split_it(shell);
	
}

void	pipe_split(t_shell shell)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (shell.input_L[++i] != '\0')
	{
		if (shell.input_L[i] == '|')
			len++;
		
	}
}

void	split_it(t_shell *shell)
{
	// ' '  '\n'  '\t'  '\f'  '\v'  '\r'
	// '|'  '$'  ';'  '\''  '"'  '\\'  ''' '('  ')'  '&'  '*'
	// '<'  '>'  '<<'  '>>' 
	
}

int	open_quote_or_no(char *str)
{
	int	i;
	int	yay;
	
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