/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:56:21 by aishamagour       #+#    #+#             */
/*   Updated: 2025/02/24 00:26:10 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// echo hel"lo    $USERaaa loll"lll > file.txt >hel"lo world.t"xt   |    '  echo     $USERRR jasjnkad    sss    ' | cat    -eeee  

void    tokenize_it(t_shell *shell)
{
	// shell->pipe_split_L into shell.commands.cmd_line_L
	// tokenize, parse, and expand variables at the same time
	// for now probably spread to structs
	int		i;
	// int		len;
	char	*words;
	
	i = 0;
	// len = 0;
	shell->commands->cmd_line_L = ft_strdup(shell->pipe_split_L[0]);
	words = ft_strdup("");
	if (!shell->commands->cmd_line_L)
		printf("failed cmd_line_L ft_strdup\n");
	while (shell->commands->cmd_line_L[i])
	{
		printf("------------------------------ i = %d\n", i);
		if (shell->commands->cmd_line_L[i] == '\"' || 
			shell->commands->cmd_line_L[i] == '\'')
		{
			printf("in quotes\n");
			i = skip_quotes(shell->commands->cmd_line_L, i);
			// if " worry about variables then keep all of it as one word
			// if ' just blindly copy all of it as one word
			// variable expansion is already handled just skip quotes
		}
		if (shell->commands->cmd_line_L[i] == '>' ||
			shell->commands->cmd_line_L[i] == '<')
		{
			printf("in operators\n");
			operator_tokens(shell->commands, i);
			// copy the string too into redir and set next to null... deal with it idk
			// substr the rest away
			i = 0;
		}
		else if (shell->commands->cmd_line_L[i] == ' ' || shell->commands->cmd_line_L[i] == '\0')
		{
			// finish the word and substr it then restart???
			// idk figure it out how the i count is gonna look like
			// shell->commands->cmd_args
			printf("BEFORE   words = #%s#\n      cmd_line = #%s#\n", words, shell->commands->cmd_line_L);
			words = ft_strjoin(words, ft_substr(shell->commands->cmd_line_L, 0, i + 1));
			shell->commands->cmd_line_L = ft_substr(shell->commands->cmd_line_L, i + 1, \
				ft_strlen(shell->commands->cmd_line_L + 2));
			printf("AFTER    words = #%s#\n      cmd_line = #%s#\n", words, shell->commands->cmd_line_L);
			i = 0;
		}
		else 
			i++;
		printf("------------------------------ i = %d\n", i);
	}
	shell->commands->cmd_args = split_pipes(rmv_extra_spaces(words), ' ');  // REMOVE SPEECH MARKSSSS!!!
	// free(words);
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

