/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:30:35 by yes               #+#    #+#             */
/*   Updated: 2025/04/10 12:09:53 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

static int	ft_putpointerhex_fd(unsigned long n, int fd)
{
	char	*base;
	int		result;

	result = 0;
	base = "0123456789abcdef";
	if (n >= 16)
	{
		result += ft_putpointerhex_fd(n / 16, fd);
		result += ft_putpointerhex_fd(n % 16, fd);
	}
	else
		result += write (fd, &base[n], 1);
	return (result);
}

int	ft_putptr_fd(void *n, int fd)
{
	int				result;
	unsigned long	nbr;

	nbr = (unsigned long)n;
	result = 0;
	if (!nbr)
	{
		write(fd, "(nil)", 5);
		return (5);
	}
	result += ft_putstr_fd_pf("0x", fd);
	if (nbr == 0)
		result += ft_putchar_fd_pf(0, fd);
	else
		result += ft_putpointerhex_fd(nbr, fd);
	return (result);
}
