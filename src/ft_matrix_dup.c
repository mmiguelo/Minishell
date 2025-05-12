/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:21:59 by yes               #+#    #+#             */
/*   Updated: 2025/05/08 12:48:56 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a deep copy of a NULL-terminated matrix of strings.
 *
 * @param matrix A void** pointing to a NULL-terminated array of char*.
 * @return A deep copied matrix (void**) or NULL on allocation failure.
 */
char	**ft_matrix_dup(char **matrix)
{
	char	**dup;
	int		i;
	int		len;

	i = 0;
	len = 0;
	matrix = (char **)matrix;
	while (matrix[len])
		len++;
	dup = (char **)ft_calloc(len + 1, sizeof(char *));
	while (i < len)
	{
		dup[i] = ft_strldup(matrix[i], ft_strlen(matrix[i]));
		if (!dup[i])
		{
			ft_matrix_free((void ***)(&dup));
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
