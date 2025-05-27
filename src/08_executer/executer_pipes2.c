/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipes2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:24:02 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/27 13:24:02 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipe_data(t_shell *shell)
{
	int	count;

	count = count_pid(shell);
	shell->pid_nbr = malloc(sizeof(pid_t) * count);
	if (!shell->pid_nbr)
		perror("malloc failed");
}

void	close_extra_fds(int in_fd, int fd[2])
{
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (fd)
	{
		close(fd[0]);
		close(fd[1]);
	}
}

void	wait_all(t_shell *shell, int n)
{
	int	status;
	int	i;

	i = 0;
	while (i < n)
	{
		waitpid(shell->pid_nbr[i], &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			shell->exit_status = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGQUIT)
				ft_printf_fd(2, "Quit (core dumped)\n");
			else if (WTERMSIG(status) == SIGINT)
				ft_printf_fd(2, "\n");
		}
		i++;
	}
	free(shell->pid_nbr);
	shell->pid_nbr = NULL;
	reset_dups(shell);
}

void	execve_with_error_handling(char *path, t_node *node, t_shell *shell)
{
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

void	reset_dups(t_shell *shell)
{
	if (shell->fd[0] != STDIN_FILENO)
		dup2(shell->fd[0], STDIN_FILENO);
	if (shell->fd[1] != STDOUT_FILENO)
		dup2(shell->fd[1], STDOUT_FILENO);
}
