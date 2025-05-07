/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:50:48 by yes               #+#    #+#             */
/*   Updated: 2025/05/07 18:52:28 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	heredoc_readline(t_heredoc *hd)
{
	
} */

int	read_write_heredoc(t_heredoc *hd)
{
	char	*line;
	int		fd;
	
	set_signal_mode(SIGMODE_HEREDOC);
	fd = open(hd->hd_path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
	{
		ft_printf_fd(2, ERROR_HD_CREATE);
		set_signal_mode(SIGMODE_DEFAULT);
		return(ERROR);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || get_signo() == CTRL_C)
		{
			close(fd);
			set_signal_mode(SIGMODE_DEFAULT);
			if (!line)
				ft_printf_fd(2, "minishell: "ERROR_HD_EOF, hd->delimiter);
			return (ERROR);
		}
		if (ft_strcmp(line, hd->delimiter) == 0)
		{
			free(line);
			break;
		}
		ft_printf_fd(fd, "%s\n", line);
		free_ref(&line);
	}
	set_signal_mode(SIGMODE_DEFAULT);
	close(fd);
	return (SUCCESS);
}

int	create_heredoc(t_token *token, char *dir)
{
	t_heredoc	*hd;
	
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
				return (ERROR);
		}
		token = token ->next;
	}
	return (SUCCESS);
}