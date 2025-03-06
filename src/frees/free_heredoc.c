/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:23:48 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/03/06 19:23:48 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees the memory allocated for a linked list of t_heredoc structures.
 * 
 * @param heredoc Pointer to the head of the linked list of structure.
 */
void	free_heredoc(t_heredoc *heredoc)
{
	t_heredoc	*tmp;

	while(heredoc)
	{
		tmp = heredoc->next;
		if (heredoc->heredoc_path)
		{
			free(heredoc->heredoc_path);
			heredoc->heredoc_path = NULL;
		}
		free(heredoc);
		heredoc = tmp;
	}
}
