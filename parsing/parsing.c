/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:37:42 by lalwafi           #+#    #+#             */
/*   Updated: 2024/12/02 22:55:00 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell shell;
	
	(void)av;
	if (ac != 1)
		return (printf("'./minishell' only, no arguments\n"));
	init_all(&shell);
	// change_shlvl();
	get_env(&shell, env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	minishell(&shell);
	free_all(&shell);
}

void	init_all(t_shell *shell)
{
	
}

