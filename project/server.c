/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:20:39 by zsonie            #+#    #+#             */
/*   Updated: 2025/03/19 21:51:38 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		*bynary_message;

static void	receive_message(int sig)
{
	static int		c;
	static char		letter;

	c = 0;
	letter = 0;
	if (sig == SIGUSR1)
		letter = letter | (0 << c);
	else if (sig == SIGUSR2)
		letter = letter | (1 << c);
	c++;
	if (c == 8)
	{
		write(1, &letter, 1);
		c = 0;
		letter = 0;
	}
}

static char	*convert_message_to_base10(char *binary_message)
{
	int		i;
	int		j;
	char	*message;

	i = 0;
	j = 0;
	message = malloc(1000);
	while (binary_message[i])
	{
		message[j] = message[j] | (binary_message[i] << j);
		j++;
		if (j == 8)
		{
			j = 0;
			i++;
		}
	}
	return (message);
}

static void	print_user_message(int sig)
{
	if (sig == SIGUSR1)
	{
		write(1, "0", 1);
	}
	else if (sig == SIGUSR2)
	{
		write(1, "1", 1);
	}
}

static void	print_PID(void)
{
	int pid;

	pid = getpid();
	printf("SERVER PID: %d\n", pid);
	write(1, "\n", 1);
}

int main(int ac, char **av)
{
	(void)	ac;
	(void)	av;	
	print_PID();
	bynary_message = malloc(message_lenght + 1);
	while (1)
	{
		while (message_lenght < 8)
		{
			signal(SIGUSR1, print_user_message);
			signal(SIGUSR2, print_user_message);
		}		
		printf("Bynary : %d\n", *bynary_message);

		pause();
	}
	return (0);
}