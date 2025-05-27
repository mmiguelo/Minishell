/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:56:20 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/27 16:56:23 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_var_name(char *s, int *i)
{
	int	start;
	int	len;

	start = *i;
	len = 0;
	if (s[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
	{
		(*i)++;
		len++;
	}
	return (ft_strndup(&s[start], len));
}

char	*get_env_value_expansion(char *var_name, char **envp)
{
	int		len;
	int		i;

	len = ft_strlen(var_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + (len + 1));
		i++;
	}
	return ("");
}

int	check_if_var_is_alone(char *s, int i, t_info *info)
{
	int	before;
	int	after;

	before = FALSE;
	after = FALSE;
	if (info->env_start > 0
		&& (!ft_strchr(WHITE_SPACES, s[info->env_start - 1]))
		&& (!ft_strchr(T_REDIR, s[info->env_start - 1])))
		before = TRUE;
	if ((s[i]) && !ft_strchr(WHITE_SPACES, s[i]))
		after = TRUE;
	if (before == TRUE || after == TRUE)
		return (TRUE);
	return (FALSE);
}

char	*expand_var_in_str(char *s, char *var_value, int i, t_info *info)
{
	char	*new_s;
	int		s_len;
	int		new_len;
	int		var_len;
	int		value_len;

	s_len = ft_strlen(s);
	var_len = i - info->env_start;
	value_len = ft_strlen(var_value);
	new_len = s_len - var_len + value_len;
	new_s = (char *)ft_calloc((new_len + 1), sizeof(char));
	if (!new_s)
		return (NULL);
	ft_memcpy(new_s, s, info->env_start);
	ft_strlcpy(new_s + info->env_start, var_value, (value_len + 1));
	ft_strlcpy(new_s + info->env_start + value_len, s + i, (s_len - i + 1));
	new_s[new_len] = '\0';
	return (new_s);
}
