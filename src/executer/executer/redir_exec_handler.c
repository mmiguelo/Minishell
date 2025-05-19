/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:37:30 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/19 19:04:13 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_redir_handle(t_shell *shell, t_redir *redir, int fd[2])
{
	int file;

	if (redir->type == REDIR_IN)
		file = open(redir->filename, O_RDONLY, 0600);
	else if (redir->type == HEREDOC)
	{
		ft_printf("redirecting from heredoc: %s\n", redir->heredoc->hd_path);
		file = open(redir->heredoc->hd_path, O_RDONLY, 0600);
	}
	else
		return (SUCCESS);
	if (file == -1)
	{
		ft_printf_fd(2, "Error: failed to open file\n");
		return ( shell->exit_status = 1, ERROR);
	}
	if (dup2(file, fd[0]) == -1)
	{
		ft_printf_fd(2, "Error: dup2 failed\n");
		shell->exit_status = 1;
		return (close(file), ERROR);
	}
	return (close (file), SUCCESS);
}

int	output_redir_handle(t_shell *shell, t_redir *redir, int fd[2])
{
	int file;

	if (redir->type == REDIR_OUT)
		file = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		file = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (SUCCESS);
	if (file == -1)
	{
		ft_printf_fd(2, "Error: failed to open file\n");
		return (shell->exit_status = 1, ERROR);
	}
	if (dup2(file, fd[1]) == -1)
	{
		ft_printf_fd(2, "Error: dup2 failed\n");
		shell->exit_status = 1;
		return (close(file), ERROR);
	}
	return (close (file), SUCCESS);
}

int	exec_redir_handler(t_shell *shell, t_redir *redir, int fd[2])
{
	while(redir)
	{
		if (redir->type == REDIR_IN || redir->type == HEREDOC)
		{
			if (input_redir_handle(shell, redir, fd) == ERROR)
				return (ERROR);
		}
		else if (redir->type == REDIR_OUT || redir->type == APPEND)
		{
			if (output_redir_handle(shell, redir, fd) == ERROR)
				return (ERROR);
		}
		redir = redir->next;
	}
	return (SUCCESS);
}