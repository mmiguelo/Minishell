/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:18:50 by yes               #+#    #+#             */
/*   Updated: 2025/04/30 11:27:38 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Frees a dynamically allocated NULL-terminated matrix of strings.
 *
 * @param matrix A pointer to a matrix (void***) to free and NULL out.
 */
void	ft_matrix_free(void ***matrix)
{
	int	i;

	if (!(*matrix))
		return ;
	i = 0;
	while ((*matrix)[i])
	{
		free((*matrix)[i]);
		(*matrix)[i] = NULL;
		i++;
	}
	free (*matrix);
	*matrix = NULL;
}
