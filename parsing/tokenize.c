/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:56:21 by aishamagour       #+#    #+#             */
/*   Updated: 2024/12/05 02:05:26 by lalwafi          ###   ########.fr       */
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

char *get_str(char ** input,t_)























meow goodluck with tokenization