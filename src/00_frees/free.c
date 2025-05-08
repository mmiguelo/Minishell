/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:43:05 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/06 16:07:18 by yes              ###   ########.fr       */
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
 * @brief Frees a NULL-terminated array of strings (char **), without altering
 * the caller's pointer.
 *
 * Use this when you want to release the memory of each string and the array
 * itself, but you do not need to set the original pointer to NULL in the caller.
 *
 * @param s The array of strings to free.
 */
void	free_char_pp(char **s)
{
	int	i;

	i = 0;
	if (!(*s))
		return ;
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
	if ((*shell)->input)
		free((*shell)->input);
	if ((*shell)->args)
		free_char_pp_ref(&(*shell)->args);
	if ((*shell)->token_list)
		free_tokens(&(*shell)->token_list);
	if ((*shell)->envp)
		free_matriz((*shell)->envp, ft_arrlen((*shell)->envp));
	if ((*shell)->cmd)
		free_matriz((*shell)->cmd, ft_arrlen((*shell)->cmd));
	if ((*shell)->old_pwd)
		free((*shell)->old_pwd);
	rl_clear_history();
	exit(status);
}
