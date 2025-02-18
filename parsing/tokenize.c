/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:56:21 by aishamagour       #+#    #+#             */
/*   Updated: 2025/02/18 22:02:57 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void    tokenize_it(t_shell *shell)
// {
	
// }

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

void	expand_vars(char *str, t_environment *env)
{
	// char	*result;
	char	*var;
	char	*cmp = " \n\t\f\v\r<>|$";
	int		i;
	int		j;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				var = "?"; //ITS THE EXIT CODE IN SHELL->EXIT_CODE!!!!!
			j = i + 1;
			while (str[j] != '\0' && ft_strchr(cmp, str[j]) == NULL)
				j++;
			var = malloc(j - i);
			if (!var)
				return;
			ft_strlcpy(var, &str[i + 1], j - i);
			printf("var = #%s#\n", var);
			while (env->vals->next != NULL)
			{
				if (ft_strlen(env->vals->key) >= ft_strlen(var))
					j = ft_strlen(var);
				else
					j = ft_strlen(env->vals->key);
				if (ft_strncmp_lyall(env->vals->key, var, j) == 0)
					printf("var = %s matches key = %s\n", var, env->vals->key);
				else
					printf("var = %s doesn't match key = %s\n", var, env->vals->key);
				env->vals = env->vals->next;
			}
			free(var);
		}
	}
}

// int main(void)
// {
// 	char *a = "$USERecho  he\"llo' $USER frie\"nd > fi\"le  he'l\"l.txt$MEO\tW";
// 	expand_vars(a);
// }
