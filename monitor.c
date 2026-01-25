/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 11:32:39 by brendos-          #+#    #+#             */
/*   Updated: 2026/01/25 11:32:42 by brendos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philo_death(t_table *table, int i)
{
	long	now;
	long	diff;

	now = get_time_ms();
	diff = now - table->philos[i].last_meal;
	if (diff > table->time_die)
	{
		table->stop_simulation = 1;
		pthread_mutex_unlock(&table->lock_mtx);
		safe_print(table, table->philos[i].id, "died");
		return (1);
	}
	return (0);
}

static int	check_all_philos(t_table *table, int *finished)
{
	int	i;

	i = 0;
	while (i < table->philos_nbr)
	{
		pthread_mutex_lock(&table->lock_mtx);
		if (table->stop_simulation)
			return (pthread_mutex_unlock(&table->lock_mtx), 0);
		if (check_philo_death(table, i))
			return (0);
		if (table->limit_meals > 0
			&& table->philos[i].meals_count >= table->limit_meals)
			(*finished)++;
		pthread_mutex_unlock(&table->lock_mtx);
		i++;
	}
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		finished;

	table = (t_table *)arg;
	while (1)
	{
		finished = 0;
		if (!check_all_philos(table, &finished))
			return (NULL);
		if (table->limit_meals > 0 && finished == table->philos_nbr)
		{
			pthread_mutex_lock(&table->lock_mtx);
			table->stop_simulation = 1;
			pthread_mutex_unlock(&table->lock_mtx);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
