/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:56:21 by aishamagour       #+#    #+#             */
/*   Updated: 2025/02/19 02:36:54 by lalwafi          ###   ########.fr       */
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

char	*rmv_invalid_vars(char *str, t_environment *env)
{
	char	*var;
	char	*cmp = " \n\t\f\v\r<>|$";
	int		i;
	int		j;
	int		flag;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			i++; //ITS THE EXIT CODE IN SHELL->EXIT_CODE!!!!!
		else if (str[i] == '$')
		{
			flag = 0;
			j = i + 1;
			while (str[j] != '\0' && ft_strchr(cmp, str[j]) == NULL)
				j++;
			var = malloc(j - i);
			if (!var)
				return (NULL);
			ft_strlcpy(var, &str[i + 1], j - i);
			printf("var = #%s#\n", var);
			while (env->vals->next != NULL)
			{
				if (ft_strlen(env->vals->key) >= ft_strlen(var))
					j = ft_strlen(var);
				else
					j = ft_strlen(env->vals->key);
				if (ft_strncmp_lyall(env->vals->key, var, j) == 0)
					flag = 1;
				env->vals = env->vals->next;
			}
			if (flag == 0)
			{
				str = ft_remove_chunk(str, i, ft_strlen(var));
				i = 0;
			}
			free(var);
		}
	}
	return (str);
}

char	*ft_remove_chunk(char *str, int start, int len)
{
	char	*result;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (len <= 0)
		return (str);
	result = malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	if (!result)
		return (NULL);
	while (str[++i])
	{
		if (i == start)
			i += len;
		result[j++] = str[i];
	}
	result[j] = '\0';
	free(str);
	return (result);
}


// int main(void)
// {
// 	// char *a = "$USERecho  he\"llo' $USER frie\"nd > fi\"le  he'l\"l.txt$MEO\tW";
// 	// expand_vars(a);

// 	char *b = "echo $usss $USER lol";
// 	char *result;
// 	result = ft_remove_chunk(b, 5, 5);
// 	printf("result = %s\n", result);
// 	free(result);
// }
