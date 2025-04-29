/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_pf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:09 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/04/10 12:06:39 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

void	ft_printstr_fd( char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	ft_putstr_fd_pf(char *str, int fd)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		ft_printstr_fd("(null)", fd);
		return (6);
	}
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (i);
}
