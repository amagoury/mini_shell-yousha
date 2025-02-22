/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_stuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:05:41 by lalwafi           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/20 00:17:23 by lalwafi          ###   ########.fr       */
=======
/*   Updated: 2025/02/21 21:10:59 by lalwafi          ###   ########.fr       */
>>>>>>> e3c04689e87eb0d88ac830579b35e40b4e79eebd
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
<<<<<<< HEAD
	char	*cmp = " <>|$";
=======
	char	*cmp = " <>|$-";
>>>>>>> e3c04689e87eb0d88ac830579b35e40b4e79eebd
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
<<<<<<< HEAD
	free(str);
=======
	// free(str);
>>>>>>> e3c04689e87eb0d88ac830579b35e40b4e79eebd
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
