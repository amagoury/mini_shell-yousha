/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:39:51 by aishamagour       #+#    #+#             */
/*   Updated: 2025/02/26 18:35:06 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void final_exec(t_command *cmd,t_environment *path, int cmd_cnt)
{
	int fd[2];
	int i = -1;
	pid_t last_pid;
	pid_t pid;
	// int run_bulidin;
	// print_commands(cmd);
	while(++i < cmd_cnt)
	{
		if(pipe(fd) == -1)
			exit(1);
		pid = fork();
		if(pid == 0)
		{
			printf("hi child\n");
			close(fd[0]);
			dup2(fd[1],STDOUT_FILENO);
			close(fd[1]);
			if(is_bulidin(cmd) == true && cmd_cnt > 1)
				cmd->save_statues = run_bulidin(cmd, path);
			else if(is_bulidin(cmd) ==  false && execve(cmd->cmd,cmd->cmd_args,path->path) == -1)
					exit(1);
			exit(0);
		}
		else
		{
			printf("hi parent\n");
			close(fd[1]);
			// dup2(fd[0],STDIN_FILENO);
			close(fd[0]);
			// printf("%s\n",cmd->cmd_args[0]);
			if(is_bulidin(cmd) == true &&cmd_cnt == 1)
				cmd->save_statues = run_bulidin(cmd, path);
		}
		last_pid = pid;
	}
	int kill_child = 0;
	int status;
	// kill_child = waitpid(&status);
	while(kill_child != -1)
	{
		kill_child = wait(&status);
		if(kill_child == last_pid)
			cmd->save_statues =WEXITSTATUS(status);
	}
	
}