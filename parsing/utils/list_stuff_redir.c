/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_stuff_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:25:27 by lalwafi           #+#    #+#             */
/*   Updated: 2025/02/27 19:27:03 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_lstsize_redir(t_direct *lst)
{
	t_direct	*current;
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

t_direct	*ft_lstlast_redir(t_direct *lst)
{
	t_direct	*temp;
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
	// printf("------- lstlastcmds key = %s\n", temp->key);
	return (temp);
}

void	ft_lstadd_back_redir(t_direct **lst, t_direct *new)
{
	t_direct	*last;

	if (*lst)
	{
		last = ft_lstlast_redir(*lst);
		last->next = new;
		// printf("last = #%s#\nnew = #%s#\nnext node = %s\n\n", last->key, new->key, last->next->key);
	}
	else
	{
		*lst = new;
		// printf("edewdwedewdwedwdwdwelse\n");
	}
}

void	ft_lstclear_redir(t_direct *lst)
{
	t_direct	*a;

	while (lst)
	{
		a = lst->next;
		free(lst->file);
		free(lst);
		lst = a;
	}
	// lst = NULL;
}
