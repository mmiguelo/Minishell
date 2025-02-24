/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:31:13 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/24 17:50:52 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* char *string_found(char *input, int *i)
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
} */

char *string_found(char *input, int *i)
{
	char	*new_s;
	int		len;
	int		j;

	j = 0;
	len = 0;
	while(input[*i] && input[*i] != '|')
	{
		*i = *i + 1;
		len++;
	}
	new_s = (char *)malloc((len + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	while (len != 0)
	{
		new_s[j] = input[*i - len];
		len--;
		j++;
	}
	new_s[j] = '\0';
	*i = *i - 1;
	return (new_s);
}

void	node_split(t_token_tree **token_list, char *input)
{
	t_token_tree	*new_node;
	char			*s;
	int				i;
	
	i = 0;
	while(input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		else
		{
			if (input[i] == '|')
			{
				new_node = initialize_token_list("|", PIPE);
				add_pipe_to_node(token_list, new_node);
			}
			else
			{
				s = string_found(input, &i);
				if(!s)
					break ;
				new_node = initialize_token_list(s, EXEC);
				add_last_node(token_list, new_node);
				free(s);
			}
		}
		i++;
	}
}

void	tokenizer(char *input)
{
	t_token_tree	*token_list;

	token_list = NULL;
	node_split(&token_list, input);
	print_token_list(token_list);
	//print_token_list_simple(token_list);//not fuctional for token_list!
	free_token_list(&token_list);
}

/* void	token_split(t_token_tree **token_list, char *input)
{
	t_token_tree	*new_token;
	char	**splitted;
	int		i;

	splitted = ft_split(input, ' ');
	i = 0;
	while (splitted[i] != NULL)
	{
		new_token = initialize_token(splitted[i]);
		list_add_last_token(token_list, new_token);
		i++;
	}
	free_char_pp(splitted);
} */