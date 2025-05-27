/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:25:43 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/27 16:54:33 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_heredoc_child(t_hd **hd)
{
	if (!hd || !(*hd))
		return ;
	free_ref(&(*hd)->hd_path);
	free_ref(&(*hd)->delimiter);
	free((*hd));
	(*hd) = NULL;
}

void	free_redir_child(t_redir **redir)
{
	t_redir	*temp;

	if (!redir || !(*redir))
		return ;
	while (*redir)
	{
		temp = (*redir)->next;
		if ((*redir)->filename)
			free((*redir)->filename);
		if ((*redir)->heredoc)
			clean_heredoc_child(&(*redir)->heredoc);
		free(*redir);
		*redir = temp;
	}
	(*redir) = NULL;
}

void	free_process_child(t_node **process)
{
	t_node	*temp;

	if (!process || !(*process))
		return ;
	while (*process)
	{
		temp = (*process)->next;
		if ((*process)->args)
			ft_matrix_free((void ***)(&(*process)->args));
		if ((*process)->redir)
			free_redir_child(&(*process)->redir);
		free_ref(&(*process)->cmd);
		free(*process);
		*process = temp;
	}
	(*process) = NULL;
}
