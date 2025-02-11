/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:31:13 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/11 17:52:55 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_token(t_token **token, char *input)
{
	t_token *new;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return ;
	new->token = ft_strdup(input);
	new->type = ft_strdup("type");
	new->next = NULL;
	new->prev = NULL;
	*token = new;
}

/* void	token_split(t_token **token,char *input)
{
	t_token	*new;
	char	**splitted;

	splitted = ft_split(input, ' ');
	new = initialize_token(input);
	free_char_pp(splitted);
} */


void	print_token_list(t_token *token)
{
	t_token	*temp;

	temp = token;
	ft_printf("-----------------\n");
	while (temp)
	{
		ft_printf("Token: {%s}\n", token->token);
		ft_printf("Type : %s\n", token->type);
		ft_printf("Next : %s\n", token->next);
		ft_printf("-----------------\n");
		temp = temp->next;
	}
	ft_printf("NULL\n");
}

void	tokenizer(char *input)
{
	t_token	*token;

	token = NULL;
	/* token_split(&token, input); */
	initialize_token(&token, input);
	print_token_list(token);
	free_tokens(&token);
}
