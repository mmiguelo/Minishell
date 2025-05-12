/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:46:34 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/02 17:48:07 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_nodes(t_node *node)
{
	int		i;
	t_redir	*redir;
	int		index;

	index = 1;
	while (node)
	{
		printf("=== PROCESSO %d ===\n", index++);
		if (node->cmd)
			printf("CMD: %s\n", node->cmd);
		else
			printf("CMD: (null)\n");
		printf("ARGS: ");
		if (node->args)
		{
			i = 0;
			while (node->args[i])
			{
				printf("[%s] ", node->args[i]);
				i++;
			}
			printf("\n");
		}
		else
			printf("(null)\n");
		printf("REDIRECIONAMENTOS:\n");
		redir = node->redir;
		while (redir)
		{
			printf(" - [%d] %s\n", redir->type, redir->filename);
			redir = redir->next;
		}
		node = node->next;
		printf("\n");
	}
}
