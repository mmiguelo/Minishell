/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd_pf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:54:29 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/04/10 12:07:07 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

int	ft_putnbr_fd_pf(int n, int fd)
{
	int		length;
	char	*num;

	length = 0;
	num = ft_itoa(n);
	length = ft_putstr_fd_pf(num, fd);
	free(num);
	return (length);
}
