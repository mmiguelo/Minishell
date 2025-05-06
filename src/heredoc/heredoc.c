/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:50:48 by yes               #+#    #+#             */
/*   Updated: 2025/05/06 17:54:09 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_heredoc(t_token *token, char *dir)
{
	t_heredoc	*hd;
	//int			fd[2];
	
	hd = init_heredoc(token);
	if (!hd)
		return (ERROR);
	hd->hd_path = generate_tempfile_path(dir);
	if (!hd->hd_path)
		return (ERROR);
	ft_printf("HD_PATH: %s\n", hd->hd_path);
	ft_printf("WRITE HEREDOC\n");
	/* if (read_write_heredoc(hd) != SUCCESS)
		return (ERROR); */
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