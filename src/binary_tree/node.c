/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:00:03 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/04/24 14:00:03 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*create_redir_node(char *filename, int type)
{
	t_redir	*redir_node;

	redir_node = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!redir_node)
		return (NULL);
	redir_node->type = REDIR;
	redir_node->redir_file = filename;
	redir_node->redir_type = type;
	redir_node->next = NULL;
	return (redir_node);
}

t_cmd	*create_cmd_node(void)
{
	t_cmd	*cmd_node;

	cmd_node = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd_node)
		return (NULL);
	cmd_node->type = CMD;
	cmd_node->argv = NULL;
	cmd_node->redirs = NULL;
	return (cmd_node);
}

t_pipe	*create_pipe_node(t_node *left, t_node *right)
{
	t_pipe	*new_node;

	new_node = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
	if (!new_node)
		return (NULL);
	new_node->type = PIPE;
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}
