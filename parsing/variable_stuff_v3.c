/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_stuff_v3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:53:50 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 20:16:25 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_them_vars(char *str, t_environment *env, t_shell *shell)
{
	int i;   // itterate
	int len; // length of variable starting $
	char *var;

	i = -1;
	while (str[++i]) // oops handle single quotes HANDLED
	{
		if (str[i] == '\'')
			i = skip_quotes(str, i) - 1;
		else if (str[i] == '$')
		{
			if (str[i + 1] == '\0')
				break ;
			i++;
			len = 1; //probably should add 1 cuz '$'   i did nvm 
			if (str[i] == '?')
				var = ft_itoa(shell->exit_code);
			else if (ft_isdigit(str[i]) == 1)
				var = return_var(str, i, 1, env);
			else if (ft_isalpha(str[i]) || str[i] == '_')
			{
				len = 0;
				while (str[i + len] != '\0' && (ft_isalpha(str[i + len]) == 1|| 
					str[i + len] == '_' || ft_isdigit(str[i + len]) == 1))
					len++;
				// len = return_var_length_temp(str, i, len, env);
				var = return_var(str, i, len, env);
			}
			else
				len = 0;
			// len = ft_strlen(var);
			// printf("var = %s, len = %ld\n", var, ft_strlen(var));
			// printf("len = %d, i = %d\n", len, i);
			// if (str[i] != '\0' && (ft_isalpha(str[i]) == 1|| 
			// 	str[i] == '_' || ft_isdigit(str[i]) == 1))
			if (len > 0)
			{
				str = string_but_string(str,var,--i,len + 1);
				if (str == NULL)
					(write(2, "malloc fail\n", 12), free_all(shell), exit(EXIT_FAILURE));
			}
			i--;
		}
	}
	// printf("variable str = #%s#\n", str);
	return (str);
}

char	*string_but_string(char *pushed, char *pusher, int start, int rmv)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(sizeof(char) * (ft_strlen(pushed) + ft_strlen(pusher) - rmv + 1));
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	while (pushed[++i])
	{
		if (i == start)
		{
			i += rmv - 1;
			rmv = -1;
			while (pusher[++rmv])
				result[j++] = pusher[rmv];
		}
		else
			result[j++] = pushed[i];
	}
	result[j] = '\0';
	if (pushed)
		free(pushed);
	if (pusher)
		free(pusher);
	return (result);
}

char	*return_var(char *str, int start, int len, t_environment *env)
{
	t_values *temp;
	char *var;

	var = ft_substr(str, start, len);
	if (!var)
		return (ft_strdup(""));
	// printf("var = #%s#\n", var);
	temp = env->vals;
	while (temp)
	{
		// printf("current key = #%s#\n", temp->key);
		if (ft_strcmp_l(temp->key, var) == 0)
			return (free(var), ft_strdup(temp->value));
		temp = temp->next;
	}
	free(var);
	return (ft_strdup(""));
}
