/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:10:04 by yes               #+#    #+#             */
/*   Updated: 2025/05/09 15:51:30 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1 || !s2)
	{
		ft_free(&s1);
		ft_free(&s2);
		return (NULL);
	}
	joined = ft_strjoin(s1, s2);
	ft_free(&s1);
	ft_free(&s2);
	return (joined);
}
