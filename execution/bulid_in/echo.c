/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:30:37 by aishamagour       #+#    #+#             */
/*   Updated: 2025/02/21 19:45:28 by amagoury         ###   ########.fr       */
=======
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:30:37 by aishamagour       #+#    #+#             */
/*   Updated: 2025/02/14 15:54:43 by aishamagour      ###   ########.fr       */
>>>>>>> e3c04689e87eb0d88ac830579b35e40b4e79eebd
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


static char is_n(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

<<<<<<< HEAD
int my_echo(char **command,t_command *cmd)
=======
void my_echo(char **command,t_command *cmd)
>>>>>>> e3c04689e87eb0d88ac830579b35e40b4e79eebd
{
	(void)cmd;
	int i;
	int j;
	bool flag;
	flag = false;
	i = 1;
	while(command[i] && command[i][0] == '-' && command[i][1] == 'n')
	{
		if(is_n(command[i]) == 0)
			flag = true;
		i++;
	}
	while(command[i])
	{
		j = 0;
		while(command[i][j])
		{
			write(1, &command[i][j], 1);
			j++;
		}
		if(command[i + 1])
			write(1, " ", 1);
		i++;
	}
	if(!flag)
		write(1, "\n", 1);
<<<<<<< HEAD
	return(0);
=======
>>>>>>> e3c04689e87eb0d88ac830579b35e40b4e79eebd
}
//  int main()
//  {
// 	 char *command[] = {"echo", "-n", "hello", "world", NULL};
// 	 my_echo(command, NULL);
// 	 return 0;
//  }