#include "minishell.h"

int	handle_child_pipes(t_shell *shell, int *fds, t_node *cmds)
{
	t_node	*begin;

	begin = NULL;
	shell->is_child = TRUE;
	if (!cmds->next)
	{
		dup2(shell->fd[1], STDOUT_FILENO);
		return (close(shell->fd[1]), 0);
	}
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	while (cmds->next && cmds->next->redir)
	{
		if (!begin)
			begin = cmds->next->redir;
		if (cmds->next->redir->type == REDIR_IN
				|| cmds->next->redir->type == HEREDOC)
			return (cmds->next->redir = begin, 0);
		cmds->next->redir = cmds->next->redir->next;
	}
	if (begin)
		cmds->next->redir = begin;
	close(fds[0]);
	return (0);
}


int	handle_pipes(t_shell *shell, t_node *process)
{
	int		i;
	int		fd[2];
	t_node	*cmds;

	cmds = process;
	i = 0;
	while (cmds)
	{
		pipe(fd);
		shell->pid_nbr[i] = fork();
		if (shell->pid_nbr[i++] != 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			cmds = cmds->next;
			signal(SIGINT, signal_default_handler);
			if (!cmds)
				return (dup2(shell->fd[0], STDIN_FILENO),
					close(shell->fd[1]), 1);
		}
		else
			return(handle_child_pipes(shell, fd, process));
	}
	return (0);
}
