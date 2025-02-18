// # include <stdio.h>
// # include <stdlib.h>
// # include <stdint.h>
// # include <unistd.h>
// # include <fcntl.h>
// # include <sys/wait.h>
// # include <sys/types.h>
// # include <signal.h>
// # include <string.h>

// int	skip_quotes(const char *str, int i)
// {
// 	char quote;

// 	if (str[i] == '"' || str[i] == '\'')
// 	{
// 		quote = str[i++];
// 		while (str[i] != '\0' && str[i] != quote)
// 			i++;
// 		if (str[i] == quote)
// 			i++;
// 	}
// 	return (i);
// }

// char	*rmv_extra_spaces(char *str)
// {
// 	char	*result;
// 	int		i;
// 	int		j;
// 	char	quote;

// 	i = -1;
// 	j = 0;
// 	while (str[++i])
// 		printf("i = %d , char = %c\n", i, str[i]);
// 	i = 0;
// 	printf("\n-------------\n\n");
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '\"' || str[i] == '\'')
// 		{
// 			printf("before skip quotes j = %d\n", j);
// 			j += skip_quotes(str, i) - i;
// 			printf("after skip quotes j = %d\n", j);
// 			printf("before skip quotes i = %d ,  char = %c\n", i, str[i]);
// 			i = skip_quotes(str, i);
// 			printf("after skip quotes i = %d ,  char = %c\n", i, str[i]);
// 		}
// 		else if (str[i] == ' ')
// 		{
// 			j++;
// 			while (str[i] != '\0' && str[i] == ' ')
// 				i++;
// 		}
// 		else
// 			j++, i++;
// 	}
// 	printf("\nsize of str = %ld\n", strlen(str));
// 	printf("final count j = %d\n", j);
// 	printf("final count i = %d\n", i);
// 	result = malloc(sizeof(char) * (j + 1));
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '\"' || str[i] == '\'')
// 		{
// 			quote = str[i];
// 			result[j++] = str[i++];
// 			while (str[i] != '\0' && str[i] != quote)
// 				result[j++] = str[i++];
// 			if (str[i] == quote)
// 				result[j++] = str[i++];
// 		}
// 		else if (str[i] == ' ')
// 		{
// 			result[j++] = str[i];
// 			while (str[i] != '\0' && str[i] == ' ')
// 				i++;
// 		}
// 		else
// 		result[j++] = str[i++];
// 	}
// 	result[j] = '\0';
// 	// free(str);
// 	printf("\nresult size = %ld , result = #%s#\n", strlen(result), result);
// 	printf("\nstr size    = %ld , str    = #%s#\n", strlen(str), str);
// 	return (result);
// }

// int main(void)
// {
// 	char *a = "echo    hello   \" my   friend   \"   a     hello9 birtch     \" wjat   tjhe fuck    \"";
// 	char *result;
// 	result = rmv_extra_spaces(a);
// 	printf("\nresult = #%s#\n", result);
// 	free(result);
// }
// // echo    hello   " my   friend   "   a     hello9 birtch     " wjat   tjhe fuck    "
// // i = 83  j = 68
// // echo hello " my   friend   " a hello9 birtch " wjat   tjhe fuck    "
// // echo hello " my   friend   " a hello9 birtch " wjat   tjhe fuck    "