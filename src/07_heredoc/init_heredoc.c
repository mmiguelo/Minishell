/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:57:26 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/27 16:57:29 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hd	*init_heredoc(t_redir *redir)
{
	t_hd	*new;

	new = (t_hd *)ft_calloc(1, sizeof(t_hd));
	if (!new)
		return (NULL);
	new->delimiter = ft_strdup(redir->filename);
	if (!new->delimiter)
	{
		free (new);
		return (NULL);
	}
	return (new);
}
