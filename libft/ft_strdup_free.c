/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:06:24 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/03/31 13:13:48 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Duplicates a string and frees the original strings.
 * 
 * @param s1 
 * @param s2 
 * @return char* 
 */
char	*ft_strdup_free(char *s1, char *s2)
{
	char	*dest;

	dest = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (dest);
}
