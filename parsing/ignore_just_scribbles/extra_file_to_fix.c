#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

char	*ft_remove_chunk(char *str, size_t start, size_t len)
{
	char	*result;
	size_t		i;
	size_t		j;

	i = -1;
	j = 0;
	if (len <= 0)
		return (str);
	result = malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	if (!result)
		return (NULL);
	while (str[++i])
	{
		if (i == start && ft_strlen(str) >= (i + len))
			i += len;
		result[j++] = str[i];
	}
	result[j] = '\0';
	free(str);
	return (result);
}


char	*rmv_invalid_vars(char *str, char **keys)
{
	char	*var;
	char	*cmp = " \n\t\f\v\r<>|$";
	size_t		i;
	size_t		j;
	size_t		flag;

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
			var = malloc(j - i + 1);
			if (!var)
				return (NULL);
			ft_strlcpy(var, &str[i + 1], j - i + 1);
			printf("var = #%s#\n", var);
			int k = 0;
			while (keys[k] != NULL)
			{
				if (ft_strlen(keys[k]) >= ft_strlen(var))
					j = ft_strlen(var);
				else
					j = ft_strlen(keys[k]);
				if (ft_strncmp_lyall(keys[k], var, j) == 0)
					flag = 1;
				k++;
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


int main(void)
{
	// char *a = "$USERecho  he\"llo' $USER frie\"nd > fi\"le  he'l\"l.txt$MEO\tW";
	// expand_vars(a);

	char *b = "echo $usss $USER lol";
	char *keys[4] = {"USER" , "SHELL" , "PATH" , "ENV"};
	char *result;
	result = rmv_invalid_vars(b, keys);
	printf("result = %s\n", result);
	free(result);
}
