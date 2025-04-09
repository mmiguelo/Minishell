/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:22:19 by yes               #+#    #+#             */
/*   Updated: 2025/04/09 16:49:06 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**token_list_to_array(t_token *tokens)
{
	t_token	*temp;
	char	**array;
	int		count;
	int		i;

	temp = tokens;
	count = 0;
	i = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	array = ft_calloc((count + 1), sizeof(char *));
	if (!array)
		return (NULL);
	temp = tokens;
	while (temp)
	{
		array[i] = ft_strdup(temp->token);
		temp = temp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
