/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:25:44 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/29 13:24:33 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pid(t_shell *shell)
{
	int		i;
	t_node	*process;

	process = shell->process;
	i = 0;
	while (process)
	{
		i++;
		process = process->next;
	}
	return (i);
}

static char	**get_paths_from_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

static char	*build_and_check(char *dir, char *cmd)
{
	char	*temp;
	char	*path;

	if (!dir || !cmd)
		return (NULL);
	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	path = ft_strjoin(temp, cmd);
	free_ref(&temp);
	if (!path)
		return (NULL);
	if (access(path, F_OK | X_OK) == 0)
		return (path);
	free_ref(&path);
	return (NULL);
}

static char	*check_path_and_return(char **full_path, char *cmd)
{
	int		i;
	char	*partial_path;

	if (!full_path || !cmd)
		return (free_char_pp_ref(&full_path), NULL);
	i = 0;
	while (full_path[i])
	{
		partial_path = build_and_check(full_path[i], cmd);
		if (partial_path)
			return (free_char_pp_ref(&full_path), partial_path);
		i++;
	}
	free_char_pp_ref(&full_path);
	return (NULL);
}

char	*search_path(char *cmd, char **envp)
{
	char	**full_path;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		if (errno == EACCES || errno == EISDIR)
			return (ft_strdup(cmd));
		return (NULL);
	}
	full_path = get_paths_from_env(envp);
	if (!full_path)
		return (ft_strdup(cmd));
	return (check_path_and_return(full_path, cmd));
}
