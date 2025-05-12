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
				ft_matrix_free((void ***)(&node->args));
			if (node->redir)
				free_redir(node->redir);
			free(node);
			node = temp;
		}
	}
}
