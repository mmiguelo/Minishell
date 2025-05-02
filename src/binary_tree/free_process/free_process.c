/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:33:35 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/02 17:48:43 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(t_redir *redir)
{
	t_redir	*temp;

	while (redir)
	{
		temp = redir->next;
		if (redir->filename)
			free(redir->filename);
		free(redir);
		redir = temp;
	}
}

void	free_process(t_node *node)
{
	t_node	*temp;

	if (node)
	{
		while (node)
		{
			temp = node->next;
			if (node->args)
			{
				free_char_pp(node->args);
				node->args = NULL;
			}
			if (node->redir)
				free_redir(node->redir);
			free(node);
			node = temp;
		}
	}
}
