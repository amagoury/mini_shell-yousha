/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:48:03 by lalwafi           #+#    #+#             */
/*   Updated: 2025/02/27 19:53:33 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*rmv_quotes(char *str)
{
	bool	in_q;
	char	quote;
	char	*result;
	int		i;
	int		j;
	
	in_q = false;
	i = 0;
	j = count_rmv_quotes(str, 0, 0);
	result = malloc(sizeof(char) * (j + 1));
	if (!result)
		return (NULL);
	in_q = false;
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && in_q == false)
		{
			quote = str[i];
			in_q = true;
			i++;
		}
		else if ((str[i] == '\'' || str[i] == '\"') && in_q == TRUE && quote == str[i])
		{
			in_q = FALSE;
			i++;
		}
		if (str[i] && (in_q != TRUE || str[i] != quote))
			result[j++] = str[i++];
	}
	result[j] = '\0';
	free(str);
	return (result);
}

int	count_rmv_quotes(char *str , int i, int len)
{
	bool	in_q;
	char	quote;
	
	in_q = false;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && in_q == false)
		{
			quote = str[i];
			in_q = true;
			i++;
		}
		else if ((str[i] == '\'' || str[i] == '\"') && in_q == TRUE && quote == str[i])
		{
			in_q = FALSE;
			i++;
		}
		if (str[i] && (in_q != TRUE || str[i] != quote))
			len++, i++;
	}
	return (len);
}

// int main(void)
// {
// 	char *a = "   '' \"'\" hel\"lo ' '  worl\"d"      ;
// 	char *b;
// 	b = rmv_quotes(a);
// 	printf("a = #%s#\nb = #%s#\n", a, b);
// }

// he"ll'o world"