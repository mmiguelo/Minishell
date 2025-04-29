/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:24:21 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/04/29 17:02:07 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	handle_pipe(t_shell *shell, t_pipe *node)
{
	int		pipefd[2];
	pid_t	pid_node;
	pid_t	pid_shell;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	parse_exec_or_pipe(t_shell *shell, t_node *node)
{
	if (node->type == PIPE)
		handle_pipe(shell, (t_pipe *)node);
	else
		handle_exec(shell, (t_exec *)node);
} */
