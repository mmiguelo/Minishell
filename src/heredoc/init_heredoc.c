/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:07:45 by yes               #+#    #+#             */
/*   Updated: 2025/05/08 18:34:49 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hd	*init_heredoc(t_token *token)
{
	t_hd	*new;

	new = (t_hd *)ft_calloc(1, sizeof(t_hd));
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
