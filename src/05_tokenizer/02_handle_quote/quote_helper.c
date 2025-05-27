/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:56:58 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/27 16:57:01 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: change header

#include "minishell.h"

void	quote_changer(char *s, int *i, t_info *info)
{
	if (s[*i] == '\'')
	{
		if (info->mode == GENERAL)
			info->mode = SINGLE_QUO;
		else if (info->mode == SINGLE_QUO)
			info->mode = GENERAL;
	}
	else if (s[*i] == '\"')
	{
		if (info->mode == GENERAL)
			info->mode = DOUBLE_QUO;
		else if (info->mode == DOUBLE_QUO)
			info->mode = GENERAL;
	}
	(*i)++;
}
