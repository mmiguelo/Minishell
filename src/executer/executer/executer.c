#include "minishell.h"

void	fork_single_node(t_shell *shell, t_node *node, char *path)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork failed"));
	if (pid == 0)
	{
		shell->is_child = TRUE;
		if (execve(path, node->args, shell->envp) == -1)
		{
			perror(node->cmd);
			restore_stdio(shell);
			free_ref(&path);
			if (errno == ENOENT)
				ft_kill(&shell, 127);
			else if (errno == EACCES || errno == EISDIR)
				ft_kill(&shell, 126);
			else
				ft_kill(&shell, 1);
		}
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
}

void	exec_single_node(t_shell *shell, t_node *node)
{
	t_bt	builtin;
	char	*path;

	if (backup_stdio(shell) == ERROR)
		return ;
	if (exec_redir_handler(shell, node->redir, shell->fd) == ERROR)
		return;
	builtin = ft_isbuiltin(node->cmd, shell);
	if (builtin)
	{
		shell->pid_nbr = NULL;
		builtin(node->args, shell);
		restore_stdio(shell);
		return ;
	}
	path = search_path(node->cmd, shell->envp, 0);
	if (!path)
	{
		ft_printf_fd(2, "command or PATH %s not found\n", node->cmd);
		shell->exit_status = 127;
		return ;
	}
	fork_single_node(shell, node, path);
	restore_stdio(shell);
	free_ref(&path);
}

void	execute_process(t_shell *shell)
{
	t_node	*node;

	node = shell->process;
	if (count_pid(shell) == 1)
		exec_single_node(shell, node);
	else
		exec_multi_node(shell, node);
}