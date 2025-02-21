/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:29:27 by lalwafi           #+#    #+#             */
/*   Updated: 2025/02/21 22:38:03 by lalwafi          ###   ########.fr       */
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
	return (count);
}

t_values	*ft_lstlast_values(t_values *lst)
{
	t_values	*temp;
	int		i;

	if (!lst)
		return (NULL);
	temp = lst;
	i = ft_lstsize_v(temp);
	while (i > 1)
	{
		temp = temp -> next;
		i--;
	}
	return (temp);
}

void	ft_lstadd_back_values(t_values **lst, t_values *new)
{
	t_values	*last;

	last = ft_lstlast_values(*lst);
	if (*lst)
		last -> next = new;
	else
		*lst = new;
	// printf("last = #%s#\nnew = #%s#\n\n", last->key, new->key);
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

void	ft_lstdelone_values(t_values *lst)
{
	if (lst)
	{
		free(lst->key);
		free(lst->value);
		// free(lst->envstr);
		free(lst);
	}
}
