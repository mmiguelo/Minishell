/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:22:19 by yes               #+#    #+#             */
/*   Updated: 2025/04/29 15:42:03 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_list_size(t_token *token)
{
	t_token	*temp;
	int		count;

	if (!token)
		return (0);
	count = 0;
	temp = token;
	while (temp)
	{
		temp = temp->next;
		count++;
	}
	return (count);
}

char	**token_list_to_array(t_token *tokens)
{
	t_token	*temp;
	char	**array;
	int		i;

	temp = tokens;
	i = 0;
	array = (char **)ft_calloc((token_list_size(tokens) + 1), sizeof(char *));
	if (!array)
		return (NULL);
	while (temp)
	{
		array[i] = ft_strdup(temp->token);
		if (!array[i])
			return (ft_matrix_free((void ***)&array), NULL);
		temp = temp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
