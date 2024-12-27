/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:21:30 by lalwafi           #+#    #+#             */
/*   Updated: 2024/12/27 15:32:23 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	skip_quotes(const char *str, int i)
{
	if (str[i] == '"')
	{
		i++;
		while (str[i] != '"')
			i++;
	}
	else if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'')
			i++;
	}
	return (i);
}

char	**free_array(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free (result[i]);
		i++;
	}
	free (result);
	return (NULL);
}

int	make_words(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 1;
	if (!*s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '"' || s[i] == '\'')
			i = skip_quotes(s, i);
		if ((s[i - 1] != c && s[i] == c) || (s[i + 1] == '\0' && s[i] != c))
			count++;
		i++;
	}
	return (count);
}

char	**make_letters(char **result, char const *s, char c, int count)
{
	int	i;
	int	counter;
	int	len;

	i = 0;
	counter = 0;
	len = 0;
	while (s[i] != '\0' && counter < count)
	{
		if (s[i] == '"' || s[i] == '\'')
			i = skip_quotes(s, i);
		if (s[i] != c)
		{
			while (s[i + len] != '\0' && s[i + len] != c)
			{
				if (s[i + len] == '"' || s[i + len] == '\'')
					len = skip_quotes(s, (i + len)) - i;
				len++;
			}
			result[counter] = ft_substr(s, i, len);
			if (!result[counter])
				return (free_array(result));
			i += len;
			len = 0;
			counter++;
		}
		else
			i++;
	}
	result[counter] = NULL;
	return (result);
}

char	**split_pipes(char const *s, char c)
{
	char	**result;
	int		count;

	count = make_words(s, c);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	return (make_letters(result, s, c, count));
}

// void	remove_spaces(t_shell *shell)
// {
// 	int	i;
// 	int	j;
// 	char **man;
// 	int	start;
// 	int	len;

// 	// remove spaces from pipe sides
// 	// remove closed quotes NO
// 	i = -1;
// 	j = 0;
// 	while (shell->pipe_split_L[++i])
// 	{
// 		if (j == 0 && shell->pipe_split_L[i][j] == ' ')
			
// 	}
// }


// int main(void)
// {
// 	const char *a = "echo hello > meow.txt my friend | echo hel\"lo my dear | i'm happy\" meow";
// 	char **split;
	
// 	split = split_pipes(a, '|');
// 	int i = -1;
// 	while (split[++i])
// 		printf("%s\n", split[i]);
// }