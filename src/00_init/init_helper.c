/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:33:47 by yes               #+#    #+#             */
/*   Updated: 2025/05/09 15:34:37 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_envp_int(t_shell *shell, char *var, char *path)
{
	char	*new_line;
	char	*temp;
	int		i;

	i = get_env_line(var, shell);
	new_line = ft_strjoin(var, "=");
	if (!new_line)
		return (INVALID);
	temp = new_line;
	new_line = ft_strjoin(new_line, path);
	free(temp);
	if (!new_line)
		return (INVALID);
	if (i == -1)
	{
		if (add_var_to_envp(new_line, shell) != 0)
			return (free_ref(&new_line), INVALID);
	}
	else
	{
		free(shell->envp[i]);
		shell->envp[i] = new_line;
		return (SUCCESS);
	}
	return (free_ref(&new_line), SUCCESS);
}

int	update_shlvl(t_shell *shell)
{
	char	*old;
	char	*new;
	int		shlvl;

	old = get_env_value_expansion("SHLVL", shell->envp);
	if (!old)
	{
		if (add_var_to_envp("SHLVL=1", shell) != 0)
			return (INVALID);
	}
	else
	{
		shlvl = ft_atoi(old) + 1;
		new = ft_itoa(shlvl);
		if (!new)
			return (INVALID);
		if (update_envp_int(shell, "SHLVL", new) != 0)
			return (free_ref(&new), INVALID);
		free_ref(&new);
	}
	return (SUCCESS);
}
