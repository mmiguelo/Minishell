/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:41:47 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/24 12:03:46 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*initialize_token(char *input)
{
	t_token *new;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = ft_strdup(input);
	new->type = CMD;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
t_token	*find_last_token(t_token *token)
{
	t_token	*temp;

	if (!token)
		return (NULL);
	temp = token;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return(temp);
}

t_token	*list_add_last_token(t_token **token, t_token *new)
{
	t_token *last;
	
	if (!new)
		return (NULL);
	if (!*token)
		*token = new;
	else
	{
		last = find_last_token(*token);
		last->next = new;
		new->prev = last;
	}
	return (*token);
}

/* ft_printf("-----------------\nSplitted[%i]: %s\n", i, splitted[i]); */