/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_tempfile_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:20:04 by yes               #+#    #+#             */
/*   Updated: 2025/05/06 17:48:59 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_tempfile_path(char *dir)
{
	char	*new;
	char	*hd_id;
	char	*id_s;

	id_s = ft_itoa(set_heredoc_id());
	if (!id_s)
		return (NULL);
	hd_id = ft_strjoin("hd_", id_s);
	free_ref(&id_s);
	if (!hd_id)
		return (NULL);
	new = ft_strjoin(dir, hd_id);
	free_ref(&hd_id);
	if (!new)
		return (NULL);
	return (new);
}
