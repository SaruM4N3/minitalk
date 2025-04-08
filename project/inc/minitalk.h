/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saru <saru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 01:41:52 by zsonie            #+#    #+#             */
/*   Updated: 2025/04/08 17:43:38 by saru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define MAX_MESSAGE_LENGTH 65000
# define MAX_TIMEOUT_ACK 10000

# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>

typedef struct s_server
{
	int		message_length;
	bool	running;
	int		i;
	bool	has_received;
}	t_server;

char	*ft_itoa(int n);
int		ft_strlen(char *str);
int		ft_atoi(const char *str);
void	*ft_bzero(void *s, size_t n);
bool	err_handlr(int ac, char **av);

#endif