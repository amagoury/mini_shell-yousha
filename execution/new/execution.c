/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 21:11:32 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/05 17:13:52 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_context	*create_context()
{
	t_context	*context;

	context = malloc(sizeof(t_context));
	if (!context)
		return (NULL);
	context->args = NULL;
	context->cmd = NULL;
	context->inputfd = -1;
	context->outputfd = -1;
	context->error = 0;
	context->next = NULL;
	return (context);
}

void	safe_close(int fd)
{
	if (fd != -1)
		close(fd);
}

void	heredoc_signal(int signum)
{
	if (signum == SIGINT)
	{
		close(0);
		g_sig = signum;
	}
}

int	heredoc_child(int fds[2], char *delim, t_shell *shell)
{
	char	*str;

	signal(SIGINT, heredoc_signal);
	close(fds[0]);
	str = readline("heredoc> ");
	while (str && ft_strncmp(str, delim, -1) != 0)
	{
		str = expand_them_vars(str, shell->environment, shell);
		ft_putendl_fd(str, fds[1]);
		free(str);
		str = readline("heredoc> ");
	}
	close(fds[1]);
	if (g_sig != 0)
		return (1);
	return (0);
}

bool	handle_heredoc(t_context *context, char *delim, t_shell *shell)
{
	int	fds[2];
	int	pid;
	int	status;

	pipe(fds);
	pid = fork();
	// TODO handle failure
	if (pid == 0)
	{
		exit(heredoc_child(fds, delim, shell));
	}
	close(fds[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 1)
		return (close(fds[0]), false);
	safe_close(context->inputfd);
	context->inputfd = fds[0];
	return (true);
}

void	free_context(t_context *context)
{
	free(context->cmd);
	free_array(context->args);
	safe_close(context->inputfd);
	safe_close(context->outputfd);
	free(context);
}

t_context	*handle_heredocs(t_command *command, int inputfd, t_shell *shell)
{
	t_direct	*temp;
	t_context	*context;
	int			fds[2];

	context = create_context();
	context->inputfd = inputfd;
	temp = command->redir;
	while (temp)
	{
		if (temp->direct == HERE_DOC)
		{
			if (handle_heredoc(context, temp->file, shell) == FALSE)
				shell->exit_code = 1;
		}	// TODO handle failure
		temp = temp->next;
	}
	if (command->next)
	{
		pipe(fds);
		context->next = handle_heredocs(command->next, fds[0], shell);
		if (context->next == NULL)
			return (close(fds[0]), close(fds[1]), free_context(context), NULL);
		context->outputfd = fds[1];
	}
	return (context);
}

bool	find_heredoc_after(t_direct *direct)
{
	while (direct)
	{
		if (direct->direct == HERE_DOC)
			return (true);
		direct = direct->next;
	}
	return (false);
}

void	handle_input(t_context *context, char *file, bool ignore)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(file, 2);
		if (errno == EACCES)
			ft_putstr_fd(": Permission denied\n", 2);
		else
			ft_putstr_fd(": No such file or directory\n", 2);
		context->error = 1;
		return;
	}
	if (ignore)
	{
		close(fd);
		return;
	}
	safe_close(context->inputfd);
	context->inputfd = fd;
}


void	handle_output(t_context *context, char *file, bool append)
{
	safe_close(context->outputfd);
	if (append)
		context->outputfd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		context->outputfd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (context->outputfd == -1)
	{
		ft_putstr_fd(file, 2);
		if (errno == EACCES)
			ft_putstr_fd(": Permission denied\n", 2);
		else
			ft_putstr_fd(": No such file or directory\n", 2);
		context->error = 1;
		return;
	}
}

void	handle_redirects(t_context *context, t_command *command)
{
	t_direct	*temp;

	temp = command->redir;
	while (temp && context->error == 0)
	{
		if (temp->direct == RE_INPUT)
			handle_input(context, temp->file, find_heredoc_after(temp));
		if (temp->direct == RE_OUTPUT)
			handle_output(context, temp->file, false);
		if (temp->direct == APPEND)
			handle_output(context, temp->file, true);
		temp = temp->next;
	}
}

char	**copy_strs(char **strs)
{
	char	**new;
	int		i;

	i = 0;
	while (strs[i])
		i++;
	new = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (strs[i])
	{
		new[i] = ft_strdup(strs[i]);
		if (new[i] == NULL)
			return (free_array(new), NULL);
		i++;
	}
	return (new);	
}

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	while (*env && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	if (!*env)
		return (NULL);
	paths = ft_split(*env + 5, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin_free(ft_strjoin(paths[i], "/"), cmd, 1);
		if (!path)
			return (free_array(paths), NULL);
		if (access(path, X_OK) == 0)
			return (free_array(paths), path);
		free(path);
	}
	return (free_array(paths), NULL);
}

void	handle_everything(t_context *context, t_command *commands, char **env)
{
	context->args = copy_strs(commands->cmd_args);
	if (is_bulidin(commands->cmd_args[0]))
		context->cmd = ft_strdup(commands->cmd_args[0]);
	else if (commands->cmd_args[0] != NULL)
		context->cmd = find_path(commands->cmd_args[0], env);
	handle_redirects(context, commands);
	if (commands->next)
		handle_everything(context->next, commands->next, env);
}

void	free_context_list(t_context *context)
{
	t_context	*temp;

	while (context)
	{
		temp = context->next;
		free_context(context);
		context = temp;
	}
}

t_context	*create_context_list(t_command *commands, \
t_environment *env, t_shell *shell)
{
	t_context	*context;

	context = handle_heredocs(commands, -1, shell);
	// TODO handle failure
	handle_everything(context, commands, env->export_env);
	return context;
}

int	execute_command( t_shell *shell ,t_context *context, t_environment *env)
{
	if (context->next)
		free_context_list(context->next);
	context->next = NULL;
	if (context->error != 0)
		return (context->error);
	if (context->inputfd != -1)
	{
		// printf("her is the issue11\n");
		(dup2(context->inputfd, 0), close(context->inputfd));
		context->inputfd = -1;
	}
	if (context->outputfd != -1)
	{
		// printf("her is the issue22\n");
		(dup2(context->outputfd, 1), close(context->outputfd));
		context->outputfd = -1;
	}
	// if (context->cmd == NULL)
	// 	return (free_context(context), ft_putstr_fd("Command not found\n", 2), 127);
	if (context->cmd == NULL)
		return (127);
	if (is_bulidin(context->cmd))
		return(run_bulidin(shell, context, env));
    // printf("her is the issue\n");
	if (execve(context->cmd, context->args, env->export_env) == -1)
	{
		ft_putstr_fd(context->args[0], 2);
		ft_putstr_fd(": Error executing\n", 2);
	}
	else
		printf("buildin work\n");
	// TODO check error type and print appropriate msg
	return (127); //TODO Return with correct error msg
}

int	execute_context(t_shell *shell, t_context *context, t_environment *env)
{
	int			pid;
	t_context	*temp;
	int			status;

	while (context)
	{
		pid = fork();
		if (pid == 0)
		{
			status = execute_command(shell, context, env);
			free_all(shell);
			// TODO FREE SHELL ENV AND WHATEVER U NEED
			free_context_list(context);
			exit(status);
		}
		temp = context->next;
		free_context(context);
		context = temp;
	}
	return (pid);
}

void	execution(t_shell *shell, t_environment *env)
{
	t_context	*context;
	int			pid;
	int			status;

	context = create_context_list(shell->commands, env, shell);
	// TODO check error
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (context->next == NULL && is_bulidin(context->cmd))
	{
		shell->exit_code = exec_bulidin(shell, context, env);
		return ;
	}
	pid = execute_context(shell, context, env);
	signal(SIGINT, SIG_IGN);
	// waitpid(pid, &status, 0);
	while (wait(&status) != -1)
		;
	// TODO check if status is signaled
	shell->exit_code = WEXITSTATUS(status);
}
/*
	if error != 0, dont execute anything, free and exit with error code
	if cmd == NULL, then command not found free and exit with 127
*/
