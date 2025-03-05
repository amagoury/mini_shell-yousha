/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_v2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:56:21 by aishamagour       #+#    #+#             */
/*   Updated: 2025/03/06 02:55:50 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tokenize_it(t_shell *shell, char *str)
{
	int			i;
	char		*words;
	char		*cut;
	t_command	*ctemp;

	i = 0;
	ctemp = initialize_commands();
	ctemp->cmd_line_L = ft_strdup(str);
	words = ft_strdup("");
	if (!ctemp->cmd_line_L)
		(free_all(shell), \
		write(2, "Error: malloc fail\n", 19), exit(EXIT_FAILURE));
	while (ctemp->cmd_line_L[i])
	{
		if (ctemp->cmd_line_L[i] == '\"' || \
			ctemp->cmd_line_L[i] == '\'')
		{
			i = skip_quotes(ctemp->cmd_line_L, i);
			if (ctemp->cmd_line_L[i] == '\0')
			{
				words = ft_strjoin_free(words, \
					ft_substr(ctemp->cmd_line_L, 0, i), 3);
				ctemp->cmd_line_L = ft_substr_free(ctemp->cmd_line_L, i, \
					ft_strlen(ctemp->cmd_line_L + 2));
				i = 0;
			}
		}
		else if (ctemp->cmd_line_L[i] == '>' || \
			ctemp->cmd_line_L[i] == '<')
		{
			operator_tokens(shell, ctemp, i);
			i = 0;
		}
		else if (i > 0 && (ctemp->cmd_line_L[i] == ' ' || \
			ctemp->cmd_line_L[i] == '\0' || \
			ctemp->cmd_line_L[i + 1] == '\0'))
		{
			words = ft_strjoin_free(words, \
				ft_substr(ctemp->cmd_line_L, 0, i + 1), 3);
			ctemp->cmd_line_L = ft_substr_free(ctemp->cmd_line_L, i + 1, \
				ft_strlen(ctemp->cmd_line_L + 2));
			i = 0;
		}
		else
			i++;
	}
	if (ctemp->cmd_line_L[i] == '\0' && i > 0)
	{
		words = ft_strjoin_free(words, ft_substr(ctemp->cmd_line_L, 0, i), 3);
		ctemp->cmd_line_L = ft_substr_free(ctemp->cmd_line_L, i, \
			ft_strlen(ctemp->cmd_line_L + 1));
		i = 0;
	}
	cut = ft_strtrim_free(rmv_extra_spaces(words), " ");
	ctemp->cmd_args = split_pipes(cut, ' ');
	free(cut);
	ctemp->next = NULL;
	i = -1;
	while (ctemp->cmd_args[++i])
		ctemp->cmd_args[i] = rmv_quotes(ctemp->cmd_args[i]);
	ft_lstadd_back_cmds(&shell->commands, ctemp);
}

// void	print_commands(t_command *cmds)
// {
// 	t_command	*ctemp;
// 	t_direct	*temp;
// 	int			i;

// 	ctemp = cmds;
// 	i = 0;
// 	while (ctemp)
// 	{
// 		printf("----- commands %i -----\n", i++);
// 		if (ctemp->cmd_line_L)
// 			printf("cmd_line = #%s#\n", ctemp->cmd_line_L);
// 		if (ctemp->cmd_args)
// 		{
// 			i = -1;
// 			while (ctemp->cmd_args[++i])
// 				printf("cmd_args[%d] = #%s#\n", i, ctemp->cmd_args[i]);
// 		}
// 		printf("num_of_redir = %d\n", ctemp->num_of_redir);
// 		temp = ctemp->redir;
// 		while (temp)
// 		{
// 			print_enum(temp->direct);
// 			printf(" , file =  #%s#\n", temp->file);
// 			temp = temp->next;
// 		}
// 		ctemp = ctemp->next;
// 	}
// 	printf("-----------------------\n");
// }

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
