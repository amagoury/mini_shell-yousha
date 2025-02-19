/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:39:51 by aishamagour       #+#    #+#             */
/*   Updated: 2025/02/19 20:26:58 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void final_exec(t_command *cmd,t_environment *path)
{
	int fd[2];
	int i = -1;
	pid_t last_pid;
	pid_t pid;
	// int run_bulidin;
	while(++i < cmd)
	{
		if(pipe(fd) == -1)
			exit(1);
		pid = fork();
		if(pid == 0)
		{
			close(fd[0]);
			duo2(fd[1],STDOUT_FILENO);
			close(fd[1]);
			if(exec_bulidin(cmd) == 0)
				cmd->save_statues = run_bulidin(cmd);
			else if(execve(cmd->cmd,cmd->cmd_args,path) == -1)
					exit(1);
			exit(0);
		}
		else
		{
			close(fd[1]);
			duo2(fd[0],STDIN_FILENO);
			close(fd[0]);
			if(exec_bulidin(cmd) == 0)
				cmd->save_statues = run_bulidin(cmd);
		}
		last_pid = pid;
	}
	int kill_child = 0;
	int status;
	while(kill_child != -1)
	{
		kill_child = wait(&status);
		if(kill_child == last_pid)
			cmd->save_statues =WEXITSTATUS (status);
	}
	
}