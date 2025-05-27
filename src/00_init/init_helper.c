/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:33:47 by yes               #+#    #+#             */
/*   Updated: 2025/05/27 14:39:04 by mmiguelo         ###   ########.fr       */
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
		return (SUCCESS);
	}
	shlvl = ft_atoi(old) + 1;
	if (shlvl >= 1000)
	{
		ft_printf_fd(2, "minishell: "ERROR_SHLVL, shlvl);
		shlvl = 1;
	}
	new = ft_itoa(shlvl);
	if (!new)
		return (INVALID);
	if (update_envp_int(shell, "SHLVL", new) != 0)
		return (free_ref(&new), INVALID);
	free_ref(&new);
	return (SUCCESS);
}

int	update_pwd(t_shell *shell)
{
	char	*pwd;
	char	*old_pwd;

	pwd = get_env_value_expansion("PWD", shell->envp);
	if (*pwd == '\0')
	{
		pwd = ft_strjoin_free(ft_strdup("PWD="), getcwd(NULL, 0));
		if (!pwd)
			return (INVALID);
		if (add_var_to_envp(pwd, shell) != 0)
			return (free_ref(&pwd), INVALID);
		free_ref(&pwd);
	}
	old_pwd = get_env_value_expansion("OLDPWD", shell->envp);
	if (*old_pwd == '\0')
	{
		old_pwd = ft_strjoin_free(ft_strdup("OLDPWD="), getcwd(NULL, 0));
		if (!pwd)
			return (INVALID);
		if (add_var_to_envp(old_pwd, shell) != 0)
			return (free_ref(&old_pwd), INVALID);
		free_ref(&old_pwd);
	}
	return (SUCCESS);
}

int	update_lastcmd(t_shell *shell)
{
	char	*lastcmd;

	lastcmd = get_env_value_expansion("_", shell->envp);
	if (*lastcmd == '\0')
	{
		if (add_var_to_envp("_=./minishell", shell) != 0)
			return (free_ref(&lastcmd), INVALID);
	}
	return (SUCCESS);
}

void	update_envp(t_shell *shell)
{
	if (update_shlvl(shell) != SUCCESS)
		exit_init(shell, "shlvl");
	if (update_pwd(shell) != SUCCESS)
		exit_init(shell, "pwd");
	if (update_lastcmd(shell) != SUCCESS)
		exit_init(shell, "lastcmd");
}
