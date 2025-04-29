/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:03:56 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/04/26 17:03:56 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_type(t_token *token)
{
	if (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == APPEND || token->type == HEREDOC)
		return (1);
	return (0);
}

int	insert_argv_node(t_exec *node, char *content)
{
	char	*argv;
	t_list	*new_node;

	argv = ft_strdup(content);
	if (!argv)
		return (1);
	new_node = ft_lstnew(argv);
	if (!new_node)
	{
		free(argv);
		return (1);
	}
	ft_lstadd_back(&node->argv, new_node);
	return (0);
}

int	insert_redir_node(t_exec *node, char *filename, int type)
{
	char	*file;
	t_redir	*new_node;
	t_redir	*tmp;

	file = NULL;
	if (filename)
		file = ft_strdup(filename);
	if (!file)
		return (1);
	new_node = create_redir_node(file, type);
	if (!new_node)
	{
		free(file);
		return (1);
	}
	if (node->redirs == NULL)
		node->redirs = new_node;
	else
	{
		tmp = node->redirs;
		while (node->redirs->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return (0);
}
