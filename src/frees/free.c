/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:43:05 by frbranda          #+#    #+#             */
/*   Updated: 2025/04/08 17:08:58 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_char_pp(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
	{
		free(s[i]);
		s[i] = NULL;
		i++;
	}
	free(s);
	s = NULL;
}

/**
 * @brief Frees the memory allocated for the environment variables array in
 * the shell structure.
 * 
 * @param shell The shell structure containing the array of environment
 * variables (`envp`).
 * @param i The number of environment variables in the `envp` array that should
 * be freed.
 * @return int Returns 0 upon successful completion.
 */
int	free_matriz(char **shell, int i)
{
	if (!shell)
		return (0);
	while (i >= 0)
	{
		free(shell[i]);
		shell[i] = NULL;
		i--;
	}
	free(shell);
	shell = NULL;
	return (0);
}

/**
 * @brief Frees allocated memory and exits the shell with the specified status.
 * 
 * This function is responsible for cleaning up the shell's resources before 
 * terminating the program. It frees memory allocated for the environment 
 * variables (`envp`) and the command history (`cmd`). Afterward, it clears 
 * the history in the readline library and exits the program with the given 
 * exit status. The `errno` is set to the provided status before exiting.
 * 
 * @param shell Pointer to the shell structure that contains environment 
 *               variables and commands.
 * @param status Exit status code to be returned when exiting the shell.
 */
void	ft_kill(t_shell **shell, int status)
{
	errno = status;
	if ((*shell)->token_list)
		free_tokens(&(*shell)->token_list);
	if ((*shell)->env)
		free_env(&(*shell)->env);
	if ((*shell)->s_pid)
		free((*shell)->s_pid);
	if ((*shell)->envp)
		free_matriz((*shell)->envp, ft_arrlen((*shell)->envp));
	if ((*shell)->cmd)
		free_matriz((*shell)->cmd, ft_arrlen((*shell)->cmd));
	if ((*shell)->old_pwd)
		free((*shell)->old_pwd);
	rl_clear_history();
	exit(status);
}
