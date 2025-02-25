/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:14:19 by aishamagour       #+#    #+#             */
/*   Updated: 2025/02/25 20:17:10 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// Function to create a new node in the linked list
t_command *create_node(char *cmd) {
    t_command *new_node = (t_command *)malloc(sizeof(t_command));
    if (!new_node) {
        printf("malloc");
        exit(EXIT_FAILURE);
    }
    new_node->cmd = ft_strdup(cmd); // Duplicate the string
    new_node->next = NULL;
    return new_node;
}

// Function to add a node to the linked list
void add_node(t_command **head, char *cmd) {
    t_command *new_node = create_node(cmd);
    new_node->next = *head;
    *head = new_node;
}

// Your unset function
int my_unset(t_environment **head, char *args) {
    t_environment *tmp = *head;
    t_environment *prev = NULL;

    while (tmp) {
        if (strcmp(tmp->cmd, args) == 0) {
            if (prev) {
                prev->next = tmp->next;
            } else {
                *head = tmp->next;
            }
            free(tmp->cmd);
            free(tmp);
            return 1;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return(0);
}

// Function to print the linked list (for debugging)
void print_list(t_command *head) {
    t_command *tmp = head;
    while (tmp) {
        printf("%s\n", tmp->cmd);
        tmp = tmp->next;
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