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
		if (str[i] == '$')
		{
			i++;
			len = 1; //probably should add 1 cuz '$'
			if (str[i] == '?')
				var = ft_itoa(shell->exit_code);
			else if (ft_isdigit(str[i]) == 1)
				var = return_var(str, i, 1, env);
			else if (ft_isalpha(&str[i]) || str[i] == '_')
			{
				len = 0;
				while (str[i + len] != '\0' && (ft_isalpha(&str[i + len]) || 
					str[i + len] == '_' || ft_isdigit(str[i + len]) == 1))
					len++;
				var = return_var(str, i, len, env);
			}
			str = string_but_string(str,var,--i,len + 1);
			i--;
		}
	}
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
			i += rmv;
			rmv = -1;
			while (pusher[++rmv])
				result[j++] = pusher[rmv];
		}
		result[j++] = pushed[i];
	}
	result[j] = '\0';
	free(pushed);
	free(pusher);
	return (result);
}

char	*return_var(char *str, int start, int len, t_environment *env)
{
	char *var;
	int i;

	var = ft_substr(str, start, len);
	if (!var)
		return (ft_strdup(""));
	i = 0;
	while (env->vals->next != NULL)
	{
		if (ft_strlen(env->vals->key) >= ft_strlen(var))
			i = ft_strlen(var);
		else
			i = ft_strlen(env->vals->key);
		if (ft_strncmp_lyall(env->vals->key, var, i) == 0)
			return (free(var), ft_strdup(env->vals->value));
		env->vals = env->vals->next;
	}
	free(var);
	return (ft_strdup(""));
}

int main(void)
{

}


// locate the $
// count length while checking if a valid name
// put into function that checks if it exists and return it otherwise return ""
// 

// echo  he"llo' $USER frie"nd > fi"le  he'l"l.txt$MEOW
// echo  he"llo' lalwafi frie"nd > fi"le  he'l"l.txt$MEOW

// echo $USER ha
// echo lalwafi ha

// echo $abc$USER
// echo $USER