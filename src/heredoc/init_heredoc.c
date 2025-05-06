/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:07:45 by yes               #+#    #+#             */
/*   Updated: 2025/05/06 17:55:21 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_heredoc	*init_heredoc(t_token *token)
{
	t_heredoc *new;

	new = (t_heredoc *)ft_calloc(1, sizeof(t_heredoc));
	if (!new)
		return (NULL);
	new->delimiter = ft_strdup(token->token);
	if (!new->delimiter)
	{
		free (new);
		return (NULL);
	}
	return (new);
}