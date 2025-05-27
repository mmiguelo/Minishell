/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:44:28 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/27 12:44:29 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees a dynamically allocated string and sets the original pointer to
 * NULL in the caller.
 *
 * This function safely releases a `char *` and avoids dangling pointers by
 * nullifying it via reference.
 *
 * @param s A pointer to the string to be freed.
 */
void	free_ref(char **s)
{
	if (!s || !*s)
		return ;
	free(*s);
	*s = NULL;
}

/**
 * @brief Frees a NULL-terminated array of strings and sets the original pointer
 * to NULL in the caller.
 *
 * This function receives a reference to the array pointer, allowing it to 
 * safely nullify the original pointer after freeing, preventing potential
 * dangling pointers.
 *
 * @param s A pointer to the array of strings to free.
 */
void	free_char_pp_ref(char ***s)
{
	int	i;

	i = 0;
	if (!(*s))
		return ;
	while ((*s)[i])
	{
		free((*s)[i]);
		(*s)[i] = NULL;
		i++;
	}
	free (*s);
	*s = NULL;
}

/**
 * @brief Frees the memory allocated for the environment variables array in
 * the shell structure.
 * 
 * @param shell The shell structure containing the array of environment
 * variables (`envp`).
 * @param i The number of environment variables in the `envp` array that
 * should be freed.
 * @return int Returns 0 upon successful completion.
 */
int	free_matriz(char **shell, int i)
{
	if (!shell || !*shell)
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
