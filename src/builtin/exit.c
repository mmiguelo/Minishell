/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:20:01 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/04/07 18:47:45 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Exits the shell with a specified status or prints an error message.
 * 
 * The function implements the `exit` command for the shell. It checks the number
 * of arguments provided, verifies if the exit status is a valid number, and then
 * terminates the shell with the appropriate exit status. If there are too many
 * arguments or an invalid numeric value is provided, it prints an error message
 * and terminates the shell with a status of `2`.
 * 
 * @param args Array of command arguments. The first argument (`args[0]`) is 
 * always `"exit"`, and the second argument (`args[1]`) is the exit status
 * (optional).
 * @param shell Pointer to the shell structure (used to clean up and exit the
 * shell).
 * @return int Returns `0` if the shell exit is handled successfully, or `1` for 
 * incorrect argument input. The shell process will be terminated by the
 * `ft_kill` function.
 */
int	ft_exit(char **args, t_shell *shell)
{
	ft_printf("exit\n");
	if (ft_arrlen(args) > 2)
	{
		if (!ft_isnum(args[1]))
		{
			ft_printf(NO_NUMERIC, args[1]);
			ft_kill(&shell, 2);
		}
		else
			return (ft_printf("minishell: exit: too many arguments\n"), 1);
	}
	if (ft_arrlen(args) == 2)
	{
		if (!ft_isnum(args[1]))
		{
			ft_printf(NO_NUMERIC, args[1]);
			ft_kill(&shell, 2);
		}
		else
			ft_kill(&shell, ft_atoi(args[1]));
	}
	if (ft_arrlen(args) == 1)
		ft_kill(&shell, 0);
	return (0);
}
