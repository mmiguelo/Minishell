/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:36:31 by yes               #+#    #+#             */
/*   Updated: 2025/05/19 16:33:42 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exit(t_shell *shell, int exit_status)
{
	if (shell->envp)
		ft_matrix_free((void ***)&shell->envp);
	rl_clear_history();
	exit(exit_status);
}

void	exit_init(t_shell *shell, char *reason)
{
	perror(reason);
	if (shell->envp)
		ft_matrix_free((void ***)&shell->envp);
	exit (errno);
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
	reset_dups((*shell));
	free_ref(&(*shell)->input);
	if ((*shell)->token_list)
		free_tokens(&(*shell)->token_list);
	if ((*shell)->is_child == FALSE)
		free_process(&(*shell)->process);
	else
		free_process_child(&(*shell)->process);
	if ((*shell)->envp)
		free_matriz((*shell)->envp, ft_arrlen((*shell)->envp));
	if ((*shell)->cmd)
		free_matriz((*shell)->cmd, ft_arrlen((*shell)->cmd));
	if ((*shell)->pid_nbr)
		free((*shell)->pid_nbr);
	free_ref(&(*shell)->old_pwd);
	rl_clear_history();
	exit(status);
}
