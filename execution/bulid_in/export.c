/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:45:26 by aishamagour       #+#    #+#             */
/*   Updated: 2025/03/04 21:43:16 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*ft_strjoin_free_a(char *s1, const char *s2)
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
	new_value = ft_strjoin_free_a(ft_strdup(value), "\"");
	new_value = ft_strjoin_free_a(new_value, equal_sign + 1);
	new_value = ft_strjoin_free_a(new_value, "\"");
	return (new_value);
}

void	print_env(t_values *env, bool export) //
{
	int i;
    char *quoted_value;

    (void)export;
    if (!env)
        return;
    i = 0;
    while (env) // iterate through the t_values LIST
    {
        // if (export)
        // {
            ft_putstr_fd("declare -x ", 1);
            ft_putstr_fd(env->key, 1);
            ft_putstr_fd("=",1);
            quoted_value = add_quotes(env->value);
            ft_putendl_fd(quoted_value, 1);
            free(quoted_value);
        // }
        // else
        //     ft_putendl_fd(env, 1);
        env= env->next;
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

char    *value_time(char *str)
{
    int i;
    int j;
    char    *value;
    i = 0;
    j = 0;
    while (str[i] != '=')
        i++;
    i++;
    while (str[i + j])
        j++;
    value = ft_calloc(sizeof(char), (j + 1));
    j = 0;
    while (str[i + j])
    {
        value[j] = str[j + i];
        j++;
    }
    return (value);
}


void    add_to_env_export(char *new, t_values *vals)
{
    char     *key;
    char     *value;
    t_values    *temp;

    temp = malloc(sizeof(t_values));
	if (!temp)
		printf("issue in make values node\n");
	temp->key = key_time(new);
	temp->value = value_time(new);
	temp->next = NULL;
	ft_lstadd_back_values(&vals, temp);}

bool ft_export(t_context *cntx, t_values *env)
{
    int i;

    if (!cntx->args[1]) 
    {
        print_env(env, true);
        return (true);
    }
    i = 0;
    while (cntx->args[++i])
    {
        if (!is_valid_env(cntx->args[i]))
            return (false);
        else
            add_to_env_export(cntx->args[i], env);
        // ...existing code...
    }
    return (true);
}
