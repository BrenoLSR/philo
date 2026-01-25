/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 11:36:04 by brendos-          #+#    #+#             */
/*   Updated: 2026/01/25 11:36:06 by brendos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	safe_print(t_table *table, int id, const char *msg)
{
	long	now;
	long	relative_time;

	pthread_mutex_lock(&table->lock_mtx);
	if (table->stop_simulation && ft_strcmp(msg, "died") != 0)
	{
		pthread_mutex_unlock(&table->lock_mtx);
		return ;
	}
	now = get_time_ms();
	relative_time = now - table->start_time;
	printf("%ld %d %s\n", relative_time, id, msg);
	pthread_mutex_unlock(&table->lock_mtx);
}

int	error(const char *msg)
{
	printf("Error: %s\n", msg);
	return (0);
}
