/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 11:34:34 by brendos-          #+#    #+#             */
/*   Updated: 2026/01/25 11:34:36 by brendos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	table->philos = malloc(sizeof(t_philo) * table->philos_nbr);
	if (!table->philos)
	{
		write(2, "Error: malloc failed for philos\n", 32);
		return (0);
	}
	i = -1;
	while (++i < table->philos_nbr)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->meals_count = 0;
		philo->last_meal = 0;
		philo->table = table;
		philo->left_fork = &table->forks[i];
		philo->right_fork = &table->forks[(i + 1) % table->philos_nbr];
	}
	return (1);
}
