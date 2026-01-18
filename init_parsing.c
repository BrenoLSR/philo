/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:20:51 by brendos-          #+#    #+#             */
/*   Updated: 2026/01/18 16:20:55 by brendos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_create_philo(t_table *table)
{
	int	i;

	table->philos = ft_calloc(table->philo_nbr, sizeof(t_philo));
	if (!table->philos)
		return (printf("Error: malloc philos failed\n"), false);
	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_count = 0;
		table->philos[i].table = table;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->philo_nbr];
		if (pthread_mutex_init(&table->philos[i].eat_lock, NULL) != 0)
		{
			printf("Error: mutex init eat_lock (philo %d)\n", i + 1);
			clean_philos(table->philos, i);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	init_forks_mutex(t_table *table)
{
	int	i;

	table->simulation_finish = false;
	table->forks = ft_calloc(table->philo_nbr, sizeof(t_mutex));
	if (!table->forks)
		return (printf("Error: malloc forks failed\n"), false);
	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			printf("Error: mutex init fork %d\n", i + 1);
			clean_forks(table->forks, i);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	parse_and_init(t_table *table, int ac, char **av, int i)
{
	while (++i < ac)
	{
		if (ft_atol(av[i]) <= 0)
			return (printf("Error: invalid argument %s\n", av[i]), false);
	}
	table->philo_nbr = (int)ft_atol(av[1]);
	table->time_die = ft_atol(av[2]);
	table->time_eat = ft_atol(av[3]);
	table->time_sleep = ft_atol(av[4]);
	table->limit_meals = -1;
	if (av[5])
		table->limit_meals = (int)ft_atol(av[5]);
	if (pthread_mutex_init(&table->write_lock, NULL) != 0)
		return (printf("Error: mutex init write_lock\n"), false);
	if (pthread_mutex_init(&table->sim_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->write_lock);
		return (printf("Error: mutex init sim_lock\n"), false);
	}
	return (true);
}
