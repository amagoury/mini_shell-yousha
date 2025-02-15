/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:45:26 by aishamagour       #+#    #+#             */
/*   Updated: 2025/02/14 15:53:22 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

char  *add_quotes(char *value)
{
	char *equal_sign;
	char *new_value;
	
	equal_sign = ft_strchr(value, '=');
	// No '=' found, return a duplicate of the input
	if(!equal_sign)
		return (ft_strdup(value));
	if(*(equal_sign + 1)== '\"')
		return (ft_strdup(value));
	// Construct the new string with quotes
	new_value = ft_strjoin_free(ft_strdup(value), "\"");
	new_value = ft_strjoin_free(new_value, equal_sign + 1);
	new_value = ft_strjoin_free(new_value, "\"");
	return (new_value);
}

void	print_env(char  **env, bool export)
{
	int i;
    char *quoted_value;

    if (!env)
        return;

    i = 0;
    while (env[i])
    {
        if (export)
        {
            ft_putstr_fd("declare -x ", 1);
            quoted_value = add_quotes(env[i]);
            ft_putendl_fd(quoted_value, 1);
            free(quoted_value);
        }
        else
            ft_putendl_fd(env[i], 1);
        i++;
	}
}

int env_add(char *value, char ***env)
{
    char **new_env;
    int i;
    
    i = 0;
    while ((*env)[i])
        i++;
        
    new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
        return (0);
    
    i = 0;
    while ((*env)[i])
    {
        new_env[i] = ft_strdup((*env)[i]);
        if (!new_env[i])
            return (0);
        i++;
    }
    new_env[i] = ft_strdup(value);
    new_env[i + 1] = NULL;
    *env = new_env;
    return (1);
}

bool ft_export(t_command *cmd,  char **export_env)
{
    t_list *args;

    if (!cmd || !cmd->cmd_args|| !cmd->cmd_args[0])
        return (false);

    if (!cmd->cmd_args)
    {
        print_env(export_env, true);
        return (true);
    }

    args = *(cmd->cmd_args);
    while (args)
    {
        // Now is_valid_env is properly declared
        if (!is_valid_env((char *)args->content) || ft_strncmp(args->content, "=", 1) == 0)
            return (false);
            
        // ...existing code...
    }
    return (true);
}

// int main(void)
// {
// 	char **env;
// 	char **export_env;
// 	t_command *cmd;

// 	env = malloc(sizeof(char *) * 4);
// 	if (!env)
// 		return (1);
// 	env[0] = ft_strdup("VAR1=value1");
// 	env[1] = ft_strdup("VAR2=value2");
// 	env[2] = ft_strdup("VAR3=value3");
// 	env[3] = NULL;

// 	export_env = malloc(sizeof(char *) * 4);
// 	if (!export_env)
// 		return (1);
// 	export_env[0] = ft_strdup("VAR1=value1");
// 	export_env[1] = ft_strdup("VAR2=value2");
// 	export_env[2] = ft_strdup("VAR3=value3");
// 	export_env[3] = NULL;

// 	cmd = creat_command("export");
// 	add_command(&cmd, creat_command("VAR4=value4"));
// 	add_command(&cmd, creat_command("VAR5=value5"));
// 	add_command(&cmd, creat_command("VAR6=value6"));

// 	ft_export(cmd, &env, &export_env);

// 	return (0);
// }