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

/* t_node	*parse_exec(t_token **current)
{
	t_exec	*node;

	node = create_cmd_node();
	if (node == NULL)
		return (NULL);
	while (*current && (*current)->type != PIPE)
	{
		if ((*current)->type == CMD || (*current)->type == ARG)
		{
			if (insert_argv_node(node, (*current)->token) != 0)
				return (ft_lstclear(&node->argv, free), free(node), NULL);
		}
		else if (redirection_type(*current) == 0)
		{
			if (insert_redir_node(node, (*current)->token,
					(*current)->type) != 0)
				return (ft_lstclear(&node->argv, free), free(node), NULL);
		}
		*current = (*current)->next;
	}
	return ((t_node *)node);
}

t_node	*parse_pipe(t_token **current)
{
	t_node	*node;

	node = parse_exec(current);
	if (node == NULL)
		return (NULL);
	if (*current && (*current)->type == PIPE)
	{
		node = (t_node *)create_pipe_node(node, parse_pipe(&(*current)->next));
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
	if (root->tree == NULL)
		free_tokens(&root->token_list);
	ft_printf("root value is %d\n", root->tree->type);
	if (((t_pipe *)root->tree)->left)
		ft_printf("level 1: descendatnt is %d\n", ((t_pipe *)root->tree)->left->type);
	if (((t_pipe *)root->tree)->right)
		ft_printf("Level 1: Right descendant is %d\n", ((t_pipe *)root->tree)->right->type);
	if (((t_pipe *)((t_pipe *)root->tree)->left)->left)
		ft_printf("Level 2: Left left descendant is %d\n", ((t_pipe *)((t_pipe *)root->tree)->left)->left->type);
	if (((t_pipe *)((t_pipe *)root->tree)->left)->right)
		ft_printf("Level 2: left Right descendant is %d\n", ((t_pipe *)((t_pipe *)root->tree)->left)->right->type);
	if (((t_pipe *)((t_pipe *)root->tree)->right)->left)
		ft_printf("Level 2: right Left descendant is %d\n", ((t_pipe *)((t_pipe *)root->tree)->right)->left->type);
	if (((t_pipe *)((t_pipe *)root->tree)->right)->left)
		ft_printf("Level 3: right Left descendant is %d\n", ((t_pipe *)((t_pipe *)root->tree)->right)->left->type);
	if (((t_pipe *)((t_pipe *)root->tree)->right)->right)
		ft_printf("Level 3: righjt Right descendant is %d\n", ((t_pipe *)((t_pipe *)root->tree)->right)->right->type); 
	return (0);
} */
