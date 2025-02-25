/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:56:21 by aishamagour       #+#    #+#             */
/*   Updated: 2025/02/25 21:36:52 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// echo hel"lo    $USERaaa loll"lll > file.txt >hel"lo world.t"xt   |    '  echo     $USERRR jasjnkad    sss    ' | cat    -eeee  
// echo hello>"file    .txt" haha
// echo he"l'lo w'orld"'' > fi"l'e   '.t"xt

void    tokenize_it(t_shell *shell, char *str)
{
	// shell->pipe_split_L into shell.commands.cmd_line_L
	// tokenize, parse, and expand variables at the same time
	// for now probably spread to structs
	int		i;
	// int		len;
	char	*words;
	t_command	*ctemp;
	
	i = 0;
	// len = 0;
	
	ctemp = initialize_commands();
	ctemp->cmd_line_L = str;
	words = ft_strdup("");
	if (!ctemp->cmd_line_L)
		printf("failed cmd_line_L ft_strdup\n");
	while (ctemp->cmd_line_L[i])
	{
		printf("------------------------------ i = %d\n", i);
		if (ctemp->cmd_line_L[i] == '\"' || 
			ctemp->cmd_line_L[i] == '\'')
		{
			printf("in quotes\n");
			i = skip_quotes(ctemp->cmd_line_L, i);
			// if " worry about variables then keep all of it as one word
			// if ' just blindly copy all of it as one word
			// variable expansion is already handled just skip quotes
		}
		if (ctemp->cmd_line_L[i] == '>' ||
			ctemp->cmd_line_L[i] == '<')
		{
			printf("in operators\n");
			operator_tokens(ctemp, i);
			// copy the string too into redir and set next to null... deal with it idk
			// substr the rest away
			i = 0;
		}
		else if (i > 0 && (ctemp->cmd_line_L[i] == ' ' || ctemp->cmd_line_L[i] == '\0' || ctemp->cmd_line_L[i + 1] == '\0'))
		{
			// finish the word and substr it then restart???
			// idk figure it out how the i count is gonna look like
			// ctemp->cmd_args
			printf("BEFORE   words = #%s#\n      cmd_line = #%s#\n", words, ctemp->cmd_line_L);
			words = ft_strjoin(words, ft_substr(ctemp->cmd_line_L, 0, i + 1));
			ctemp->cmd_line_L = ft_substr(ctemp->cmd_line_L, i + 1, \
				ft_strlen(ctemp->cmd_line_L + 2));
			printf("AFTER    words = #%s#\n      cmd_line = #%s#\n", words, ctemp->cmd_line_L);
			i = 0;
		}
		else 
			i++;
		printf("------------------------------ i = %d\n", i);
	}
	ctemp->cmd_args = split_pipes(ft_strtrim(rmv_extra_spaces(words), " "), ' ');  // REMOVE SPEECH MARKSSSS!!!
	ctemp->next = NULL;
	// print_commands(shell->commands);
	// print_commands(ctemp);
	// printf("<%p>\n", shell->commands);
	i = -1;
	while (ctemp->cmd_args[++i])
		ctemp->cmd_args[i] = rmv_quotes(ctemp->cmd_args[i]);
	ft_lstadd_back_cmds(&shell->commands, ctemp);
	print_commands(shell->commands);
	// free(words);
}

void	print_commands(t_command *cmds)
{
	if (cmds->cmd_line_L)
		printf("cmd_line = #%s#\n", cmds->cmd_line_L);
	if (cmds->cmd_args)
	{
		int i = -1;
		while (cmds->cmd_args[++i])
			printf("cmd_args[%d] = #%s#\n", i, cmds->cmd_args[i]);
	}
	printf("num_of_redir = %d\n", cmds->num_of_redir);
	t_direct *temp = cmds->redir;
	while (temp)
	{
		printf("node 1\n");
		printf("file = #");
		print_enum(temp->direct);
		printf(" %s#\n", temp->file);
		temp = temp->next;
	}
	
}


void	print_enum(t_state en)
{
	if (en == RE_INPUT)
		printf("direct = <");
	else if (en == RE_OUTPUT)
		printf("direct = >");
	else if (en == HERE_DOC)
		printf("direct = <<");
	else if (en == APPEND)
		printf("direct = >>");
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

