/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:57:21 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/27 16:57:24 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_readline(t_hd *hd, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (get_signo() == CTRL_C)
			return (free_ref(&line), ERROR);
		if (!line)
		{
			ft_printf_fd(2, "minishell: " ERROR_HD_EOF, hd->delimiter);
			return (free_ref(&line), SUCCESS);
		}
		if (ft_strcmp(line, hd->delimiter) == 0)
		{
			free_ref(&line);
			return (SUCCESS);
		}
		ft_printf_fd(fd, "%s\n", line);
		free_ref(&line);
	}
	return (SUCCESS);
}

int	read_write_heredoc(t_hd *hd)
{
	int	fd;

	fd = open(hd->hd_path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
	{
		ft_printf_fd(2, ERROR_HD_CREATE);
		return (ERROR);
	}
	set_signal_mode(SIGMODE_HEREDOC);
	if (heredoc_readline(hd, fd) != SUCCESS)
	{
		close(fd);
		set_signal_mode(SIGMODE_DEFAULT);
		return (ERROR);
	}
	close(fd);
	set_signal_mode(SIGMODE_DEFAULT);
	return (SUCCESS);
}

int	create_heredoc(t_shell *shell, t_redir *redir, char *dir)
{
	t_hd	*hd;

	hd = init_heredoc(redir);
	if (!hd)
		return (ft_printf_fd(2, ERROR_HD_CREATE), ERROR);
	hd->hd_path = generate_tempfile_path(dir, &shell->id);
	if (!hd->hd_path)
	{
		clean_heredoc(&hd);
		return (ft_printf_fd(2, ERROR_HD_GEN_PATH), ERROR);
	}
	if (read_write_heredoc(hd) != SUCCESS)
	{
		clean_heredoc(&hd);
		return (ERROR);
	}
	redir->heredoc = hd;
	return (SUCCESS);
}

int	heredoc_handler(t_shell *shell)
{
	t_node	*node;
	t_redir	*redir;

	node = shell->process;
	while (node)
	{
		redir = node->redir;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				if (create_heredoc(shell, redir, shell->tempfile_dir)
					!= SUCCESS)
				{
					if (get_signo() == CTRL_C)
						shell->exit_status = CTRL_C + 128;
					return (ERROR);
				}
			}
			redir = redir->next;
		}
		node = node->next;
	}
	return (SUCCESS);
}
