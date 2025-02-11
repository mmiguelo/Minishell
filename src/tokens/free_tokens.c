/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:23:28 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/11 17:54:06 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_char_pp(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
	{
		free(s[i]);
		s[i] = NULL;
		i++;
	}
	free(s);
}

void	free_tokens(t_token **token)
{
	t_token	*temp;
	while (*token != NULL)
	{
		if ((*token)->token)
			free((*token)->token);
		if ((*token)->type)
			free((*token)->type);
		temp = (*token)->next;
		free(*token);
		*token = temp;
	}
}