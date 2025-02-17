/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:17:23 by lalwafi           #+#    #+#             */
/*   Updated: 2025/02/17 19:16:01 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	change_shlvl(t_values *vals, int lvl) // still not working properly dont use
// {
// 	t_values *temp;
// 	t_values *node;

// 	temp = vals;
// 	node = NULL;
// 	while (temp->next && ft_strncmp_lyall(temp->key, "SHLVL", 5) != 0)
// 		temp = temp->next;
// 	if (ft_strncmp_lyall(temp->key, "SHLVL", 5) == 0)
// 		temp->value = ft_itoa(lvl); 
// 	else
// 	{
// 		node->key = malloc(sizeof(char) * 6);
// 		node->key = "SHLVL";
// 		node->value = ft_itoa(lvl);
// 		node->next = NULL;
// 		ft_lstadd_back_values(&vals, node);
// 	}
// }

int	count_pipes(char *str)
{
	int	i;
	int	pipes;
	
	i = -1;
	pipes = 0;
	while (str[++i])
	{
		if (str[i] == '|')
			pipes++;
	}
	return (pipes);
}


int	skip_quotes(const char *str, int i)
{
	char quote;

	if (str[i] == '"' || str[i] == '\'')
	{
		quote = str[i++];
		while (str[i] != '\0' && str[i] != quote)
			i++;
		if (str[i] == quote)
			i++;
	}
	return (i);
	
	// if (str[i] == '"')
	// {
	// 	i++;
	// 	while (str[i] != '\0' && str[i] != '"')
	// 		i++;
	// }
	// else if (str[i] == '\'')
	// {
	// 	i++;
	// 	while (str[i] != '\0' && str[i] != '\'')
	// 		i++;
	// }
	// return (i);
}

char	*rmv_extra_spaces(char *str)
{
	char	*result;
	int		i;
	int		j;
	int		quote;

	i = -1;
	j = 0;
	while (str[++i])
		printf("i = %d , char = %c\n", i, str[i]);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			j += skip_quotes(str, i) - i;
			i = skip_quotes(str, i);
		}
			j++;
		if (str[i] == ' ')
		{
			while (str[i] == ' ' && str[i] != '\0')
				i++;
		}
		else
			i++;
	}
	printf("j = %d\n", j);
	result = malloc(sizeof(char) * (j + 2));
	if (!result)
	return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		printf("what char on 1 = %c\n", str[i]);
		quote = skip_quotes(str, i) - i;
		while (quote > 0 && str[i + 1] != '\0')
		{
			printf("in quote, i = %d , j = %d , char = %c\n", i, j, str[i]);
			result[j++] = str[i++];
			quote--;
		}
		if (str[i] == '\0')
			break ;
		printf("what char on 22222 = %c\n", str[i]);
		result[j] = str[i];
		if (str[i] != '\0' && str[i + 1] != '\0' && str[i++] == ' ')
		{
			printf("what char on 3333333333 = %c\n", str[i]);
			result[j++] = str[i];
			while (str[i] == ' ' && str[i] != '\0')
				i++;
		}
		else
			j++;
		if (str[i] != '\0' && str[i + 1] == '\0')
			result[j] = str[i++];
		printf("i = %d\n", i);
		printf("j = %d\n", j);
	}
	result[j] = '\0';
	free(str);
	return (result);
}


// int main(void)
// {
// 	char *a= "echo    hello   \" my   friend   \"";
// 	char *result;
// 	result = rmv_extra_spaces(a);
// 	printf("#%s#\n", result);
// 	free(result);
// }







int	open_quote_or_no(char *str)
{
	int	i;
	
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i] != '\0')
				i++;
			if (str[i] != '"')
				return (1);
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\0')
				i++;
			if (str[i] != '\'')
				return (1);
		}
	}
	return (0);
}

//         echo    hello   " my   friend   " a
//         echo    hello   " my   friend   "a
//         echo    hello   " my   friend   "     a