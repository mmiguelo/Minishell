/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:18:29 by yes               #+#    #+#             */
/*   Updated: 2025/04/10 12:10:32 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H

# include <stdarg.h> // variadic
# include <unistd.h> // write
# include <stdio.h> // test printf
# include <stdlib.h> //free malloc
# include "../libft.h"

int	ft_printf_fd(int fd, const char *str, ...);
int	print_args_fd(va_list args, const char specifier, int fd);
int	ft_puthex_fd(unsigned int n, char c, int fd);
int	ft_putptr_fd(void *n, int fd);
int	ft_pututoa_fd(unsigned int n, int fd);
int	ft_putstr_fd_pf(char *str, int fd);
int	ft_putnbr_fd_pf(int n, int fd);
int	ft_putchar_fd_pf(char c, int fd);

#endif