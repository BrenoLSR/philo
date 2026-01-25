/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 11:35:05 by brendos-          #+#    #+#             */
/*   Updated: 2026/01/25 11:35:07 by brendos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	join_threads(t_table *table, pthread_t monitor_thread)
{
	size_t	i;

	i = 0;
	while (i < (size_t)table->philos_nbr)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (error("waiting for philo thread"));
		i++;
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		return (error("waiting for monitor thread"));
	return (1);
}

int	sim_start(t_table *table)
{
	size_t		i;
	pthread_t	monitor_thread;

	table->start_time = get_time_ms();
	pthread_mutex_lock(&table->lock_mtx);
	i = 0;
	while (i < (size_t)table->philos_nbr)
	{
		table->philos[i].last_meal = table->start_time;
		i++;
	}
	pthread_mutex_unlock(&table->lock_mtx);
	i = 0;
	while (i < (size_t)table->philos_nbr)
	{
		if (pthread_create(&table->philos[i].thread, NULL, philo_routine,
				&table->philos[i]) != 0)
			return (error("while creating philo thread"));
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_routine, table) != 0)
		return (error("while creating monitor thread"));
	if (!join_threads(table, monitor_thread))
		return (0);
	return (1);
}
