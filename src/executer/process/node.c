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

void	create_node(t_node *node)
{
	node->cmd = NULL;
	node->args = NULL;
	node->next = NULL;
	node->redir = NULL;
}

void	create_redir(t_redir *redir)
{
	redir->filename = NULL;
	redir->type = 0;
	redir->next = NULL;
}
