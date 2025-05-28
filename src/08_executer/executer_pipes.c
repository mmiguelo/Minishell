/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:23:11 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/28 14:11:37 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	path = search_path(node->cmd, shell->envp);
	if (!path)
	{
		ft_printf_fd(2, "command or PATH '%s' not found\n", node->cmd);
		ft_kill(&shell, 127);
	}
	execve_with_error_handling(path, node, shell);
}

static pid_t	create_pipe_and_fork(t_node *node, int *fds)
{
	pid_t	pid;

	if (node->next && pipe(fds) == -1)
	{
		perror("pipe failed");
		return (-1);
	}
	pid = fork();
	if (pid < 0)
		perror("fork failed");
	return (pid);
}

static void	exec_child(t_shell *shell, t_node *node, int *fds, int in_fd)
{
	set_signal_mode(SIGMODE_CHILD);
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
	if (!node->cmd)
	{
		restore_stdio(shell);
		ft_kill(&shell, 0);
	}
	close_extra_fds(in_fd, fds);
	handle_execve_or_builtin(shell, node);
}

void	exec_multi_node(t_shell *shell, t_node *node, int i)
{
	int		fds[2];
	int		in_fd;
	pid_t	pid;

	i = 0;
	in_fd = STDIN_FILENO;
	init_pipe_data(shell);
	set_signal_mode(SIGMODE_PIPELINE);
	while (node)
	{
		pid = create_pipe_and_fork(node, fds);
		if (pid == 0)
			exec_child(shell, node, fds, in_fd);
		shell->pid_nbr[i++] = pid;
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (node->next)
		{
			close(fds[1]);
			in_fd = fds[0];
		}
		node = node->next;
	}
	wait_all(shell, i);
	set_signal_mode(SIGMODE_DEFAULT);
}
