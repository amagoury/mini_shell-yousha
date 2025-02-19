/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:56:21 by aishamagour       #+#    #+#             */
/*   Updated: 2025/02/19 22:39:12 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    tokenize_it(t_shell *shell)
{
	// shell->pipe_split_L into shell.commands.cmd_line_L
	// tokenize, parse, and expand variables at the same time
	// for now probably spread to structs
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	shell->commands->cmd_line_L = ft_strdup(shell->pipe_split_L[0]);
	if (!shell->commands->cmd_line_L)
		printf("failed cmd_line_L ft_strdup\n");
	// i = ft_strlen(shell->commands->cmd_line_L);
	// if (shell->commands->cmd_line_L[i] == '>' ||
	// 	shell->commands->cmd_line_L[i] == '<')
	// 	printf("parse fail: ends in operator\n");
	while (shell->commands->cmd_line_L[i])
	{
		if ((shell->commands->cmd_line_L[i] == '>' ||
			shell->commands->cmd_line_L[i] == '<') &&
			operators_check(shell->commands->cmd_line_L, i) != -1)
		{
			shell->commands->redir->direct = operators_check(shell->commands->cmd_line_L, i);
			// copy the string too into redir and set next to null... deal with it idk
			// substr the rest away
		}
		else if (shell->commands->cmd_line_L[i] == '$')
		{
			// expand the variable or remove if invalid
		}
		else if (shell->commands->cmd_line_L[i] == '\'' ||
				shell->commands->cmd_line_L[i] == '\"')
		{
			// if " worry about variables then keep all of it as one word
			// if ' just blindly copy all of it as one word
			in_quote = 1;
		}
		else if (shell->commands->cmd_line_L[i] == ' ')
		{
			// finish the word and substr it then restart???
			// idk figure it out how the i count is gonna look like
		}
		else 
			i++;
	}
}

int	operators_check(char *str, int i)
{
	char *cmp = " <>|$";
	int		j;

	j = i;
	if ((str[j] == '>' && str[j + 1] == '<') ||
		(str[j] == '<' && str[j + 1] == '>'))
		return (-1);
	if ((str[j] == '>' && str[j + 1] == '>') ||
		(str[j] == '<' && str[j + 1] == '<'))
		j++;
	j++;
	while (str[j] != '\0' && str[j] == ' ')
		j++;
	if (str[j] == '\0')
		return (-1);
	printf("char on rn %c\n", str[j]);
	if (ft_strchr(cmp, str[j]) == NULL)
	{
		if (str[i] == '<' && str[i + 1] != '<')
			return (RE_INPUT);
		else if (str[i] == '<' && str[i + 1] == '<')
			return (HERE_DOC);
		else if (str[i] == '>' && str[i + 1] != '>')
			return (RE_OUTPUT);
		else if (str[i] == '>' && str[i + 1] == '>')
			return (APPEND);
	}
	return (-1);
}









// int set_token(t_token *token, char **input, char *quote) {
// 	token->str = NULL;
// 	token->blockers = " \n\t\f\v\r<>|$";
// 	token->s_block = '\'';
// 	token->dupl_block = "\"$";
// 	token->len = 0;
// 	token->convert = 0;
// 	token->quote = '\0';
// 	if (**input == '\'')
// 	{
// 		token->quote = '\'';
// 		token->blockers = token->s_block;
// 	}
// 	else if (**input == '\"')
// 	{
// 		token->quote = '\"';
// 		token->blockers = token->dupl_block;
// 	}
// 	if (token->quote != '\0')
// 	{
// 		(*input)++;
// 		if (**input == token->quote)
// 		{
// 			(*input)++;
// 			return 1;
// 		}
// 	}
// 	return 0;
// }

