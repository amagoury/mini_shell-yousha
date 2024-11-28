/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:29:27 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/28 13:26:01 by lalwafi          ###   ########.fr       */
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
	while (current != NULL)
	{
		current = current->next;
		count++;
	}
	return (count);
}

t_values	*ft_lstlast_values(t_values *lst)
{
	int	i;

	if (!lst)
		return (NULL);
	i = ft_lstsize_v(lst);
	while (i > 1)
	{
		lst = lst -> next;
		i--;
	}
	return (lst);
}

void	ft_lstadd_back_values(t_values **lst, t_values *new)
{
	t_values	*last;

	last = ft_lstlast_values(*lst);
	if (*lst)
		last -> next = new;
	else
		*lst = new;
}






void	ft_lstclear_values(t_values **lst, void (*del)(void *))
{
	t_values	*a;

	while (*lst)
	{
		a = (*lst)->next;
		ft_lstdelone_values(*lst, del);
		*lst = a;
	}
	*lst = NULL;
}

void	ft_lstdelone_values(t_values *lst, void (*del)(void *))
{
	if (lst)
	{
		del(lst->key);
		// del(lst->value);
		del(lst->envstr);
		free(lst);
	}
}