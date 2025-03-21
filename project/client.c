/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:20:42 by zsonie            #+#    #+#             */
/*   Updated: 2025/03/21 01:21:38 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static void	send_message(int pid, char *message)
{
	int		i;
	int		j;

	i = 0;
	while (message[i])
	{
		j = 0;
		while (j < 8)
		{
			if (message[i] & (1 << j))
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			j++;
			usleep(500);
		}
		i++;
	}
}
static void end_of_transmission(int pid)
{
	int i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR1);
		usleep(100);
		i++;
	}
}

int main(int ac, char **av)
{
	if (ac != 3)
		return (0);
	send_message(atoi(av[1]), av[2]);
	end_of_transmission(atoi(av[1]));
}
