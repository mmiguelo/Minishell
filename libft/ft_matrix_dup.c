/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:21:59 by yes               #+#    #+#             */
/*   Updated: 2025/04/30 11:27:40 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
