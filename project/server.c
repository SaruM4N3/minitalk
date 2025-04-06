/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saru <saru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:20:39 by zsonie            #+#    #+#             */
/*   Updated: 2025/04/06 20:47:12 by saru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minitalk.h"

bool	message_fully_received(char c)
{
	if (c == '\0')
	{
		write(1, "Message entirely received\n", 27);
		return (true);
	}
	return (false);
}

static void	print_user_message(int sig, siginfo_t *info, void *context)
{
	static int	fullsignal = 0;
	static int	bit_count = 0;
	char		c;
	pid_t		client_pid;

	(void)context;
	client_pid = info->si_pid;
	if (sig == SIGUSR2)
		fullsignal |= (1 << (7 - bit_count));
	if (++bit_count == 8)
	{
		c = (char) fullsignal;
		if (c == '\0')
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		fullsignal = 0;
		bit_count = 0;
	}
	if (kill(client_pid, SIGUSR1) == -1)
		write(1, "Error sending acknowledgment to client\n", 40);
}

static void	print_pid(void)
{
	int	pid;

	pid = getpid();
	printf("SERVER PID: %d\n", pid);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	(void)ac;
	(void)av;
	print_pid();
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = print_user_message;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
