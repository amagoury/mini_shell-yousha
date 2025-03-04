#include "minishell.h"

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
		printf("------------------------------ i = %d\n", i);
		if (ctemp->cmd_line_L[i] == '\"' || 
			ctemp->cmd_line_L[i] == '\'')
		{
			printf("in quotes\n");
			i = skip_quotes(ctemp->cmd_line_L, i);
			printf("i = %d\n", i);
		}
		if (ctemp->cmd_line_L[i] == '>' ||
			ctemp->cmd_line_L[i] == '<')
		{
			printf("in operators\n");
			operator_tokens(ctemp, i);
			i = 0;
		}
		else if (i > 0 && (ctemp->cmd_line_L[i] == ' ' || ctemp->cmd_line_L[i] == '\0' || ctemp->cmd_line_L[i + 1] == '\0'))
		{
			printf("BEFORE   words = #%s#\n      cmd_line = #%s#\n", words, ctemp->cmd_line_L);
			words = ft_strjoin_free(words, ft_substr(ctemp->cmd_line_L, 0, i + 1), 3); // make sure it frees
			ctemp->cmd_line_L = ft_substr_free(ctemp->cmd_line_L, i + 1, \
				ft_strlen(ctemp->cmd_line_L + 2));
			printf("AFTER    words = #%s#\n      cmd_line = #%s#\n", words, ctemp->cmd_line_L);
			i = 0;
		}
		else 
			i++;
		printf("------------------------------ i = %d\n", i);
	}
	cut = ft_strtrim_free(rmv_extra_spaces(words), " ");
	ctemp->cmd_args = split_pipes(cut, ' ');  // REMOVE SPEECH MARKSSSS!!!
	free(cut);
	ctemp->next = NULL;
	// print_commands(shell->commands);
	// print_commands(ctemp);
	// printf("<%p>\n", shell->commands);
	i = -1;
	while (ctemp->cmd_args[++i])
		ctemp->cmd_args[i] = rmv_quotes(ctemp->cmd_args[i]);
	ft_lstadd_back_cmds(&shell->commands, ctemp);
	// print_commands(shell->commands);
	// free(words);
}