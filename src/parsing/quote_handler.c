/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:44:06 by yes               #+#    #+#             */
/*   Updated: 2025/02/19 18:16:54 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//"echo"   "   ola   "   <--- 2 tokens

t_token	*quote_handler(t_token **token, char *s)
{
	bool	s_quote;
	int		i;

	i = 0;
	s_quote = false;
	while (s[i] == ' ')
			i++;
	while(s[i])
	{
		
		i++;
	}
}

t_token	*minishell_split(t_token **token, char *input)
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