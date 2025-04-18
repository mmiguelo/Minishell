/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:19:33 by yes               #+#    #+#             */
/*   Updated: 2025/04/18 17:09:16 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a deep copy of a NULL-terminated matrix of strings.
 *
 * @param matrix A void** pointing to a NULL-terminated array of char*.
 * @return A deep copied matrix (void**) or NULL on allocation failure.
 */
void	**ft_matrix_dup(void **matrix)
{
	char	**matrix_str;
	char	**dup;
	int		i;
	int		len;

	i = 0;
	len = 0;
	matrix_str = (char **)matrix;
	while (matrix_str[len])
		len++;
	dup = (char **)ft_calloc(len + 1, sizeof(char *));
	while (i < len)
	{
		dup[i] = ft_strldup(matrix_str[i], ft_strlen(matrix_str[i]));
		if (!dup[i])
		{
			ft_matrix_free((void ***)(&dup));
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return ((void **)dup);
}
