/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:23:28 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/24 17:41:08 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// FREE of the token list (binary tree)
void	free_token_list(t_token_tree **token)
{
	t_token_tree	*temp;
	while (*token != NULL)
	{
		if ((*token)->left)
			free_token_list(&(*token)->left);
		free((*token)->token_list);
		temp = (*token)->right;
		free(*token);
		*token = temp;
	}
}

void	free_tokens(t_token **token)
{
	t_token	*temp;
	while (*token != NULL)
	{
		free((*token)->token);
		temp = (*token)->next;
		free(*token);
		*token = temp;
	}
}