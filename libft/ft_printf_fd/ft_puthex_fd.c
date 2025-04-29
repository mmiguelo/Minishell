/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:30:23 by yes               #+#    #+#             */
/*   Updated: 2025/04/09 18:36:20 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

int	ft_puthex_fd(unsigned int n, char c, int fd)
{
	char	*base;
	int		result;

	result = 0;
	if (c == 'x')
		base = "0123456789abcdef";
	if (c == 'X')
		base = "0123456789ABCDEF";
	if (n >= 16)
	{
		result += ft_puthex_fd((n / 16), c, fd);
		result += ft_puthex_fd((n % 16), c, fd);
	}
	else
		result += write (fd, &base[n], 1);
	return (result);
}
