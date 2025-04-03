/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:20:42 by zsonie            #+#    #+#             */
/*   Updated: 2025/04/03 12:02:32 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700

#include "inc/minitalk.h"
#include <time.h>

static volatile int	ack_received = 0;

static void	wait_for_acknowledgment(void)
{
	int	timeout;

	timeout = 10000;
	while (!ack_received)
	{
		usleep(1);
		timeout -= 100;
		if (timeout <= 0)
		{
			write(2, "Error: Acknowledgment timeout\n", 30);
			exit(1);
		}
	}
	ack_received = 0;
}

static void	ack_handler(int sig)
{
	(void)sig;
	write(1, "Acknowledgment received\n", 24);
	ack_received = 1;
}

static void	send_message(int pid, char *message)
{
	int	i;
	int	j;

	i = 0;
	while (message[i])
	{
		j = 7;
		while (j >= 0)
		{
			if (message[i] & (1 << j))
			{
				if (kill(pid, SIGUSR2) == -1)
					exit(1);
				else if (kill(pid, SIGUSR1) == -1)
					exit(1);
			}
			wait_for_acknowledgment();
			j--;
		}
		i++;
	}
}

static void	end_of_transmission(int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			write(2, "Error: Failed to send end-of-transmission signal\n", 49);
			exit(1);
		}
		pause();
		i++;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	if (ac != 3)
	{
		write(2, "Usage: ./client <PID> <message>\n", 32);
		return (1);
	}
	// Set up acknowledgment signal handler
	sa.sa_handler = ack_handler;
	sa.sa_flags = SA_RESTART | SA_NODEFER;
	sigaction(SIGUSR1, &sa, NULL);
	send_message(atoi(av[1]), av[2]);
	end_of_transmission(atoi(av[1]));
	return (0);
}
