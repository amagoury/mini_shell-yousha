/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:49:04 by lalwafi           #+#    #+#             */
/*   Updated: 2025/02/24 00:19:20 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	count_cmdline_words(char *str)
// {
// 	int	i;
// 	int	words;

// 	i = -1;
// 	if (!str)
// 		printf("this shouldnt happen\n");
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' || str[i] == '\"')
// 			i = skip_quotes(str, i);
// 		else if (str[i] == '>' || str[i] == '<')
// 		{
			
// 		}
// 	}
// }

void	operator_tokens(t_command *cmds , int i)
{
	char *cmp = " <>|$";

	printf("=======OPERATORS======\n");
	printf("rn on = #%c#\n", cmds->cmd_line_L[i]);
	cmds->redir = malloc(sizeof(t_direct));
	if (!cmds->redir)
		printf("redir allocation fail\n");
	cmds->redir->direct = operators_check(cmds->cmd_line_L, i);
	if (cmds->redir->direct == HERE_DOC || cmds->redir->direct == APPEND)
		i += 2;
	else if (cmds->redir->direct == RE_INPUT || cmds->redir->direct == RE_OUTPUT)
		i++;
	while (cmds->cmd_line_L[i] == ' ')
		i++;
	if (ft_strchr(cmp, cmds->cmd_line_L[i]) != NULL)
		printf("operators fail\n");
	cmds->redir->file = copy_file(cmds->cmd_line_L, i, cmds);
	cmds->num_of_redir++;
	printf("=======OPERATORS======\n");
}

char	*copy_file(char *str, int i, t_command *cmds) // MAKE IT FAIL IF NO FILE NAME
{
	int		len;
	char	*result;

	len = 0;
	
	printf("copy_file char = #%c# , i+len = %d\n", str[i + len], i + len);
	while (str[i + len] != '\0' && str[i + len] != ' ')
	{
		if (str[i + len] == '\'' || str[i + len] == '\"')
			len = skip_quotes(str, i + len) - i;
		else
			len++;
	}
	printf("copy_file char = #%c# , i+len = %d\n", str[i + len], i + len);
	if (len == 0)
	printf("len shouldnt be 0\n");
	printf("before cmdline = #%s#\n", cmds->cmd_line_L);
	result = ft_substr(str, i, len);
	if (str[i + len] == ' ')
		len++;
	cmds->cmd_line_L = string_but_string(cmds->cmd_line_L, ft_strdup(""), 0, i + len);
	printf("        result = #%s#\n       cmd_line = #%s#\n", result, cmds->cmd_line_L);
	return (result);
}



t_state	operators_check(char *str, int i)    // integrate quotes!!! tokenize_it should handle nvm
{
	if (str[i] == '<' && str[i + 1] == '<')
		return (HERE_DOC);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	else if (str[i] == '<' && str[i + 1] != '<')
		return (RE_INPUT);
	else
		return (RE_OUTPUT);
}
