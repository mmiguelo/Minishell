/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:48:43 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/27 14:42:38 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_process(t_shell *shell)
{
	t_node	*node;

	node = shell->process;
	if (count_pid(shell) == 1)
		exec_single_node(shell, node);
	else
		exec_multi_node(shell, node, 0);
}
