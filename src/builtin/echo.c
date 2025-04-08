/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:19:50 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/04/07 18:47:38 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the given argument is the string "-n".
 * 
 * This function checks if the provided argument `arg` starts with a minus sign
 * (`-`) and is followed only by the letter 'n'. If the argument matches the 
 * pattern `"-n"` (with no additional characters after the 'n'), the function 
 * returns `1`. Otherwise, it returns `0`.
 * 
 * @param arg The argument string to check.
 * @return int Returns 1 if the argument is "-n", 0 otherwise.
 */
static int	ft_is_n(char *arg)
{
	int	i;

	i = -1;
	if (arg[++i] != '-')
		return (0);
	if (!arg[++i])
		return (0);
	while (arg[++i])
	{
		if (arg[i] != 'n')
			return (0);
	}
	return (1);
}

/**
 * @brief Prints the arguments to the standard output, with an optional newline.
 * 
 * This function implements the `echo` built-in command. It prints the arguments
 * provided to the standard output (`stdout`). If the argument `-n` is used, the 
 * function suppresses the trailing newline that is usually printed at the end.
 * 
 * The function checks if the `-n` flag is set (using the `ft_is_n` helper
 * function), and if so, it avoids printing a newline at the end. Otherwise,
 * it prints a newline after the arguments.
 * 
 * @param args Array of command arguments. The first argument (`args[0]`) is
 * usually `"echo"`, and subsequent arguments are the strings to be printed.
 * @param shell Pointer to the shell structure (unused in this function).
 * @return int Always returns `0` indicating successful execution.
 */
int	ft_echo(char **args, t_shell *shell)
{
	int	i;
	int	n_flag;

	(void)shell;
	i = 1;
	n_flag = 0;
	while (args[i] && ft_is_n(args[i]))
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
