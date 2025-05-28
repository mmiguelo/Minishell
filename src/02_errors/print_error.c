/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:14:30 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/28 17:59:38 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles errors related to the `export` command when an invalid
 * argument is provided.
 * 
 * This function checks the provided argument to the `export` command. If the
 * argument starts with a dash ('-') and has invalid options or is not a valid
 * identifier, an appropriate error message is printed.
 * 
 * @param arg The argument passed to the `export` command that is being
 * validated.
 * @return int Returns an error code:
 * 
 * - `2` if the argument is an invalid option (e.g., `-a`, `-1`).
 * 
 * - `1` if the argument is a valid identifier but not allowed for export.
 * 
 * - `0` if no error is found.
 */
int	export_error(char *arg)
{
	if (arg[0] == '-')
	{
		if (arg[1])
			return (ft_printf_fd(2, "minishell: export -%c: invalid option\n",
					arg[1]), 2);
		return (ft_printf_fd(2, \
			"minishell: export: `%s': not a valid identifier\n", arg), 1);
	}
	return (0);
}

/**
 * @brief Prints an error message indicating that the provided variable name is
 * not a valid identifier.
 * 
 * This function is used to print an error message when an invalid variable name
 * is encountered during the export process. The error message indicates that the
 * variable is not a valid identifier as per the shell's requirements.
 * 
 * @param var The name of the variable that is not valid.
 */
int	print_invalid_var(char *var)
{
	return (ft_printf_fd(2, \
		"minishell: export: `%s': not a valid identifier\n", var), 1);
}
