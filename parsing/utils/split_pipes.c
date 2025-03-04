/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:21:30 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/04 20:38:56 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//  echo ""
// echo m a m a
// echo "$USER"

char	**free_array(char **result) // see if neccessary to have char **
{
	int	i;

	i = 0;
	if (!result)
		return (NULL);
	while (result && result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
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
		if (s[i] == '\0')
			break;
		// if ((s[i - 1] != c && s[i] == c) || (s[i + 1] == '\0' && s[i] != c))
		// 	count++;
		if (s[i] == c)
			count++;
		i++;
	}
	count++;
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
		printf("1 s = %c , i = %d\n", s[i], i);
		if (s[i] == '"' || s[i] == '\'')
			i = skip_quotes(s, i);
		printf("2 s = %c , i = %d\n", s[i], i);
		while (s[i] == ' ' && s[i] != '\0')
			i++;
		printf("3 s = %c , i = %d\n", s[i], i);
		if (s[i] != c)
		{
			printf("making word 1 s = %c , i = %d , len+i = %d\n", s[i], i, i + len);
			while (s[i + len] != '\0' && s[i + len] != c)
			{
				if (s[i + len] == '"' || s[i + len] == '\'')
					len = skip_quotes(s, (i + len)) - i;
				else
					len++;
			}
			printf("making word 2 s = %c , i = %d , len+i = %d\n", s[i], i, i + len);
			while (s[i + len - 1] != c && s[i + len - 1] == ' ')
				len--;
			printf("making word 3 s = %c , i = %d , len+i = %d\n", s[i], i, i + len);
			result[counter] = ft_substr(s, i, len);
			if (!result[counter])
				return (free_array(result));
			printf("word = #%s#\n", result[counter]);
			i += len;
			len = 0;
			counter++;
		}
		else
			i++;
		printf("4 s = %c , i = %d\n", s[i], i);
	}
	result[counter] = NULL;
	return (result);
}

char	**one_word(char const *s, char **result)
{
	printf("in one word\n");
	result[0] = ft_strdup(s);
	result[1] = NULL;
	return(result);
}
char	**split_pipes(char const *s, char c)
{
	char	**result;
	int		count;

	count = make_words(s, c);
	result = ft_calloc(sizeof(char *), (count + 1));
	if (!result)
		return (NULL);
	if (count == 1)
		return (one_word(s, result));
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