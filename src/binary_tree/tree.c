/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:45:20 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/04/24 13:45:20 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* t_node	*parse_redir(t_token **current)
{
	t_cmd	*node;

	while
} */

t_node	*parse_pipe(t_token **current)
{
	t_node	*node;

	node = parse_redir(current);
	if (node == NULL)
		return (NULL);
	if (*current && (*current)->type == PIPE)
	{
		*current = (*current)->next;
		node = create_pipe_node(node, parse_pipe(current));
		if (node == NULL)
			return (NULL);
	}
	return (node);
}

int	make_tree(t_shell *root)
{
	t_token	*current;

	current = root->token_list;
	root->tree = parse_pipe(&current);
	return (0);
}
