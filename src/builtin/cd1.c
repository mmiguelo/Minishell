/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:19:57 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/23 16:10:45 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Searches for an environment variable in the shell's list.
 * 
 * This function scans the shell's environment (`shell->envp`) for a variable
 * that matches `var`. It returns the index of the variable if found, or -1
 * if the variable is not found or invalid.
 * 
 * @param var  The name of the environment variable to search for.
 * @param shell The shell structure containing the environment (`shell->envp`).
 * @return int The index of the variable in `shell->envp` if found.
 * 		   -1 if the variable is not found or invalid.
 */
int	get_env_line(const char *var, t_shell *shell)
{
	int		i;
	int		len;
	char	**env;

	len = ft_strlen(var);
	if (!validate_var(var))
		return (-1);
	i = -1;
	if (!shell->envp)
		return (-1);
	env = shell->envp;
	while (env[++i])
	{
		if (ft_strncmp(env[i], var, len) == 0
			&& (env[i][len] == '\0' || env[i][len] == '='))
			return (i);
	}
	return (-1);
}

char	*get_env_value(const char *var, t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], var, ft_strlen(var)) == 0
			&& shell->envp[i][ft_strlen(var)] == '=')
			break ;
		i++;
	}
	if (shell->envp[i] == NULL)
		return (ft_printf_fd(2, "minishell: cd: HOME not set\n"), NULL);
	return (shell->envp[i] + ft_strlen(var) + 1);
}
