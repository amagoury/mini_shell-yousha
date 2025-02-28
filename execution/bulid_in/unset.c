/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:14:19 by aishamagour       #+#    #+#             */
/*   Updated: 2025/02/28 20:31:22 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// Function to create a new node in the linked list
// t_values*create_node(char *cmd) {
//     t_values *new_node = (t_values*)malloc(sizeof(t_values));
//     if (!new_node) {
//         printf("malloc");
//         exit(EXIT_FAILURE);
//     }
//     new_node->next = ft_strdup(cmd); // Duplicate the string
//     new_node->next= NULL;
//     return new_node;
// }

// Function to add a node to the linked list
// void add_node(t_environment **head, char *cmd) {
//     t_environment *new_node = create_node(cmd);
//     new_node->next = *head;
//     *head = new_node;
// }

// Your unset function
int my_unset(t_values **head, char *args) 
{
    t_values  *tmp = *head;
    t_values    *prev;
    // t_values *prev = NULL;
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

// int main() {
//     t_command *unset = NULL; // Initialize the head of the linked list

//     // Add some nodes to the linked list
//     add_node(&unset, "VAR1=value1");
//     add_node(&unset, "VAR2=value2");
//     add_node(&unset, "VAR3=value3");

//     // Print the list before unsetting
//     printf("Before unset:\n");
//     print_list(unset);

//     // Unset a variable
//     my_unset(&unset, "VAR2");

//     // Print the list after unsetting
//     printf("\nAfter unset:\n");
//     print_list(unset);

//     // Free the remaining nodes in the list
//     while (unset) {
//         t_command *tmp = unset;
//         unset = unset->next;
//         free(tmp->cmd);
//         free(tmp);
//     }

//     return 0;
// }