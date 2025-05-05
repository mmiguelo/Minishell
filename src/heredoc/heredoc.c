/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:50:48 by yes               #+#    #+#             */
/*   Updated: 2025/05/05 18:21:57 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* #include "minishell.h"

static int	get_next_heredoc_id(void)
{
	static int	id = 0;
	return (id++);
}

static char	*gen_tmpfile_path(void)
{
	char	*path;

	path = malloc(256);
	if (!path)
		return (NULL);
	snprintf(path, 256, "%s%d", HEREDOC_TMP_DIR, get_next_heredoc_id());
	return (path);
}

static int	write_line(int fd, char *line)
{
	write(fd, line, strlen(line));
	write(fd, "\n", 1);
	return (SUCCESS);
}

static int	read_input_loop(int fd, char *delimiter)
{
	char	*line;
	size_t	len;
	ssize_t	nread;

	line = NULL;
	len = 0;
	while (1)
	{
		write(1, "> ", 2);
		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break ;
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (strcmp(line, delimiter) == 0)
			break ;
		write_line(fd, line);
	}
	free(line);
	return (SUCCESS);
}

static int	create_heredoc(t_token *tok)
{
	t_heredoc	*heredoc;
	int			fd;

	heredoc = malloc(sizeof(t_heredoc));
	if (!heredoc)
		return (FAILURE);
	heredoc->delimiter = strdup(tok->next->token);
	heredoc->heredoc_path = gen_tmpfile_path();
	if (!heredoc->delimiter || !heredoc->heredoc_path)
		return (FAILURE);
	fd = open(heredoc->heredoc_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return (FAILURE);
	if (read_input_loop(fd, heredoc->delimiter) != SUCCESS)
	{
		close(fd);
		return (FAILURE);
	}
	close(fd);
	tok->heredoc = heredoc;
	return (SUCCESS);
}

int	heredoc_handler(t_shell *shell)
{
	t_token	*tok;

	tok = shell->input;
	while (tok)
	{
		if (tok->type == TOKEN_HEREDOC && tok->next && tok->next->token)
		{
			if (create_heredoc(tok) != SUCCESS)
				return (FAILURE);
		}
		tok = tok->next;
	}
	return (SUCCESS);
} */
