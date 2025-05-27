/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_tempfile_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:57:16 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/27 16:57:18 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_tempfile_path(char *dir, int *id)
{
	char	*new;
	char	*id_s;
	char	*hd_id;

	id_s = ft_itoa(*id);
	(*id)++;
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
