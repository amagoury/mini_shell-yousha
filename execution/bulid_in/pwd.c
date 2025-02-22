/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:17:44 by aishamagour       #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/21 19:44:25 by amagoury         ###   ########.fr       */
=======
/*   Updated: 2025/02/14 15:54:09 by aishamagour      ###   ########.fr       */
>>>>>>> e3c04689e87eb0d88ac830579b35e40b4e79eebd
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

<<<<<<< HEAD
int 	ms_pwd(void)
=======
void	ms_pwd(void)
>>>>>>> e3c04689e87eb0d88ac830579b35e40b4e79eebd
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
<<<<<<< HEAD
	return(0);
=======
>>>>>>> e3c04689e87eb0d88ac830579b35e40b4e79eebd
}




