#include "minishell.h"

int main(void)
{
	t_shell *shell;

	shell->commands->cmd = ft_strdup("echo");
	shell->commands->cmd_args = {"hello", "world"};
	
}