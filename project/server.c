/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:20:39 by zsonie            #+#    #+#             */
/*   Updated: 2025/03/21 01:54:44 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minitalk.h"

int	fullsignal;

static void	print_user_message(int sig)
{
	static int	bit_count = 0;
	bool debug = false;

	if (sig == SIGUSR2)
		fullsignal |= (1 << (7 - bit_count));
	else
		fullsignal &= ~(1 << (7 - bit_count));
	bit_count++;

	if (debug)
	{
		printf("Signal received: %s, fullsignal: %d, bit_count: %d\n",
			(sig == SIGUSR1) ? "SIGUSR1" : "SIGUSR2", fullsignal, bit_count);
	}
	if (bit_count == 8)
	{
		char c = (char)fullsignal;
		if (c == '\0')
			write(1, "\n", 1);
		else
		{
			write(1, &c, 1);
		}
		fullsignal = 0;
		bit_count = 0;
	}
}

static void	print_PID(void)
{
	int	pid;

	pid = getpid();
	printf("SERVER PID: %d\n", pid);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	print_PID();
	while (1)
	{
		signal(SIGUSR1, print_user_message);
		signal(SIGUSR2, print_user_message);
		
		pause();
	}
	return (0);
}