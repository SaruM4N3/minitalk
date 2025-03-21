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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	fullsignal;

static void	print_user_message(int sig)
{
	fullsignal = fullsignal << 1;
	if (sig == SIGUSR2)
	{
		fullsignal = fullsignal | 1;
	}
	if (strlen(ft_itoa(fullsignal)) == 8)
	{
		write(1, "enter", 5);
		if (!strchr(ft_itoa(fullsignal), '1'))
			write(1, "end", 3);
		else
		{
			write(1, "\n", 1);
			write(1, &fullsignal, 1);
		}
		fullsignal = 0;	
	}
}

static void	print_PID(void)
{
	int	pid;

	pid = getpid();
	printf("SERVER PID: %d\n", pid);
	write(1, "\n", 1);
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
		// signal(SIGUSR1, print_letter);
		// signal(SIGUSR2, print_letter);
		
		pause();
	}
	return (0);
}