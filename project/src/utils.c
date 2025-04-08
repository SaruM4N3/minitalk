/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:06:04 by zsonie            #+#    #+#             */
/*   Updated: 2024/11/24 17:44:44 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_itoa(int n)
{
	char			*res;
	int				len;
	unsigned int	num;

	len = ft_intlen(n);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	num = n;
	if (n < 0)
		num = -n;
	res[len] = '\0';
	while (len-- != 0)
	{
		res[len] = num % 10 + 48;
		num /= 10;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}

void	*ft_bzero(void *s, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		((unsigned char *) s)[i] = 0;
		i++;
	}
	return (s);
}
