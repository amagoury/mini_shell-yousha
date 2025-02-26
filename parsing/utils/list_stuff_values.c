/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_stuff_values.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:29:27 by lalwafi           #+#    #+#             */
/*   Updated: 2025/02/26 17:13:17 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_lstsize_v(t_values *lst)
{
	t_values	*current;
	int			count;

	count = 0;
	if (!lst)
		return (0);
	current = lst;
	while (current->next != NULL)
	{
		current = current->next;
		count++;
	}
	// printf("size  = %d\n", count);
	return (count);
}

t_values	*ft_lstlast_values(t_values *lst)
{
	t_values	*temp;
	// int		i;

	if (!lst)
		return (NULL);
	temp = lst;
	// i = ft_lstsize_v(temp);
	// printf("i = %d\n", i);
	while (temp->next)
	{
		temp = temp->next;
		// i--;
	}
	// printf("------- lstlastvalues key = %s\n", temp->key);
	return (temp);
}

void	ft_lstadd_back_values(t_values **lst, t_values *new)
{
	t_values	*last;

	if (*lst)
	{
		last = ft_lstlast_values(*lst);
		last->next = new;
		// printf("last = #%s#\nnew = #%s#\nnext node = %s\n\n", last->key, new->key, last->next->key);
	}
	else
	{
		*lst = new;
		// printf("edewdwedewdwedwdwdwelse\n");
	}
}

void	ft_lstclear_values(t_values *lst)
{
	t_values	*a;

	while (lst)
	{
		a = lst->next;
		// ft_lstdelone_values(lst);
		free(lst->key);
		free(lst);
		lst = a;
	}
	// lst = NULL;
}

void	ft_lstdelone_values(t_values *prev, t_values *del, t_values *nxt)
{
	prev->next = nxt;
	if (del)
	{
		free(del->key);
		// free(del->value);
		// free(del->envstr);
		free(del);
	}
}
