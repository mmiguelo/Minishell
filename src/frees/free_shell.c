/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:03:57 by frbranda          #+#    #+#             */
/*   Updated: 2025/04/21 18:47:10 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// free tokens
void	free_tokens(t_token **token)
{
	t_token	*temp;

	if (!token || !(*token))
		return ;
	while (*token != NULL)
	{
		free((*token)->token);
		temp = (*token)->next;
		free(*token);
		*token = temp;
	}
	(*token) = NULL;
}

void	free_env(t_env **env)
{
	t_env	*temp;

	if (!env || !(*env))
		return;
	while (*env != NULL)
	{
		free((*env)->name);
		free((*env)->value);
		temp = (*env)->next;
		free(*env);
		*env = temp;
	}
	(*env) = NULL;
}

// TODO might delete V
// free main struct (shell)
void	free_shell(t_shell	**shell)
{
	if ((*shell)->token_list)
		free_tokens(&(*shell)->token_list);
	if ((*shell)->env)
		free_env(&(*shell)->env);
	if ((*shell)->s_pid)
		free((*shell)->s_pid);
}
