/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 11:35:23 by brendos-          #+#    #+#             */
/*   Updated: 2026/01/25 11:35:26 by brendos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_basic_fields(t_table *table)
{
	table->start_time = 0;
	table->stop_simulation = 0;
	table->philos = NULL;
	table->forks = NULL;
}

static int	alloc_forks(t_table *table)
{
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philos_nbr);
	if (!table->forks)
	{
		write(2, "Error: malloc failed for forks\n", 31);
		return (0);
	}
	return (1);
}

static int	init_forks(t_table *table)
{
	int	i;
	int	j;

	i = 0;
	while (i < table->philos_nbr)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&table->forks[j]);
				j++;
			}
			free(table->forks);
			table->forks = NULL;
			write(2, "Error: failed to init fork mutex\n", 33);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_global_mutex(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->lock_mtx, NULL) != 0)
	{
		i = 0;
		while (i < table->philos_nbr)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
		table->forks = NULL;
		write(2, "Error: failed to init global mutex\n", 35);
		return (0);
	}
	return (1);
}

int	init_table(t_table *table)
{
	init_basic_fields(table);
	if (!alloc_forks(table))
		return (0);
	if (!init_forks(table))
		return (0);
	if (!init_global_mutex(table))
		return (0);
	return (1);
}
