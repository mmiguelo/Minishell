#include "minishell.h"

static void	init_pipe_data(t_shell *shell)
{
	int	count = count_pid(shell);

	shell->pid_nbr = malloc(sizeof(pid_t) * count);
	if (!shell->pid_nbr)
		perror("malloc failed");
}

static void	close_extra_fds(int in_fd, int fd[2])
{
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (fd)
	{
		close(fd[0]);
		close(fd[1]);
	}
}

static void	handle_execve_or_builtin(t_shell *shell, t_node *node)
{
	t_bt	builtin;
	char	*path;

	builtin = ft_isbuiltin(node->cmd, shell);
	if (builtin)
	{
		shell->exit_status = builtin(node->args, shell);
		ft_kill(&shell, shell->exit_status);
	}
	path = search_path(node->cmd, shell->envp, 0);
	if (!path)
	{
		ft_printf_fd(2, "command or PATH %s not found\n", node->cmd);
		ft_kill(&shell, 127);
	}
	if (execve(path, node->args, shell->envp) == -1)
	{
		perror(node->cmd);
		free_ref(&path);
		if (errno == ENOENT)
			ft_kill(&shell, 127);
		else if (errno == EACCES || errno == EISDIR)
			ft_kill(&shell, 126);
		else
			ft_kill(&shell, 1);
	}
}

static void	wait_all(t_shell *shell, int n)
{
	int	status;
	int	i;

	i = 0;
	while (i < n)
	{
		waitpid(shell->pid_nbr[i], &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		i++;
	}
	free(shell->pid_nbr);
	shell->pid_nbr = NULL;
	reset_dups(shell);
}

void	exec_multi_node(t_shell *shell, t_node *node)
{
	int	fds[2];
	int		in_fd = STDIN_FILENO;
	pid_t	pid;
	int		i = 0;

	init_pipe_data(shell);
	while (node)
	{
		if (node->next && pipe(fds) == -1)
			return (perror("pipe failed"));
		pid = fork();
		if (pid < 0)
			return (perror("fork failed"));
		if (pid == 0)
		{
			shell->is_child = TRUE;
			if (shell->fd[0] == STDIN_FILENO && in_fd != STDIN_FILENO)
				dup2(in_fd, STDIN_FILENO);
			if (node->next)
			{
				close(fds[0]);
				dup2(fds[1], STDOUT_FILENO);
				close(fds[1]);
			}
			if (exec_redir_handler(shell, node->redir, shell->fd) == ERROR)
				ft_kill(&shell, shell->exit_status);
			close_extra_fds(in_fd, fds);
			handle_execve_or_builtin(shell, node);
		}
		shell->pid_nbr[i++] = pid;
		if (in_fd != STDIN_FILENO) 
			close(in_fd);
		if (node->next)
		{
			close(fds[1]);
			in_fd = fds[0];
		}
		if (ft_isbuiltin(node->cmd, shell) && node->next
				&& !ft_isbuiltin(node->next->cmd, shell))
		{
			waitpid(shell->pid_nbr[i - 1], NULL, 0);
			i--;
		}
		node = node->next;
	}
	wait_all(shell, i);
}
