/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:49:04 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/05 00:16:38 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	operator_tokens(t_shell *shell, t_command *cmds , int i)
{
	char *cmp = " <>|";
	t_direct	*temp;
	int			start;

	// printf("=======OPERATORS======\n");
	start = i;
	// printf("rn on = #%c#, i = %d\n", cmds->cmd_line_L[i], i);
	temp = malloc(sizeof(t_direct));
	if (!temp)
		(write(2, "malloc fail\n", 12), free_all(shell), exit(EXIT_FAILURE));
	temp->direct = operators_check(cmds->cmd_line_L, i);
	// print_enum(temp->direct);
	if (temp->direct == HERE_DOC || temp->direct == APPEND)
		i += 2;
	else if (temp->direct == RE_INPUT || temp->direct == RE_OUTPUT)
		i++;
	while (cmds->cmd_line_L[i] == ' ')
		i++;
	if (ft_strchr(cmp, cmds->cmd_line_L[i]) != NULL)
		shell->parse_fail_L = 1;
	temp->file = copy_file(cmds->cmd_line_L, i, cmds, start);
	if (temp->file == NULL)
		shell->parse_fail_L = 1;
	cmds->num_of_redir += 1;
	temp->next = NULL;
	ft_lstadd_back_redir(&cmds->redir, temp);
	// printf("=======OPERATORS======\n");
}

char	*copy_file(char *str, int i, t_command *cmds, int start) // MAKE IT FAIL IF NO FILE NAME i took care in operator tokens i think
{
	int		len;
	char	*result;
	char *cmp = " <>|";
	len = 0;
	
	// printf("copy_file char = #%c# , i+len = %d\n", str[i + len], i + len);
	while (str[i + len] != '\0' && ft_strchr(cmp, str[i + len]) == NULL)
	{
		if (str[i + len] == '\'' || str[i + len] == '\"')
			len = skip_quotes(str, i + len) - i;
		else
			len++;
	}
	// printf("copy_file char = #%c# , i+len = %d\n", str[i + len], i + len);
	if (len == 0)
		return (NULL);
	// printf("before cmdline = #%s#\n", cmds->cmd_line_L);
	result = rmv_quotes(ft_substr(str, i, len));
	// if (str[i + len] == ' ')
	// 	len++;
	cmds->cmd_line_L = string_but_string(cmds->cmd_line_L, ft_strdup(""), start, len + i - start);
	// printf("        result = #%s#\n      cmd_line = #%s#\n", result, cmds->cmd_line_L);
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




// minishell> echo hello> " file"
// #echo hello> " file"#
// ------------------------------ i = 0
// ------------------------------ i = 1
// ------------------------------ i = 1
// ------------------------------ i = 2
// ------------------------------ i = 2
// ------------------------------ i = 3
// ------------------------------ i = 3
// ------------------------------ i = 4
// ------------------------------ i = 4
// BEFORE   words = ##
//       cmd_line = #echo hello> " file"#
// AFTER    words = #echo #
//       cmd_line = #hello> " file"#
// ------------------------------ i = 0
// ------------------------------ i = 0
// ------------------------------ i = 1
// ------------------------------ i = 1
// ------------------------------ i = 2
// ------------------------------ i = 2
// ------------------------------ i = 3
// ------------------------------ i = 3
// ------------------------------ i = 4
// ------------------------------ i = 4
// ------------------------------ i = 5
// ------------------------------ i = 5
// in operators
// =======OPERATORS======
// rn on = #>#
// copy_file char = #"# , i+len = 7
// copy_file char = ## , i+len = 14
// before cmdline = #hello> " file"#
//         result = #" file"#
//        cmd_line = ##
// =======OPERATORS======
// ------------------------------ i = 0