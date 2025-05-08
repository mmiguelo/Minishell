/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:50:48 by yes               #+#    #+#             */
/*   Updated: 2025/05/08 18:34:24 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_readline(t_hd *hd, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || get_signo() == CTRL_C)
		{
			if (!line)
				ft_printf_fd(2, "minishell: " ERROR_HD_EOF, hd->delimiter);
			free_ref(&line);
			return (SUCCESS);
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

int	create_heredoc(t_token *token, char *dir)
{
	t_hd	*hd;

	hd = init_heredoc(token);
	if (!hd)
		return (ERROR);
	hd->hd_path = generate_tempfile_path(dir);
	if (!hd->hd_path)
	{
		clean_heredoc(&hd);
		return (ERROR);
	}
	if (read_write_heredoc(hd) != SUCCESS)
	{
		clean_heredoc(&hd);
		return (ERROR);
	}
	token->heredoc = hd;
	return (SUCCESS);
}

int	heredoc_handler(t_shell *shell)
{
	t_token	*token;

	token = shell->token_list;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			if (create_heredoc(token, shell->tempfile_dir) != SUCCESS)
			{
				if (get_signo() == CTRL_C)
					shell->exit_status = CTRL_C + 128;
				return (ERROR);
			}
		}
		token = token ->next;
	}
	return (SUCCESS);
}
