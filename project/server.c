/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:20:39 by zsonie            #+#    #+#             */
/*   Updated: 2025/04/03 11:47:13 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minitalk.h"

int			fullsignal;

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
	static int	bit_count = 0;
	char		c;
	pid_t		client_pid;

	static int fullsignal = 0; // Reset for each client
	(void)context;
	client_pid = info->si_pid; // Get the client PID from siginfo_t
	if (sig == SIGUSR2)
		fullsignal |= (1 << (7 - bit_count));
	else
		fullsignal &= ~(1 << (7 - bit_count));
	bit_count++;
	if (bit_count == 8)
	{
		c = (char)fullsignal;
		if (c == '\0') // End of message
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		fullsignal = 0;
		bit_count = 0;
	}
	// Send acknowledgment signal to the client
	if (kill(client_pid, SIGUSR1) == -1)
		write(1, "Error sending acknowledgment to client\n", 40);
	else
		write(1, "Acknowledgment sent\n", 21);
}

static void	print_PID(void)
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
	print_PID();
	sa.sa_sigaction = print_user_message;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	// Use SA_SIGINFO and restart system calls
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause(); // Wait for signals
	return (0);
}
