/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:17:54 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/04/09 14:35:18 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**realloc_env(char **envp)
{
	char	**new_envp;
	int		i;
	int		len;

	len = ft_arrlen(envp);
	i = 0;
	new_envp = ft_calloc(len + 2, sizeof(char *));
	if (!new_envp)
		return (NULL);
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	new_envp[i + 1] = NULL;
	free_char_pp_ref(&envp);
	return (new_envp);
}

int	update_existing_var(char *new_var, t_shell *shell, int i)
{
	if (i >= 0)
	{
		free(shell->envp[i]);
		shell->envp[i] = new_var;
		return (0);
	}
	return (-1);
}

char	*get_value(char *var)
{
	char	*value;
	int		i;

	i = 0;
	if (!var)
		return (NULL);
	while (var[i] && var[i] != '=')
		i++;
	value = ft_strdup(var + i + 1);
	if (!value)
		return (ft_strdup(""));
	return (value);
	printf("value: %s\n", value);
}

void	concatenate_value(char **var, char *new_var, t_shell *shell, int i)
{
	char	*new_value;
	char	*old_value;

	old_value = get_value(shell->envp[i]);
	new_value = ft_strdup(ft_strnstr(*var, "+=", ft_strlen(*var)) + 2);
	*var = ft_strdup_free(ft_strjoin(new_var, "="),
			ft_strdup_free(old_value, new_value));
	free(shell->envp[i]);
	shell->envp[i] = *var;
}
