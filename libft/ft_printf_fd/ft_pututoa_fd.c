/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pututoa_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:30:49 by yes               #+#    #+#             */
/*   Updated: 2025/04/10 12:18:12 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

static unsigned int	ft_intlenght_fd(unsigned int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

int	ft_pututoa_fd(unsigned int n, int fd)
{
	char	*str;
	size_t	lenght;
	int		result;

	result = 0;
	lenght = ft_intlenght_fd(n);
	str = (char *)malloc(sizeof(char) * (lenght + 1));
	if (!str)
		return (0);
	str[lenght] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		lenght--;
		str[lenght] = (n % 10) + 48;
		n = n / 10;
	}
	result = ft_putstr_fd_pf(str, fd);
	free(str);
	return (result);
}
