/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saru <saru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 07:30:24 by zsonie            #+#    #+#             */
/*   Updated: 2025/04/08 17:35:05 by saru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	ptr;
	size_t	i;
	size_t	fsize;

	i = 0;
	fsize = 0;
	if (!str)
		return (1);
	va_start(ptr, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			ft_printf_parse(str[i + 1], ptr, &fsize);
			i++;
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			fsize++;
		}
		i++;
	}
	va_end(ptr);
	return (fsize);
}
