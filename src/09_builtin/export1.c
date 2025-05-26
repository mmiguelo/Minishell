/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 08:39:16 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/03/19 08:39:16 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_export_value(char *arg)
{
	int		i;
	char	*value;

	i = check_for_value(arg);
	if (i == 0)
		return (NULL);
	value = ft_substr(arg, i + 1, ft_strlen(arg) - i - 1);
	return (value);
}

char	*get_export_var(char *arg)
{
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			break ;
		i++;
	}
	return (ft_substr(arg, 0, i));
}

int	check_for_value(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	validate_var(const char *var)
{
	int	i;

	i = 0;
	if (var[i] != '_' && !ft_isalpha(var[i]))
		return (0);
	while (var[++i])
	{
		if (var[i] != '_' && !ft_isalnum(var[i]))
			return (0);
	}
	return (i);
}

int	check_if_var_is_in_env(char *arg, t_shell *shell)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(arg);
	while (shell->envp[i] != NULL)
	{
		if (ft_strncmp(shell->envp[i], arg, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}
