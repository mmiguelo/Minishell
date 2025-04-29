/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:26:03 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/04/25 18:12:19 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initializes a new environment array by duplicating the provided
 * environment variables.
 * 
 * This function takes an array of environment variables (`envp`) and creates
 * a new array
 * of strings that duplicates the provided environment variables. It allocates
 * memory for
 * the new environment array and copies each string from the original `envp`
 * array into it.
 * 
 * @param envp A pointer to the array of environment variables passed to the
 * program.
 * @return char** A new array of environment variables, or `NULL` if memory
 * allocation fails.
 */
char	**init_env(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = ft_calloc(i + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
	}
	new_env[i] = NULL;
	return (new_env);
}

void	inizialize_info(t_info	*info)
{
	info->start = 0;
	info->end = 0;
	info->env_start = 0;
	info->env_end = 0;
	info->type = CMD;
	info->type_flag = FALSE;
	info->mode = GENERAL;
	info->error_flag = FALSE;
}

t_token	*initialize_token(char *s, int type)
{
	t_token	*new;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = ft_strdup(s);
	new->type = type;
	new->next = NULL;
	return (new);
}

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
		//TODO maybe change this ? because its showing with env -i
		if (add_var_to_envp("SHLVL=1", shell) != 0)
			return (INVALID);
	}
	else
	{
		shlvl = ft_atoi(old) + 1;
		new = ft_itoa(shlvl);
		if(!new)
			return (INVALID);
		if (update_envp_int(shell, "SHLVL", new) != 0)
			return (free_ref(&new), INVALID);
		free_ref(&new);
	}
	return (SUCCESS);
}

/**
 * @brief Initializes the shell structure with environment variables and
 * command array.
 * 
 * @param shell A pointer to the `t_shell` structure that represents the shell.
 * @param envp A pointer to the environment variables passed to the program
 * (typically from `main`).
 */
void	ft_init(t_shell	*shell, char **envp)
{
	shell->input = NULL;
	shell->args = NULL;
	shell->token_list = NULL;
	shell->head = NULL;
	shell->pid = getpid();
	shell->s_pid = NULL;
	shell->envp = init_env(envp);
	if (!shell->envp)
		exit_init(shell, "malloc");
	if (update_shlvl(shell) != SUCCESS)
		exit_init(shell, "shlvl");
	shell->cmd = NULL;
	shell->old_pwd = NULL;
	shell->exit_status = 0;
	shell->prev_exit_status = 0;
}
