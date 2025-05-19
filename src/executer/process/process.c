/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:27:28 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/02 12:27:28 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_redir(t_token *temp, t_node *node)
{
	t_redir	*redir;
	t_redir	*last;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return ;
	create_redir(redir);
	redir->filename = ft_strdup(temp->token);
	redir->type = temp->type;
	redir->next = NULL;
	if (!node->redir)
		node->redir = redir;
	else
	{
		last = node->redir;
		while (last->next)
			last = last->next;
		last->next = redir;
	}
}

t_token	*divide_process(t_token *temp, t_node *node)
{
	int	args_count;
	int	i;

	i = 0;
	args_count = count_args(temp);
	if (args_count)
	{
		node->args = (char **)malloc(sizeof(char *) * (args_count + 1));
		node->args[args_count] = NULL;
	}
	while (temp && temp->type != PIPE)
	{
		if (redirection_type(temp))
			save_redir(temp, node);
		else
			node->args[i++] = ft_strdup(temp->token);
		temp = temp->next;
	}
	if (temp)
	{
		node->next = (t_node *)malloc(sizeof(t_node));
		create_node(node->next);
	}
	return (temp);
}

t_node	*create_process(t_token *token_list)
{
	t_node	*node;
	t_token	*temp;
	t_node	*start;

	temp = token_list;
	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	create_node(node);
	start = node;
	while (temp)
	{
		temp = divide_process(temp, node);
		if (node->args && node->args[0])
			node->cmd = ft_strdup(node->args[0]);
		if (temp)
		{
			temp = temp->next;
			node = node->next;
		}
	}
	return (start);
}

int	build_process(t_shell *shell)
{
	shell->process = create_process(shell->token_list);
	if (!(shell->process))
	{
		free_loop(shell);
		return (ERROR);
	}
	if (heredoc_handler(shell) != SUCCESS)
	{
		free_loop(shell);
		return (ERROR);
	}
	return (SUCCESS);
}
