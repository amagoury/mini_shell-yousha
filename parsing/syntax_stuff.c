/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:16:42 by lalwafi           #+#    #+#             */
/*   Updated: 2025/01/22 19:44:55 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_syntax_errors(char *input)
{
	int	i;
	int	j;

	i = -1;
	j = ft_strlen(input) - 1;
	if (input[0] == '|' || input[j] == '|')
		return (1);
	while (input[++i])
	{
		if (input[i] == '|' && (input[i + 1] == '|' || input[i + 2] == '|'))
			return (1);
	}
	return (0);
}

// 