/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:26:03 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/04/21 18:41:55 by yes              ###   ########.fr       */
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

// TODO DELETE LATER WHEN ENV IS INITIALIZE
/* t_env	*initialize_env(void)
{
	t_env	*new;
	t_env	*new2;
	t_env	*new3;

	new = ft_calloc(1, sizeof(t_env));
	new->name = ft_strdup("VAR");
	new->value = ft_strdup("s -");
	new->next = NULL;
	new2 = ft_calloc(1, sizeof(t_env));
	new2->name = ft_strdup("VAR1");
	new2->value = ft_strdup("echo");
	new2->next = NULL;
	new->next = new2;
	new3 = ft_calloc(1, sizeof(t_env));
	new3->name = ft_strdup("REDIR");
	new3->value = ft_strdup(">>");
	new3->next = NULL;
	new2->next = new3;
	return (new);
} */

/* static int	create_env(t_shell *shell)
{
	// TODO create
	if (shlvl() == FALSE)
		return (FALSE);
	if (lastcmd() == FALSE)
		return (FALSE);
	if (pwd() == FALSE)
		return (FALSE);
	if (!shell)
		return (FALSE);
	return (TRUE);
} */

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
	shell->env = NULL;
	shell->pid = getpid();
	shell->s_pid = NULL;
	if (!envp || !envp[0])
	{
		ft_printf("Creating default env to shell->envp\n");
		/* 	if (create_env(shell) == FALSE)
		exit_init(shell, "getcwd"); */
	}
	else
	{
		shell->envp = init_env(envp);
		if (!shell->envp)
		exit_init(shell, "malloc");
	}
	shell->env = NULL;
	shell->cmd = NULL;
	shell->old_pwd = NULL;
	shell->exit_status = 0;
	shell->prev_exit_status = 0;
}
