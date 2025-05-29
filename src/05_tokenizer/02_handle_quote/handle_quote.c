/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:56:35 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/29 17:33:48 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(char *s, int i, t_info *info)
{
	int	len;

	len = ft_strlen(s);
	if (i < 0 || i >= len)
		return ;
	ft_memmove(&s[i], &s[i + 1], len - i);
	s[len - 1] = '\0';
	info->end--;
}

int	handle_solo_empty(char **s_ptr, int *i, t_info *info)
{
	char	*s;

	s = *s_ptr;
	if ((info->end - (*i)) == 2
		&& ft_strchr(QUOTES, s[*i]) && ft_strchr(QUOTES, s[*i + 1]))
	{
		*i = *i + 2;
		return (TRUE);
	}
	return (FALSE);
}

void	remove_backslash(char *s, int i, t_info *info)
{
	int	len;

	len = ft_strlen(s);
	if (i < 0 || i >= len)
		return ;
	ft_memmove(&s[i], &s[i + 1], len - i);
	s[len - 1] = '\0';
	info->end--;
}

static void	handle_quote_loop(char *s, int *i, t_info *info)
{
	while (s[*i] && *i < info->end)
	{
		if (ft_strchr(QUOTES, s[*i]) && info->mode == GENERAL)
		{
			quote_changer(s, i, info);
			*i = *i - 1;
			remove_quotes(s, *i, info);
		}
		else if ((s[*i] == '\'' && info->mode == SINGLE_QUO)
			|| (s[*i] == '"' && info->mode == DOUBLE_QUO))
		{
			quote_changer(s, i, info);
			*i = *i - 1;
			remove_quotes(s, *i, info);
		}
		else if (s[*i] == '\\' && info->mode != SINGLE_QUO)
		{
			remove_backslash(s, *i, info);
			(*i)++;
		}
		else
			(*i)++;
	}
}

void	handle_quotes(char **s_ptr, int *i, t_info *info)
{
	char	*s;

	s = *s_ptr;
	info->mode = GENERAL;
	*i = info->start;
	if (handle_solo_empty(s_ptr, i, info) == TRUE)
		return ;
	handle_quote_loop(s, i, info);
}
