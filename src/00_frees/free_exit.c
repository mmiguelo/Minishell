/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:36:31 by yes               #+#    #+#             */
/*   Updated: 2025/04/21 18:52:31 by yes              ###   ########.fr       */
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
