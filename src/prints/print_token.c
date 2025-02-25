/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:56:49 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/25 12:03:48 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *token)
{
	t_token	*temp;

	if (!token)
		return ;
	temp = token;
	ft_printf("-----------------\n");
	while (temp)
	{
		ft_printf("Token: {%s}\n", temp->token);
		if (temp->type == EXEC)
			ft_printf("Type : ARG\n");
		if (temp->next == NULL)
			ft_printf("Next : %s\n", temp->next);
		else
			ft_printf("Next : {%s}\n", temp->next->token);
		if (temp->prev == NULL)
			ft_printf("Prev : %s\n", temp->prev);
		else
			ft_printf("Prev : {%s}\n", temp->prev->token);
		ft_printf("-----------------\n");
		temp = temp->next;
	}
	ft_printf("NULL\n");
	ft_printf("-----------------\n");
}

void	print_tokens_simple(t_token *token)
{
	t_token	*temp;

	if (!token)
		return ;
	temp = token;
	ft_printf("Tokens: [\"%s\"", temp->token);
	temp = temp->next;
	while (temp)
	{
		ft_printf(", \"%s\"", temp->token);
		temp = temp->next;
	}
	ft_printf("]\n");
}