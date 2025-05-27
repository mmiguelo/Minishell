/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:57:10 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/27 16:57:13 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*add_new_token(t_token **token_list, char *s, t_info *info)
{
	t_token	*new_token;
	char	*temp;

	if (info->end - info->start <= 0)
		return (NULL);
	temp = ft_substr(s, info->start, (info->end - info->start));
	new_token = initialize_token(temp, info->type);
	add_last_token(token_list, new_token);
	free(temp);
	return (*token_list);
}
