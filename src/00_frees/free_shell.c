/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:03:57 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/08 18:35:16 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_heredoc(t_hd **hd)
{
	if (!hd || !(*hd))
		return ;
	unlink((*hd)->hd_path);
	free_ref(&(*hd)->hd_path);
	free_ref(&(*hd)->delimiter);
	free((*hd));
	(*hd) = NULL;
}

// free tokens
void	free_tokens(t_token **token)
{
	t_token	*temp;

	if (!token || !(*token))
		return ;
	while (*token != NULL)
	{
		temp = (*token)->next;
		free((*token)->token);
		if ((*token)->heredoc)
			clean_heredoc(&(*token)->heredoc);
		free(*token);
		*token = temp;
	}
	(*token) = NULL;
}
