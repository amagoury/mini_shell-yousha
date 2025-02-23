// void	operator_tokens(t_command *cmds , int i)
// {
// 	printf("rn on = #%c#\n", cmds->cmd_line_L[i]);
// 	cmds->redir->direct = operators_check(cmds->cmd_line_L, i);
// 	while (cmds->cmd_line_L[i] == '>' || 
// 			cmds->cmd_line_L[i] == '<' || 
// 			cmds->cmd_line_L[i] == ' ')
// 		i++;
// 	cmds->redir->file = copy_file(cmds->cmd_line_L, i, cmds);
// }

// char	*copy_file(char *str, int i, t_command *cmds) // MAKE IT FAIL IF NO FILE NAME
// {
// 	int		len;
// 	char	*result;

// 	len = 0;
// 	while (str[i + len] != '\0' && str[i + len] != ' ')
// 	{
// 		if (str[i + len] == '\'' || str[i + len] == '\"')
// 			len = skip_quotes(str, i + len) - i;
// 		else
// 			len++;
// 	}
// 	printf("copy_file rn on = #%c#\n", str[i + len]);
// 	if (len == 0)
// 		printf("len shouldnt be 0\n");
// 	result = ft_substr(str, i, len);
// 	cmds->cmd_line_L = string_but_string(cmds->cmd_line_L, ft_strdup(""), 0, i + len);
// 	return (result);
// }

// t_state	operators_check(char *str, int i)    // integrate quotes!!! tokenize_it should handle nvm
// {
// 	char *cmp = " <>|$";
// 	int		j;

// 	j = i;
// 	if ((str[j] == '>' && str[j + 1] == '<') ||
// 		(str[j] == '<' && str[j + 1] == '>'))
// 		return (-1);
// 	if ((str[j] == '>' && str[j + 1] == '>') ||
// 		(str[j] == '<' && str[j + 1] == '<'))
// 		j++;
// 	j++;
// 	while (str[j] != '\0' && str[j] == ' ')
// 		j++;
// 	if (str[j] == '\0')
// 		return (-1);
// 	printf("char on rn %c\n", str[j]);
// 	if (ft_strchr(cmp, str[j]) == NULL)
// 	{
// 		if (str[i] == '<' && str[i + 1] != '<')
// 			return (RE_INPUT);
// 		else if (str[i] == '<' && str[i + 1] == '<')
// 			return (HERE_DOC);
// 		else if (str[i] == '>' && str[i + 1] != '>')
// 			return (RE_OUTPUT);
// 		else if (str[i] == '>' && str[i + 1] == '>')
// 			return (APPEND);
// 	}
// 	return (-1);
// }