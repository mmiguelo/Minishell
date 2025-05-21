/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:21:45 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/21 11:24:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**when_no_env(void)
{
	char	**env;
	char	cwd[1024];

	env = ft_calloc(4, sizeof(char *));
	if (!env)
		return (NULL);
	env[0] = ft_strdup_free(ft_strdup("PWD="),
			ft_strdup(getcwd(cwd, sizeof(cwd))));
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	return (env);
}

static int	env_error(char *arg)
{
	if (!arg)
		return (0);
	if (arg[0] == '-' && arg[1])
	{
		ft_printf("env: illegal option -- %c\n", arg[1]);
		return (125);
	}
	else
	{
		ft_printf("env: '%s': No such file or directory\n", arg);
		return (127);
	}
}

int	ft_env(char **args, t_shell *shell)
{
	int	i;

	(void)args;
	i = -1;
	if (!shell->envp)
		return (0);
	if (args[1])
		env_error(args[1]);
	else
	{
		while (shell->envp[++i])
		{
			if (ft_strchr(shell->envp[i], '='))
				ft_printf("%s\n", shell->envp[i]);
		}
	}
	return (0);
}
