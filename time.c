/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 11:35:42 by brendos-          #+#    #+#             */
/*   Updated: 2026/01/25 11:35:44 by brendos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)time.tv_sec * 1000
		+ (long long)time.tv_usec / 1000);
}

void	smart_sleep(t_table *table, long wakeup)
{
	long	start;

	start = get_time_ms() + wakeup;
	while (get_time_ms() < start)
	{
		if (table->stop_simulation)
			break ;
		usleep(100);
	}
}
