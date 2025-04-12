/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/11/19 19:06:04 by zsonie            #+#    #+#             */
/*   Updated: 2024/11/24 17:44:44 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"
#include <limits.h>
#include <stddef.h>

static void	ft_space_and_sign_increment(const char *str, size_t *i, int *sign)
{
	*i = 0;
	while (str[*i] && ((str[*i] == ' ') || (str[*i] >= 9 && str[*i] <= 13)))
		(*i)++;
	*sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

int	ft_atoi(const char *str)
{
	size_t	i;
	long	num;
	int		sign;

	num = 0;
	ft_space_and_sign_increment(str, &i, &sign);
	while (str[i] && !(str[i] < '0' || str[i] > '9'))
	{
		if (LONG_MAX / 10 < num)
		{
			if (sign > 0)
				return (-1);
			return (0);
		}
		num *= 10;
		if (LONG_MAX - (str[i] - 48) < num)
		{
			if (sign > 0)
				return (-1);
			return (0);
		}
		num += str[i] - '0';
		i++;
	}
	return (num * sign);
}

static bool	ft_isdigit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (false);
	}
	return (true);
}

bool	err_handlr(int ac, char **av)
{
	if (ac != 3)
	{
		write(2, "Usage: ./client <PID> <message>\n", 32);
		return (false);
	}
	if (ft_atoi(av[1]) <= 0 || !ft_isdigit(av[1]) || ft_atoi(av[1]) > MAX_PID)
	{
		write(2, "Correct PID needed!", 20);
		return (false);
	}
	if (ft_strlen(av[2]) > MAX_MESSAGE_LENGTH)
	{
		write(2, "Message too long\n", 18);
		return (false);
	}
	return (true);
}
