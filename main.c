#include "philo.h"

static bool	start_simulation(t_table *table)
{
	int	i;

	table->start_time = time_ms() + (table->philo_nbr * 2 * 10);
	i = 0;
	while (i++ < table->philo_nbr)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, &philo_routine,
				&table->philos[i]) != 0)
			return (false);
	}
	if (table->philo_nbr > 1)
	{
		if (pthread_create(&table->monitor, NULL, &monitor_routine,
				&table->monitor) != 0)
			return (false);
	}
	return (true);
}

static void	stop_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i++ < table->philo_nbr)
		pthread_join(table->philos[i].thread_id, NULL);
	if (table->philo_nbr > 1)
		pthread_join(table->monitor, NULL);
	clean_table(table);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc < 5 || argc > 6)
	{
		write(2, "Argument Error\n", 15);
		return (1);
	}
	table = ft_calloc(1, sizeof(t_table));
	if (!table)
		return (1);
	if (!valid_init_input(table, argc, argv, 0) || (!init_forks_mutex(table))
		|| (!init_create_philo(table)))
	{
		clean_table(table);
		return (1);
	}
	if (!sim_start(table))
	{
		clean_table(table);
		return (1);
	}
	sim_stop(table);
	return (0);
}
