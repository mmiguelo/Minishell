/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:00:24 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/04/29 13:56:29 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tree_node(t_node **node)
{
	t_redir	*redir;
	t_redir	*temp;

	if (!node || !*node)
		return ;
	if ((*node)->type == PIPE)
	{
		free_tree_node(&((t_pipe *)(*node))->left);
		free_tree_node(&((t_pipe *)(*node))->right);
		free(*node);
	}
	else if ((*node)->type == REDIR || (*node)->type == CMD)
	{
		ft_lstclear(&((t_exec *)(*node))->argv, free);
		redir = ((t_exec *)(*node))->redirs;
		while (redir)
		{
			temp = redir;
			redir = redir->next;
			free(temp->redir_file);
			free(temp);
		}
		free(*node);
	}
}
