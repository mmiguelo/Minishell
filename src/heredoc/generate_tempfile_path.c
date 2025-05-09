/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_tempfile_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:20:04 by yes               #+#    #+#             */
/*   Updated: 2025/05/09 15:53:54 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_pid_id(void)
{
	char	*temp;
	char	*pid_s;
	char	*id_s;

	pid_s = ft_itoa(getpid());
	if (!pid_s)
		return (NULL);
	id_s = ft_itoa(set_heredoc_id());
	if (!id_s)
		return (free_ref(&pid_s), NULL);
	temp = ft_strjoin(pid_s, "_");
	free_ref(&pid_s);
	if (!temp)
		return (free_ref(&id_s), NULL);
	return (ft_strjoin_free(temp, id_s));
}

char	*generate_tempfile_path(char *dir)
{
	char	*new;
	char	*id_s;
	char	*hd_id;

	id_s = get_pid_id();
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
