/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 11:30:42 by brendos-          #+#    #+#             */
/*   Updated: 2026/01/25 11:30:45 by brendos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_forks(pthread_mutex_t *forks, int count)
{
	int	i;

	if (!forks)
		return ;
	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

static void	clean_philos(t_philo *philos)
{
	if (!philos)
		return ;
	free(philos);
}

void	clean_table(t_table *table)
{
	if (!table)
		return ;
	if (table->forks)
	{
		clean_forks(table->forks, table->philos_nbr);
		table->forks = NULL;
	}
	if (table->philos)
	{
		clean_philos(table->philos);
		table->philos = NULL;
	}
	pthread_mutex_destroy(&table->lock_mtx);
}
