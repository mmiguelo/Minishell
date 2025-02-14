/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:31:13 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/12 14:46:14 by frbranda         ###   ########.fr       */
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
	new->type = ft_strdup("type");
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

void	token_split(t_token **token,char *input)
{
	t_token	*new_token;
	char	**splitted;
	int		i;

	i = 0;
	splitted = ft_split(input, ' ');
	while (splitted[i] != NULL)
	{
		new_token = initialize_token(splitted[i]);
		list_add_last_token(token, new_token);
		i++;
	}
	free_char_pp(splitted);
}

void	print_token_list(t_token *token)
{
	t_token	*temp;

	temp = token;
	ft_printf("-----------------\n");
	while (temp)
	{
		ft_printf("Token: {%s}\n", temp->token);
		ft_printf("Type : %s\n", temp->type);
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

void	tokenizer(char *input)
{
	t_token	*token;

	token = NULL;
	token_split(&token, input);
	print_token_list(token);
	free_tokens(&token);
}

/* ft_printf("-----------------\nSplitted[%i]: %s\n", i, splitted[i]); */