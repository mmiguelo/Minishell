/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:19:57 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/27 13:10:06 by mmiguelo         ###   ########.fr       */
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

int	save_cwd(char *cwd, size_t size)
{
	if (getcwd(cwd, size) == NULL)
		return (errno);
	return (0);
}

int	verify_dir(const char *dir)
{
	if (!dir || !dir[0] || access(dir, F_OK) != 0)
		return (perror(dir), 1);
	if (chdir(dir) != 0)
		return (perror("cd"), 1);
	return (0);
}
