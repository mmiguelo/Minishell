/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:31:13 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/20 20:26:47 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// single quote handler
// double quote handler

// " echo "   "   ola   "   <--- 2 tokens / 6 tokens (if no quote handler)


char *string_found(char *input, int *i)
{
	char	*new_s;
	int		word_count;
	int		j;

	j = 0;
	word_count = 0;
	while(input[*i] && input[*i] != ' ')
	{
		*i = *i + 1;
		word_count++;
	}
	new_s = (char *)malloc((word_count + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	while (word_count != 0)
	{
		new_s[j] = input[*i - word_count];
		word_count--;
		j++;
	}
	new_s[j] = '\0';
	*i = *i - 1;
	return (new_s);
}

void	*quote_handler(t_token **token, char **input, int *i)
{
	if (input[*i] == '\'')
}

void	token_split(t_token **token, char *input)
{
	t_token	*new_token;
	char	*s;
	int		i;
	
	i = 0;
	while(input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		if (input[i] == '\'' || input[i] == '\"')
			quote_handler(token, input, &i);
		else
		{
			s = string_found(input, &i);
			if(!s)
				break ;
			new_token = initialize_token(s);
			list_add_last_token(token, new_token);
			free(s);
		}
		i++;
	}
	//token = quote_handler(input);
}

void	tokenizer(char *input)
{
	t_token	*token;

	token = NULL;
	token_split(&token, input);
	print_token_list(token);
	print_tokens(token);
	free_tokens(&token);
}

/* void	token_split(t_token **token, char *input)
{
	t_token	*new_token;
	char	**splitted;
	int		i;

	//splitted = ft_split(input, ' ');
	//token = quote_handler(input);
	i = 0;
	while (splitted[i] != NULL)
	{
		new_token = initialize_token(splitted[i]);
		list_add_last_token(token, new_token);
		i++;
	}
	free_char_pp(splitted);
} */