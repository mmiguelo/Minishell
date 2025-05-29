/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_single.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:22:46 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/29 13:24:19 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_single_builtin(t_shell *shell, t_node *node)
{
	t_bt	builtin;

	builtin = ft_isbuiltin(node->cmd, shell);
	if (!builtin)
		return (0);
	shell->pid_nbr = NULL;
	shell->exit_status = builtin(node->args, shell);
	restore_stdio(shell);
	return (1);
}

void	exec_single_node(t_shell *shell, t_node *node)
{
	char	*path;

	if (backup_stdio(shell) == ERROR)
		return ;
	if (exec_redir_handler(shell, node->redir, shell->fd) == ERROR)
		return (restore_stdio(shell));
	if (!node->cmd)
		return ((void)(shell->exit_status = 0), restore_stdio(shell));
	if (handle_single_builtin(shell, node))
		return ;
	path = search_path(node->cmd, shell->envp);
	if (!path)
		return (ft_printf_fd(2, "command or PATH '%s' not found\n", node->cmd),
			(void)(shell->exit_status = 127));
	set_signal_mode(SIGMODE_PIPELINE);
	fork_single_node(shell, node, path);
	set_signal_mode(SIGMODE_DEFAULT);
	restore_stdio(shell);
	free_ref(&path);
}

static void	handle_execve_failure(t_shell *shell, t_node *node, char *path)
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

static void	handle_exit_status(t_shell *shell, int status)
{
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
}

void	fork_single_node(t_shell *shell, t_node *node, char *path)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork failed"));
	if (pid == 0)
	{
		set_signal_mode(SIGMODE_CHILD);
		shell->is_child = TRUE;
		if (execve(path, node->args, shell->envp) == -1)
			handle_execve_failure(shell, node, path);
	}
	waitpid(pid, &status, 0);
	handle_exit_status(shell, status);
}
