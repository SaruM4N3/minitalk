/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saru <saru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:20:39 by zsonie            #+#    #+#             */
/*   Updated: 2025/04/08 19:21:34 by saru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"
#include "../inc/ft_printf.h"

volatile t_server	g_data = {0, true, -1, false};

bool	message_length_received(char current_char, char **str)
{
	static char	tmp[12] = "";

	if (g_data.has_received)
		return (true);
	if (current_char == '!')
	{
		g_data.message_length = ft_atoi((const char *)tmp);
		*str = malloc(sizeof(char) * (g_data.message_length + 1));
		g_data.has_received = true;
		ft_bzero(tmp, sizeof(tmp));
	}
	else
		tmp[++g_data.i] = current_char;
	return (false);
}

void	print_and_reset(char **buffer, int *fullsignal, int *i)
{
	if ((char)*fullsignal == '\0')
	{
		write(1, *buffer, g_data.message_length);
		write(1, "\n", 1);
		g_data.message_length = 0;
		g_data.running = true;
		g_data.i = -1;
		g_data.has_received = false;
		free(*buffer);
		*buffer = NULL;
		*i = 0;
	}
	else
		(*buffer)[(*i)++] = (char)*fullsignal;
}

static void	print_user_message(int sig, siginfo_t *info, void *context)
{
	static int	fullsignal = 0;
	static int	bit_count = 0;
	static char	*buffer;
	static int	i = 0;

	(void)context;
	if (sig == SIGUSR2)
		fullsignal |= (1 << (7 - bit_count));
	if (++bit_count == 8)
	{
		if (message_length_received((char)fullsignal, &buffer))
		{
			if (!buffer)
			{
				g_data.running = false;
				return ;
			}
			print_and_reset(&buffer, &fullsignal, &i);
		}
		fullsignal = 0;
		bit_count = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		write(1, "Error sending acknowledgment to client\n", 40);
}

static void	print_pid(void)
{
	int	pid;

	pid = getpid();
	ft_printf("SERVER PID: %d\n", pid);
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
	while (g_data.running)
		pause();
	return (0);
}
