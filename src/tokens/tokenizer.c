/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:31:13 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/18 18:59:07 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	tokenizer(char *input)
{
	t_token	*token;

	token = NULL;
	token_split(&token, input);
	print_token_list(token);
	free_tokens(&token);
}