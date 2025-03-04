/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:14:19 by aishamagour       #+#    #+#             */
/*   Updated: 2025/03/04 21:44:19 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int my_unset(t_values **head, char *args) 
{
    t_values  *tmp;
    t_values    *prev;
    
    tmp = *head;
    while (tmp && tmp->next) {
        if (strcmp(tmp->key, args) == 0)
        {
            printf("FOUND KEY\n");
            ft_lstdelone_values(prev, tmp, tmp->next);
            break ;
        }
        prev = tmp;
        tmp= tmp->next;
    }
    
    return(0);
}

// Function to print the linked list (for debugging)
void print_list(t_environment *head)
{
   t_environment*tmp = head;
    while (tmp)
    {
        printf("%s\n", tmp->vals->key);
        tmp->vals = tmp->vals->next;
    }
}
