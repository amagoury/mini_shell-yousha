/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_stuff_v2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:11:55 by lalwafi           #+#    #+#             */
/*   Updated: 2025/02/25 19:15:47 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// echo  he"llo' $USER frie"nd > fi"le  he'l"l.txt$MEOW
// echo  he"llo' lalwafi frie"nd > fi"le  he'l"l.txt$MEOW

// echo '$USER' ha
// echo lalwafi ha

char	*expand_them_vars(char *str, t_environment *env, t_shell *shell)
{
	// locate $
	// find end of variable name
	//		if starts with number, only one char and thats it, same with ?
	//		if starts with letter or '_' , numbers letters and '_' are valid, anything else nah
	//		otherwise its just another word to keep 
	//		(eg: "$-USER" -> "$-USER") , ("$USER" -> "lalwafi") , ("$1USER" , "USER")
	int i;   // itterate
	int len; // length of variable starting $
	char *var;

	i = -1;
	while (str[++i]) // oops handle single quotes
	{
		if (str[i] == '\'')
			i = skip_quotes(str, i) - 1;
		else if (str[i] == '$')
		{
			i++;
			len = 1; //probably should add 1 cuz '$' i did nvm
			if (str[i] == '?')
				var = ft_itoa(shell->exit_code);
			else if (ft_isdigit(str[i]) == 1)
				var = return_var(str, i, 1, env);
			else if (ft_isalpha(str[i]) || str[i] == '_')
			{
				len = 0;
				while (str[i + len] != '\0' && (ft_isalpha(str[i + len]) || 
					str[i + len] == '_' || ft_isdigit(str[i + len]) == 1))
					len++;
				len = return_var_length_temp(str, i, len, env);
				var = return_var(str, i, len, env);
			}
			// len = ft_strlen(var);
			// printf("var = %s, len = %ld\n", var, ft_strlen(var));
			str = string_but_string(str,var,--i,len + 1);
			i--;
		}
	}
	return (str);
}

char	*string_but_string(char *pushed, char *pusher, int start, int rmv)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(sizeof(char) * (ft_strlen(pushed) + ft_strlen(pusher) - rmv + 1));
	if (!result)
	{
		printf("string_but_string\n");
		return (NULL);
	}
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
	free(pushed);
	free(pusher);
	return (result);
}

char	*return_var(char *str, int start, int len, t_environment *env)
{
	t_values *temp;
	char *var;
	int i;

	var = ft_substr(str, start, len);
	if (!var)
		return (ft_strdup(""));
	// printf("var = #%s#\n", var);
	i = 0;
	temp = env->vals;
	while (temp->next != NULL)
	{
		// printf("current key = #%s#\n", temp->key);
		if (ft_strlen(temp->key) >= ft_strlen(var))
			i = ft_strlen(var);
		else
			i = ft_strlen(temp->key);
		if (ft_strncmp_lyall(temp->key, var, i) == 0)
			return (free(var), ft_strdup(temp->value));
		temp = temp->next;
	}
	free(var);
	return (ft_strdup(""));
}


int	return_var_length_temp(char *str, int start, int len, t_environment *env) // temporary fix change later
{
	t_values *temp;
	char *var;
	int i;

	var = ft_substr(str, start, len);
	if (!var)
		return (0);
	// printf("var = #%s#\n", var);
	i = 0;
	temp = env->vals;
	while (temp->next != NULL)
	{
		// printf("current key = #%s#\n", temp->key);
		if (ft_strlen(temp->key) >= ft_strlen(var))
			i = ft_strlen(var);
		else
			i = ft_strlen(temp->key);
		if (ft_strncmp_lyall(temp->key, var, i) == 0)
		{
			len = ft_strlen(temp->key);
			return (len);
		}
		temp = temp->next;
	}
	free(var);
	return (0);
}
// locate the $
// count length while checking if a valid name
// put into function that checks if it exists and return it otherwise return ""
// 