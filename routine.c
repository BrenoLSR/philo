/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 11:34:50 by brendos-          #+#    #+#             */
/*   Updated: 2026/01/25 11:34:52 by brendos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	sim_stopped(t_table *table)
{
	int	stopped;

	pthread_mutex_lock(&table->lock_mtx);
	stopped = table->stop_simulation;
	pthread_mutex_unlock(&table->lock_mtx);
	return (stopped);
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->id % 2 == 0)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	else
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	pthread_mutex_lock(first);
	safe_print(philo->table, philo->id, "has taken a fork");
	pthread_mutex_lock(second);
	safe_print(philo->table, philo->id, "has taken a fork");
}

static void	*one_philo_routine(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->lock_mtx);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&table->lock_mtx);
	pthread_mutex_lock(philo->left_fork);
	safe_print(table, philo->id, "has taken a fork");
	smart_sleep(table, table->time_die);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

static void	eat_sleep_think(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->lock_mtx);
	philo->last_meal = get_time_ms();
	philo->meals_count++;
	pthread_mutex_unlock(&table->lock_mtx);
	safe_print(table, philo->id, "is eating");
	smart_sleep(table, table->time_eat);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	safe_print(table, philo->id, "is sleeping");
	smart_sleep(table, table->time_sleep);
	safe_print(table, philo->id, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (table->philos_nbr == 1)
		return (one_philo_routine(philo));
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!sim_stopped(table))
	{
		take_forks(philo);
		eat_sleep_think(philo);
	}
	return (NULL);
}
