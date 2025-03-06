/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:37:16 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/03/06 19:37:16 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_process(char *eof, char *temp_path, t_shell *shell)
{
	int		status;
	int		temp_fd;

	set_heredoc_signals();
	while (1)
	{
		temp_fd = open(temp_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		status = fill_heredoc(temp_fd, eof);
		if (status == 1)
			printf("msh: warning: here-document delimited\n");
		close(temp_fd);
		free_all_heredoc(msh);
		if (status == 0 || status == 1)
			exit (0);
		else if (status == 2)
			exit(130);
	}
}