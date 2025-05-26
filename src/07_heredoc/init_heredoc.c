/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:07:45 by yes               #+#    #+#             */
/*   Updated: 2025/05/16 17:00:39 by yes              ###   ########.fr       */
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
