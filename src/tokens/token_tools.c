/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:41:47 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/18 19:21:07 by yes              ###   ########.fr       */
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
	new->type = ARG;
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

void	print_token_list(t_token *token)
{
	t_token	*temp;

	temp = token;
	ft_printf("-----------------\n");
	while (temp)
	{
		ft_printf("Token: {%s}\n", temp->token);
		if (temp->type == ARG)
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
}

/* ft_printf("-----------------\nSplitted[%i]: %s\n", i, splitted[i]); */