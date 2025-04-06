/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saru <saru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:20:42 by zsonie            #+#    #+#             */
/*   Updated: 2025/04/06 21:13:29 by saru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minitalk.h"

static volatile int	g_ack_received = 0;

static void	wait_for_acknowledgment(void)
{
	int	timeout_count;

	timeout_count = 0;
	while (!g_ack_received)
	{
		usleep(100);
		timeout_count += 1;
		if (timeout_count >= 10000)
		{
			write(2, "Error: Acknowledgment timeout\n", 30);
			exit(1);
		}
	}
	g_ack_received = 0;
}

static void	ack_handler(int sig)
{
	(void) sig;
	g_ack_received = 1;
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
			}
			else
			{
				if (kill(pid, SIGUSR1) == -1)
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
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_handler = ack_handler;
	sigaction(SIGUSR1, &sa, NULL);
	send_message(atoi(av[1]), av[2]);
	end_of_transmission(atoi(av[1]));
	return (0);
}
