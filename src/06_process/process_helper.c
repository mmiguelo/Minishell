/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:27:51 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/02 12:27:51 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_type(t_token *token)
{
	if (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == APPEND || token->type == HEREDOC)
		return (1);
	return (0);
}

int	count_args(t_token *temp)
{
	int	count;

	count = 0;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == CMD || temp->type == ARG)
			count++;
		temp = temp->next;
	}
	return (count);
}
