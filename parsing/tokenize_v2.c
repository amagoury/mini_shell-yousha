/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_v2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:56:21 by aishamagour       #+#    #+#             */
/*   Updated: 2025/03/05 00:17:21 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// echo hel"lo    $USERaaa loll"lll > file.txt >hel"lo world.t"xt   |    '  echo     $USERRR jasjnkad    sss    ' | cat    -eeee  
// echo hello>"file    .txt" haha
// echo he"l'lo w'orld"'' > fi"l'e   '.t"xt
// >tes"ting ""| test"
// a"e"a"e"''a''
void    tokenize_it(t_shell *shell, char *str)
{
	int		i;
	char	*words;
	char	*cut;
	t_command	*ctemp;

	i = 0;
	ctemp = initialize_commands();
	ctemp->cmd_line_L = ft_strdup(str);
	words = ft_strdup("");
	if (!ctemp->cmd_line_L)
		(free_all(shell), write(2, "Error: malloc fail\n", 19), exit(EXIT_FAILURE));
	while (ctemp->cmd_line_L[i])
	{
		// printf("------------------------------ i = %d\n", i);
		if (ctemp->cmd_line_L[i] == '\"' || 
			ctemp->cmd_line_L[i] == '\'')
		{
			// printf("in quotes\n");
			i = skip_quotes(ctemp->cmd_line_L, i);
			// printf("i = %d\n", i);
			if (ctemp->cmd_line_L[i] == '\0')
			{
				// printf("BEFORE   words = #%s#\n      cmd_line = #%s#\n", words, ctemp->cmd_line_L);
				words = ft_strjoin_free(words, ft_substr(ctemp->cmd_line_L, 0, i), 3); // make sure it frees
				ctemp->cmd_line_L = ft_substr_free(ctemp->cmd_line_L, i, \
					ft_strlen(ctemp->cmd_line_L + 2));
				// printf("AFTER    words = #%s#\n      cmd_line = #%s#\n", words, ctemp->cmd_line_L);
				i = 0;
			}
		}
		else if (ctemp->cmd_line_L[i] == '>' ||
			ctemp->cmd_line_L[i] == '<')
		{
			// printf("in operators\n");
			operator_tokens(shell, ctemp, i);
			i = 0;
		}
		else if (i > 0 && (ctemp->cmd_line_L[i] == ' ' || \
			ctemp->cmd_line_L[i] == '\0' || \
			ctemp->cmd_line_L[i + 1] == '\0'))
		{
			// printf("BEFORE   words = #%s#\n      cmd_line = #%s#\n", words, ctemp->cmd_line_L);
			words = ft_strjoin_free(words, ft_substr(ctemp->cmd_line_L, 0, i + 1), 3); // make sure it frees
			ctemp->cmd_line_L = ft_substr_free(ctemp->cmd_line_L, i + 1, \
				ft_strlen(ctemp->cmd_line_L + 2));
			// printf("AFTER    words = #%s#\n      cmd_line = #%s#\n", words, ctemp->cmd_line_L);
			i = 0;
		}
		else 
			i++;
		// printf("------------------------------ i = %d\n", i);
	}
	if (ctemp->cmd_line_L[i] == '\0' && i > 0)
	{
		// printf("BEFORE   words = #%s#\n      cmd_line = #%s#\n", words, ctemp->cmd_line_L);
		words = ft_strjoin_free(words, ft_substr(ctemp->cmd_line_L, 0, i), 3); // make sure it frees
		ctemp->cmd_line_L = ft_substr_free(ctemp->cmd_line_L, i, \
			ft_strlen(ctemp->cmd_line_L + 1));
		// printf("AFTER    words = #%s#\n      cmd_line = #%s#\n", words, ctemp->cmd_line_L);
		i = 0;
	}
	// printf("before trim words = #%s#\n", words);
	cut = ft_strtrim_free(rmv_extra_spaces(words), " ");
	// printf("after trim words = #%s#\n", cut);
	ctemp->cmd_args = split_pipes(cut, ' ');  // REMOVE SPEECH MARKSSSS!!! done
	free(cut);
	ctemp->next = NULL;
	// print_commands(ctemp);
	// printf("<%p>\n", shell->commands);
	i = -1;
	while (ctemp->cmd_args[++i])
		ctemp->cmd_args[i] = rmv_quotes(ctemp->cmd_args[i]);
	ft_lstadd_back_cmds(&shell->commands, ctemp);
	// print_commands(shell->commands);
	// free(words);
}

void	print_commands(t_command *cmds)
{
	t_command	*ctemp = cmds;
	int			i;

	i = 0;
	while (ctemp)
	{
		printf("----- commands %i -----\n", i++);
		if (ctemp->cmd_line_L)
			printf("cmd_line = #%s#\n", ctemp->cmd_line_L);
		if (ctemp->cmd_args)
		{
			int i = -1;
			while (ctemp->cmd_args[++i])
				printf("cmd_args[%d] = #%s#\n", i, ctemp->cmd_args[i]);
		}
		printf("num_of_redir = %d\n", ctemp->num_of_redir);
		t_direct *temp = ctemp->redir;
		while (temp)
		{
			print_enum(temp->direct);
			printf(" , file =  #%s#\n", temp->file);
			temp = temp->next;
		}
		ctemp = ctemp->next;
	}
	printf("-----------------------\n");
}


void	print_enum(t_state en)
{
	if (en == RE_INPUT)
		printf("redirect = <");
	else if (en == RE_OUTPUT)
		printf("redirect = >");
	else if (en == HERE_DOC)
		printf("redirect = <<");
	else if (en == APPEND)
		printf("redirect = >>");
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

